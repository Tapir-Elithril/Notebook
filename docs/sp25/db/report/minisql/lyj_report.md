<br/>

<font face="Times">

<div align=center>
<img src=img/image.png width=45%>
</div>

# <font size= 20><center>DataBase System</center></font>

<br/><br/>

# <font size= 20><center><font face="Times">MiniSQL 个人设计报告</font></center></font>

<br/><br/><br/><br/>

<div align=center>
    <font face="楷体" size="5">
        姓名：<u>&emsp;&emsp;刘&emsp;奕&emsp;嘉&emsp;&emsp;</u><br/><br/><br/>
    </font>
</div>


<div STYLE="page-break-after: always;"></div>



## 一、 实验背景与目的

- 设计并实现一个精简型单用户SQL引擎MiniSQL，允许用户通过字符界面输入SQL语句实现基本的增删改查操作，并能够通过索引来优化性能。
- 通过对MiniSQL的设计与实现，提高系统编程能力，加深对数据库管理系统底层设计的理解。


## 二、 设计完成内容
- 在本次实验中，设计并完成DISK AND BUFFER POOL MANAGER模块，RECORD MANAGER模块，LOCK MANAGER模块：
  - `DISK AND BUFFER POOL MANAGER`相关文件：
  ![alt text](img/image1.png)
  - `RECORD MANAGER`相关文件：
  ![alt text](img/image2.png)
  - `LOCK MANAGER`相关文件：
  ![alt text](img/image3.png)
  

## 三、 具体模块设计

---
### `DISK AND BUFFER POOL MANAGER` 模块设计

#### 1、架构设计

`Disk and Buffer Pool Manager` 模块是数据库系统与磁盘进行交互的核心组件，主要负责数据的持久化存储、按需加载数据页到内存（缓冲池）以及管理缓冲池中的数据页，以优化磁盘 I/O 性能。

* **DiskManager (磁盘管理器):** 负责数据库文件在磁盘上的物理存储和逻辑页到物理页的映射，以及管理页的分配和回收。
    * 文件操作: 提供读写磁盘页的接口，确保数据能够在系统重启后依然可用。
    * 页分配与回收:
        * 采用位图机制来管理磁盘上的空闲页，每个位图页可以管理 `BITMAP_SIZE` 个数据页。
        * 整个数据库文件被划分为多个区，每个区包含一个位图页和 `BITMAP_SIZE` 个数据页。
        * 元数据页记录了整个数据库文件的全局信息，包括已分配页的数量和每个区已使用页的数量。
    * 逻辑页号到物理页号的映射: 实现一个映射函数将外部使用的逻辑页号转换为磁盘上的物理页号。

* **BitmapPage (位图页):** 管理一个区内数据页的分配状态。
    * 位图表示: 使用字节数组 `bytes` 来存储位图，每个位代表一个数据页的空闲状态。
    * 页分配/回收: 提供 `AllocatePage` 和 `DeAllocatePage` 方法，通过位图操作来分配和释放区内的逻辑页。
    * 查找空闲页: `next_free_page_` 成员变量记录下一个可能空闲页的偏移量，优化查找速度。
    * 已分配页计数: `page_allocated_` 记录当前位图页管理的区中已分配的页数量。

* **BufferPoolManager (缓冲池管理器):** 作为数据库的内存缓存层，管理从磁盘加载到内存的数据页。
    * 页缓存: 维护一个固定大小的内存区域，用于存储从磁盘读取的数据页。
    * 页查找与替换:
        * 当请求的页不在缓冲池中时，会从`free_list_`中获取一个页帧，或者通过页面替换算法淘汰一个现有页。
        * 目前采用 LRU 替换策略来选择牺牲页。
    * 页元数据管理: 维护每个页帧的元数据。
    * 页固定/取消固定: 通过 `pin_count` 来跟踪有多少个线程正在使用该页。被固定的页不能被替换。
    * 脏页处理: 如果牺牲页的内容被修改过，在替换之前必须将其写回磁盘。
    * 新页分配: 当需要一个新的数据页时，向 `DiskManager` 请求分配一个新的逻辑页，并将其加载到缓冲池中。

* **LRUReplacer (LRU 替换器):** 实现 LRU 页面替换算法。
    * 数据结构:
        * `lru_list_` (`std::list<frame_id_t>`): 双向链表，头部为最近使用的页帧，尾部为最久未使用的页帧。
        * `lru_set_` (`std::unordered_set<frame_id_t>`): 快速判断一个页帧是否在 `lru_list_` 中，以及快速查找并移除。
    * Pin/Unpin: `Pin` 操作将页帧从 `lru_list_` 中移除，使其不能被替换；`Unpin` 操作将页帧添加到 `lru_list_` 的头部，表示最近被使用。
    * Victim: 返回并移除 `lru_list_` 尾部的页帧（最近最少使用的），作为牺牲页。

#### 2、架构图示

* **位图**

![位图](img/bitmap.png)

* **磁盘数据页管理图**

![磁盘数据页管理图示](img/disk.png)

* 模块关键操作流程
    * 读操作流程：BufferPoolManager 请求页 → 检查缓冲池 → 不存在则调用 DiskManager 读取 → 转换逻辑页号为物理页号 → 加载到缓冲池
    * 写操作流程：BufferPoolManager 修改页 → 标记为脏页 → 缓冲池满时 LRUReplacer 选择牺牲页 → 脏页刷盘后释放

* **DISK AND BUFFER POOL MANAGER模块示意图**

![DISK AND BUFFER POOL MANAGER模块](img/dab.png)

---
#### 2、代码分析

**`bitmap_page.cpp`**

* `bool BitmapPage<PageSize>::AllocatePage(uint32_t &page_offset)`:
    * 在当前位图页管理的区中查找一个空闲位，将其标记为已分配。
    * 更新 `page_allocated_` 和 `next_free_page_`。
    * 通过 `page_offset` 返回分配的页在当前位图页管理区中的偏移量。
    * 如果区已满，返回 `false`。

* `bool BitmapPage<PageSize>::DeAllocatePage(uint32_t page_offset)`:
    * 将指定偏移量的页标记为空闲。
    * 更新 `page_allocated_` 并可能更新 `next_free_page_`。
    * 如果页已是空闲状态，返回 `false`。

* `bool BitmapPage<PageSize>::IsPageFree(uint32_t page_offset) const`:
    * 判断指定偏移量的页是否空闲。
    * 内部调用 `IsPageFreeLow` 来执行位操作判断。

* `bool BitmapPage<PageSize>::IsPageFreeLow(uint32_t byte_index, uint8_t bit_index) const`:
    * 实际的位操作函数，通过检查 `bytes[byte_index]` 中 `bit_index` 位的状态来判断页是否空闲。

---
**`buffer_pool_manager.cpp`**

* `Page *BufferPoolManager::FetchPage(page_id_t page_id)`:
    * 从缓冲池中获取指定 `page_id` 的数据页。
    * 查找页表: 如果页已在缓冲池中，增加 `pin_count` 并将页帧从 `replacer_` 中固定，然后返回。
    * 页替换: 如果页不在缓冲池中，尝试从 `free_list_` 获取页帧；如果 `free_list_` 为空，则从 `replacer_` 中选择一个牺牲页帧。
    * 脏页回写: 如果牺牲页是脏的，将其写回磁盘。
    * 更新页表: 将旧页从 `page_table_` 中移除，将新页插入 `page_table_`。
    * 读入新页: 从 `DiskManager` 读取请求的页到新的页帧中。
    * 更新元数据: 设置新页的 `page_id_`、`pin_count_` 、`is_dirty_` ，并固定该页帧。

* `Page *BufferPoolManager::NewPage(page_id_t &page_id)`:
    * 分配一个新的数据页并将其加载到缓冲池中。
    * 分配逻辑页: 调用 `DiskManager::AllocatePage` 分配一个新的逻辑页号。
    * 获取页帧: 与 `FetchPage` 类似，尝试从 `free_list_` 或 `replacer_` 获取一个可用的页帧。
    * 脏页回写: 如果选定的页帧是脏的，将其内容写回磁盘。
    * 更新页表: 从 `page_table_` 中移除旧映射，插入新页的映射。
    * 初始化新页: 重置页帧的内存为零，设置 `page_id_`、`pin_count_`、`is_dirty_`，并固定该页帧。

* `bool BufferPoolManager::DeletePage(page_id_t page_id)`:
    * 释放一个数据页。
    * 释放逻辑页: 调用 `DiskManager::DeallocatePage` 释放磁盘上的对应逻辑页。
    * 检查页表: 如果页不在缓冲池中，直接返回 `true`。
    * 检查固定计数: 如果页在缓冲池中且 `pin_count_` 大于0，表示正在被使用，返回 `false`。
    * 清理缓冲池: 否则，从 `page_table_` 中移除该页，重置页帧元数据，将其归还到 `free_list_`，并解除固定。

* `bool BufferPoolManager::UnpinPage(page_id_t page_id, bool is_dirty)`:
    * 减少一个页的 `pin_count`。
    * 检查页是否存在: 如果页不在缓冲池中，返回 `false`。
    * 减少引用计数: 减少页的 `pin_count_`。
    * 更新脏状态: 根据 `is_dirty` 参数设置页的 `is_dirty_` 状态。
    * 解除固定: 如果 `pin_count_` 降为0，则调用 `replacer_->Unpin()` 将该页帧重新加入替换器管理队列。

* `bool BufferPoolManager::FlushPage(page_id_t page_id)`:
    * 将指定 `page_id` 的数据页强制写回磁盘。
    * 检查页是否存在: 如果页不在缓冲池中，返回 `false`。
    * 回写脏页: 如果页是脏的，调用 `disk_manager_->WritePage` 将其内容写回磁盘，并将 `is_dirty_` 设置为 `false`。

* `frame_id_t BufferPoolManager::TryToFindFreePage()`:
    * 辅助函数，用于查找一个可用的页帧，优先从 `free_list_` 获取，其次从 `replacer_` 获取。

---
**`lru_replacer.cpp`**

* `bool LRUReplacer::Victim(frame_id_t *frame_id)`:
    * 选择并移除最近最少使用的页帧。
    * 如果 `lru_list_` 为空，返回 `false`。
    * 返回 `lru_list_` 尾部的页帧，并将其从 `lru_list_` 和 `lru_set_` 中移除。

* `void LRUReplacer::Pin(frame_id_t frame_id)`:
    * 将指定的 `frame_id` 从 LRU 替换器中移除，使其不能被替换。
    * 如果 `frame_id` 存在于 `lru_set_` 中，则从 `lru_list_` 和 `lru_set_` 中移除。

* `void LRUReplacer::Unpin(frame_id_t frame_id)`:
    * 将指定的 `frame_id` 加入 LRU 替换器，使其可以被替换。
    * 如果 `frame_id` 不在 `lru_set_` 中，则将其添加到 `lru_list_` 的头部，表示其最近被使用。
    * 如果添加后 `lru_list_` 的大小超过 `capacity_`，则需要淘汰 `lru_list_` 尾部的页帧。

* `size_t LRUReplacer::Size()`:
    * 返回当前 LRU 替换器中可被替换的页帧数量。

---
**`disk_manager.cpp`**

* `DiskManager::DiskManager(const std::string &db_file)`:
    * 构造函数，打开或创建数据库文件，并读取元数据页。

* `void DiskManager::Close()`:
    * 关闭数据库文件，并在关闭前将元数据页写回磁盘。

* `void DiskManager::ReadPage(page_id_t logical_page_id, char *page_data)`:
    * 读取指定逻辑页号的数据页。
    * 内部调用 `MapPageId` 将逻辑页号转换为物理页号，然后调用 `ReadPhysicalPage`。

* `void DiskManager::WritePage(page_id_t logical_page_id, const char *page_data)`:
    * 写入指定逻辑页号的数据页。
    * 内部调用 `MapPageId` 将逻辑页号转换为物理页号，然后调用 `WritePhysicalPage`。

* `page_id_t DiskManager::AllocatePage()`:
    * 从磁盘中分配一个空闲的逻辑页号。
    * 遍历位图页: 查找第一个还有空闲页的区。
    * 新建位图页: 如果所有现有区都已满，则创建一个新的区，这意味着会创建一个新的位图页并将其初始化为空。
    * 分配位图位: 读取对应位图页的内容，调用 `BitmapPage::AllocatePage` 来分配一个位。
    * 更新元数据: 更新 `DiskFileMetaPage` 中已分配页的总数和对应区已使用页的数量，并将位图页写回磁盘。

* `void DiskManager::DeAllocatePage(page_id_t logical_page_id)`:
    * 释放指定逻辑页号的磁盘空间。
    * 计算位图页信息: 根据 `logical_page_id` 计算出对应的位图页的物理地址和在该位图页中的偏移量。
    * 释放位图位: 读取对应的位图页，调用 `BitmapPage::DeAllocatePage` 释放对应的位。
    * 更新元数据: 更新 `DiskFileMetaPage` 中已分配页的总数和对应区已使用页的数量，并将位图页写回磁盘。

* `bool DiskManager::IsPageFree(page_id_t logical_page_id)`:
    * 判断指定逻辑页号是否空闲。
    * 与 `DeAllocatePage` 类似，计算出对应的位图页信息，然后调用 `BitmapPage::IsPageFree`。

* `page_id_t DiskManager::MapPageId(page_id_t logical_page_id)`:
    * 将逻辑页号转换为物理页号。

* `void DiskManager::ReadPhysicalPage(page_id_t physical_page_id, char *page_data)`:
    * 从磁盘读取一个物理页到 `page_data` 缓冲区。
    * 处理文件末尾不足一个页的情况，用零填充剩余部分。

* `void DiskManager::WritePhysicalPage(page_id_t physical_page_id, const char *page_data)`:
    * 将 `page_data` 缓冲区的内容写入磁盘上的一个物理页。
    * 刷新文件流以确保数据写入磁盘。



### `RECORD MANAGER` 模块设计

#### 1、架构设计

`Record Manager` 模块主要负责数据库中数据的存储、管理和访问。它定义了数据在磁盘上的物理布局，并提供了操作这些数据的接口。该模块是数据库存储层的基础，确保了数据的持久性和高效访问。

* **核心组件:**
    * `Column` (列): 描述了表中单个列的元数据，包括列名、数据类型、长度、在表中的索引、是否可空以及是否唯一。
        * 序列化与反序列化: 提供了 `SerializeTo` 和 `DeserializeFrom` 方法，用于将 Column 对象转换为字节流存储到磁盘，以及从字节流中重建 Column 对象。
    * `Row` (行): 代表了数据库表中的一条记录。
        * 字段管理: 内部通过 `Field` 指针数组来维护记录中的各个字段。
        * 序列化与反序列化: `SerializeTo` 将 `Row` 对象及其包含的 `Field` 数据序列化到指定的缓冲区，并利用位图高效处理空值。`DeserializeFrom` 则从缓冲区反序列化数据，重建 `Row` 对象。
        * 记录大小计算: `GetSerializedSize` 计算序列化后的 `Row` 在磁盘上占用的字节数，以便存储管理器能够为其分配合适的空间。
        * 主键提取: `GetKeyFromRow` 根据给定的 `Key Schema` 从当前 `Row` 中提取出作为键的字段，用于索引操作。
    * `Schema` (模式): 定义了数据库表的结构，包含了一组 `Column` 对象。
        * 序列化与反序列化: 提供了 `SerializeTo` 和 `DeserializeFrom` 方法，用于将 `Schema` 对象的元数据存储到磁盘，以及从磁盘加载表结构。
        * 模式大小计算: `GetSerializedSize` 计算序列化后的 `Schema` 在磁盘上占用的字节数。
    * `Field` (字段): 代表了 `Row` 中单个列的数据值。
        * 数据类型封装: 封装了不同数据类型的值，并支持空值。
        * 类型无关操作: 提供了类型无关的序列化、反序列化和比较操作，通过多态性将具体操作委托给 `Type` 类的子类。
    * `Type` (数据类型): 抽象基类，定义了数据库中各种数据类型的通用接口和操作。
        * 多态实现: 具体数据类型继承自 `Type` 类，实现各自的序列化、反序列化、大小计算和比较逻辑。
    * `TableHeap` (表堆): 管理表的所有数据页，支持对表中的记录进行插入、更新、删除和查询。
        * 页面链表: 通过维护一个页面链表来存储 `Row` 数据，每个页面是一个 `TablePage`。
        * 记录操作: 提供了 `InsertTuple`, `UpdateTuple`, `ApplyDelete`, `GetTuple`, `MarkDelete`, `RollbackDelete` 等方法，用于管理表中的记录。
        * 迭代器支持: `Begin` 和 `End` 方法返回 `TableIterator`，支持对表中所有记录的顺序扫描。
        * Buffer Pool Manager交互: 通过 `BufferPoolManager` 来获取、固定和释放数据页。
    * `TableIterator` (表迭代器): 实现了对 `TableHeap` 中记录的遍历功能。
        * 状态管理: 维护当前指向的 `Row` 和所属的 `TableHeap`。
        * 遍历操作: 重载了 `operator++` 和 `operator*` 等操作符，使得可以像遍历标准容器一样遍历表中的记录。

---

#### 2、代码分析

** `column.cpp`**

* **`Column::Column(std::string column_name, TypeId type, uint32_t index, bool nullable, bool unique)`:**
    * 构造函数，用于 `INT` 和 `FLOAT` 类型的列。根据 `type` 自动设置 `len_` 为对应数据类型的大小。
* **`Column::Column(std::string column_name, TypeId type, uint32_t length, uint32_t index, bool nullable, bool unique)`:**
    * 构造函数，专门用于 `CHAR` 类型的列。需要额外指定 `length` 参数。
* **`Column::Column(const Column *other)`:**
    * 拷贝构造函数，用于创建 `Column` 对象的副本。
* **`uint32_t Column::SerializeTo(char *buf) const`:**
    * 将 `Column` 对象的元数据序列化到 `buf` 中。
    * 返回写入的字节数。
* **`uint32_t Column::GetSerializedSize() const`:**
    * 计算 `Column` 对象序列化后所需的总字节数。
* **`static uint32_t Column::DeserializeFrom(char *buf, Column *&column)`:**
    * 从 `buf` 中反序列化数据，重建 `Column` 对象。
    * 首先检查魔数以验证数据完整性。
    * 根据反序列化出的数据类型选择正确的 `Column` 构造函数。
    * 返回读取的字节数。

**`record/row.h` / `record/row.cpp`**

* **`uint32_t Row::SerializeTo(char *buf, Schema *schema) const`:**
    * 将 `Row` 对象中的所有 `Field` 数据序列化到 `buf` 中。
    * 序列化包括字段数量、空值位图和各个非空字段的数据。
    * 返回写入的字节数。
* **`uint32_t Row::DeserializeFrom(char *buf, Schema *schema)`:**
    * 从 `buf` 中反序列化数据，重建 `Row` 对象。
    * 读取字段数量和空值位图，然后根据位图和 `Schema` 信息调用 `Field::DeserializeFrom` 创建 `Field` 对象。
    * 返回读取的字节数。
* **`uint32_t Row::GetSerializedSize(Schema *schema) const`:**
    * 计算 `Row` 对象序列化后所需的总字节数。
* **`void Row::GetKeyFromRow(const Schema *schema, const Schema *key_schema, Row &key_row)`:**
    * 根据 `key_schema` 从当前 `Row` 中提取出对应字段，并构建一个新的 `key_row`。

**`schema.cpp`**

* **`uint32_t Schema::SerializeTo(char *buf) const`:**
    * 将 `Schema` 对象的元数据序列化到 `buf` 中。
    * 返回写入的字节数。
* **`uint32_t Schema::GetSerializedSize() const`:**
    * 计算 `Schema` 对象序列化后所需的总字节数。
* **`static uint32_t Schema::DeserializeFrom(char *buf, Schema *&schema)`:**
    * 从 `buf` 中反序列化数据，重建 `Schema` 对象。
    * 首先检查魔数，然后读取列数量，并循环调用 `Column::DeserializeFrom` 来重建所有 `Column`。
    * 返回读取的字节数。

**`types.cpp`**

* **`Type::type_singletons_[]`:**
    * 静态数组，存储了各种 `Type`（`TypeInt`, `TypeFloat`, `TypeChar`）的单例实例。
* **`uint32_t TypeInt::SerializeTo(const Field &field, char *buf) const`:**
    * 针对 `INT` 类型，将 `Field` 中的整数值序列化到 `buf`。
* **`uint32_t TypeInt::DeserializeFrom(char *storage, Field **field, bool is_null) const`:**
    * 针对 `INT` 类型，从 `storage` 中反序列化整数值，并创建新的 `Field` 对象。
* **`uint32_t TypeInt::GetSerializedSize(const Field &field, bool is_null) const`:**
    * 针对 `INT` 类型，计算序列化后所需字节数。
* **`CmpBool TypeInt::CompareEquals(const Field &left, const Field &right) const`:**
    * 针对 `INT` 类型，比较两个 `Field` 的值。在比较前会检查是否可比较以及是否有空值。
* **`TypeFloat` 和 `TypeChar` 类的比较方法:**
    * 功能与 `TypeInt` 类似，但针对各自的数据类型实现特定的序列化、反序列化和比较逻辑。`TypeChar` 会额外处理字符串长度。

**`table_heap.cpp`**

* **`bool TableHeap::InsertTuple(Row &row, Txn *txn)`:**
    * 向表堆中插入一条 `Row` 记录。
    * 检查 `Row` 大小是否超出页面限制。
    * 遍历页面链表查找有足够空间的 `TablePage`，如果需要则创建新页面并链接。
    * 调用 `TablePage::InsertTuple` 在页面中插入实际数据。
* **`bool TableHeap::UpdateTuple(Row &new_row, const RowId &rid, Txn *txn)`:**
    * 更新指定 `RowId` 的记录。
    * 尝试在原页面更新。如果空间不足，则先 `MarkDelete` 原记录，再 `InsertTuple` 新记录，最后 `ApplyDelete` 物理删除旧记录。
* **`void TableHeap::ApplyDelete(const RowId &rid, Txn *txn)`:**
    * 物理删除指定 `RowId` 的记录，释放其在页面中的空间。
* **`bool TableHeap::GetTuple(Row *row, Txn *txn)`:**
    * 根据 `RowId` 获取指定的 `Row` 记录。
    * 从 `BufferPoolManager` 获取对应页面，并调用 `TablePage::GetTuple` 读取数据。
* **`TableIterator TableHeap::Begin(Txn *txn)`:**
    * 返回一个指向表堆中第一条有效记录的迭代器。
    * 会遍历页面链表直到找到第一条记录。
* **`TableIterator TableHeap::End()`:**
    * 返回一个表示表结束的迭代器。
* **`bool TableHeap::MarkDelete(const RowId &rid, Txn *txn)`:**
    * 标记指定 `RowId` 的记录为逻辑删除。
* **`void TableHeap::RollbackDelete(const RowId &rid, Txn *txn)`:**
    * 回滚对指定 `RowId` 记录的逻辑删除标记。
* **`void TableHeap::DeleteTable(page_id_t page_id)`:**
    * 递归删除表堆中的所有页面，释放占用的磁盘空间。

**`table_iterator.cpp`**

* **`TableIterator::TableIterator(TableHeap *table_heap, RowId rid, Txn *txn)`:**
    * 构造函数，根据给定的 `TableHeap` 和 `RowId` 初始化迭代器。
    * 尝试获取 `RowId` 对应的 `Row` 数据。
* **`TableIterator::TableIterator(const TableIterator &other)`:**
    * 拷贝构造函数，实现对 `current_row_` 的深拷贝。
* **`TableIterator::TableIterator(TableIterator &&other) noexcept`:**
    * 移动构造函数。
* **`TableIterator::~TableIterator()`:**
    * 析构函数，释放 `current_row_` 所占用的内存。
* **`bool TableIterator::operator==(const TableIterator &itr) const`:**
    * 判断两个迭代器是否指向同一条记录或都表示结束。
* **`bool TableIterator::operator!=(const TableIterator &itr) const`:**
    * 判断两个迭代器是否不相等。
* **`const Row &TableIterator::operator*()`:**
    * 解引用操作符，返回当前迭代器指向的 `Row` 对象的引用。
* **`Row *TableIterator::operator->()`:**
    * 成员访问操作符，返回指向当前 `Row` 对象的指针。
* **`TableIterator &TableIterator::operator=(const TableIterator &itr) noexcept`:**
    * 赋值操作符，实现深拷贝。
* **`TableIterator &TableIterator::operator++()`:**
    * 前缀递增操作符。将迭代器前进到下一条有效记录。
    * 如果当前页面没有更多记录，会从 `TableHeap` 获取下一个页面并查找第一条记录。
    * 如果找不到下一条记录，则将迭代器设置为 `End()`。
* **`TableIterator TableIterator::operator++(int)`:**
    * 后缀递增操作符。创建当前迭代器的一个副本，然后递增当前迭代器，并返回之前创建的副本。

---




### `LOCK MANAGER` 模块设计

#### 1、架构设计

`Lock Manager` 模块主要负责数据库中的并发控制，确保事务在访问共享数据时的一致性。它通过实现**两阶段锁协议 (2PL)** 和**死锁检测**来管理事务对数据行的锁请求。

* **LockManager (锁管理器):** 管理行级锁，处理事务的锁请求（S锁、X锁、锁升级）和锁释放，并在发生死锁时进行检测和处理。
    * **两阶段锁 (2PL) 协议:**
        * **增长阶段 (Growing Phase):** 事务可以获取新的锁，但不能释放任何已持有的锁。
        * **收缩阶段 (Shrinking Phase):** 事务可以释放已持有的锁，但不能获取任何新的锁。
    * **锁粒度:** 实现行级锁，每个锁都针对表中的一个特定行。
    * **锁模式:**
        * **共享锁 (S锁):** 允许多个事务并发读取同一行数据。
        * **排他锁 (X锁):** 确保单个事务独占写权限，用于修改数据。
        * **锁升级:** 允许将事务已持有的 S 锁升级为 X 锁，适用于先读后写的场景。
    * **等待图 (Waits-for Graph):** 用于死锁检测。节点为事务ID，有向边 T1→T2 表示 T1 正在等待 T2 释放锁。
    * **死锁检测:**
        * 定期遍历等待图，使用深度优先搜索检测是否存在环。
        * 若检测到环，则选择环中事务ID最大的事务进行回滚。
        * 被回滚事务状态设置为 `kAborted`，并唤醒其等待的所有锁请求。
    * **数据结构:**
        * `lock_table_`: 存储每个 `RowId` 对应的锁请求队列。
        * `latch_`: 保护 `lock_table_` 和 `waits_for_` 的互斥锁。
        * `waits_for_`: 事务等待图。
        * `visited_set_`: DFS 过程中已访问节点的集合。
        * `visited_path_`: DFS 过程中当前遍历路径的栈。
        * `revisited_node_`: DFS 过程中检测到环时重新访问的节点。
        * `enable_cycle_detection_`: 控制死锁检测是否启用的原子标志。
        * `cycle_detection_interval_`: 死锁检测的运行间隔。
        * `txn_mgr_`: 事务管理器的指针，用于协作。

* **LockRequestQueue (锁请求队列):** 为每个被请求锁的 RowId 维护一个队列。
    * `req_list_` (`std::list<LockRequest>`): 存储所有锁请求（包括已授予和等待中的）。
    * `req_list_iter_map_` (`std::unordered_map<txn_id_t, std::list<LockRequest>::iterator>`): 快速查找特定事务的锁请求。
    * `cv_` (`std::condition_variable`): 用于等待和唤醒等待在该 RowId 上的事务。
    * `sharing_cnt_` (`int`): 当前持有共享锁的事务数量。
    * `is_writing_` (`bool`): 是否有事务持有排他锁。
    * `is_upgrading_` (`bool`): 是否有事务正在进行锁升级。

* **TxnManager (事务管理器):** 负责事务的生命周期管理。
    * **与 LockManager 交互:** 在事务提交或中止时，调用`LockManager::ReleaseLocks` 释放事务持有的所有锁。
    * **事务状态:** 维护事务的当前状态（`kGrowing`, `kShrinking`, `kCommitted`, `kAborted`）。


#### 2. 核心流程图示

* **获取锁流程图**

![获取锁流程图](img/lockobtain.png)


* **升级锁流程图**

![升级锁流程图](img/lockupgrade.png)


* **死锁检测与处理流程图**

![死锁检测与处理流程图](img/deadlock.png)


* **2pl流程图**

![2pl流程图](img/2pl.png)



#### 3、代码分析

**`lock_manager.cpp`**

* `void LockManager::SetTxnMgr(TxnManager *txn_mgr)`:
    - 设置指向 `TxnManager` 的指针，便于死锁检测时回调中止事务。

* `bool LockManager::LockShared(Txn *txn, const RowId &rid)`:
    - 申请共享锁（S锁）。
    - 检查事务状态和隔离级别，获取/创建对应的锁队列。
    - 若有排他锁或锁升级正在进行，则进入等待，并更新等待图。
    - 死锁检测期间若事务被中止，则清理并返回 `false`。
    - 成功后标记为已授予，更新计数，并将 RowId 加入事务的 S锁集合。

* `bool LockManager::LockExclusive(Txn *txn, const RowId &rid)`:
    - 申请排他锁（X锁）。
    - 检查事务状态，获取/创建锁队列。
    - 若有其他锁或锁升级正在进行，则进入等待，并更新等待图。
    - 死锁检测期间若事务被中止，则清理并返回 `false`。
    - 成功后标记为已授予，设置写标志，更新事务锁集合。

* `bool LockManager::LockUpgrade(Txn *txn, const RowId &rid)`:
    - S锁升级为X锁。
    - 检查事务状态和是否持有S锁，若有其他事务正在升级则回滚当前事务。
    - 设置升级标志，等待其他锁释放，期间更新等待图。
    - 死锁检测期间若事务被中止则清理并返回 `false`。
    - 成功后取消升级标志，修改请求模式，更新计数和事务锁集合，并唤醒等待队列。

* `bool LockManager::Unlock(Txn *txn, const RowId &rid)`:
    - 释放事务持有的 S锁或 X锁。
    - 更新锁队列状态，移除事务锁请求。
    - 若事务处于增长阶段，则切换为收缩阶段。
    - 从等待图中删除相关边，唤醒等待队列。

* `void LockManager::AddEdge(txn_id_t t1, txn_id_t t2)`:
    - 在等待图中添加一条从 t1 到 t2 的有向边。

* `void LockManager::RemoveEdge(txn_id_t t1, txn_id_t t2)`:
    - 移除等待图中的一条边，若 t1 无其他等待则移除节点。

* `bool LockManager::HasCycle(txn_id_t &max_tid)`:
    - 使用 DFS 检测等待图中是否存在环（死锁）。
    - 若有环，返回环中最大事务ID。

* `void LockManager::DeleteNode(txn_id_t txn_id)`:
    - 从等待图中删除指定事务相关的节点和所有边。

* `void LockManager::RunCycleDetection()`:
    - 独立线程定期运行死锁检测。
    - 检测到死锁时中止最大ID事务，并唤醒相关等待队列。

* `void LockManager::LockPrepare(Txn *txn, const RowId &rid)`:
    - 事务进入等待前，根据当前锁队列已授予的锁，构建等待图的边。

* `void LockManager::CheckAbort(Txn *txn, LockManager::LockRequestQueue &req_queue)`:
    - 该函数为空，通过 txn->GetState() == TxnState::kAborted 检查替代其功能。

* `std::vector<std::pair<txn_id_t, txn_id_t>> LockManager::GetEdgeList()`:
    - 仅用于测试，返回等待图中所有边的列表。


## 四、 实验结果展示


- 运行`minisql_test`：
![alt text](img/image4.png)
![alt text](img/image5.png)
![alt text](img/image6.png)

</br>

- 进行`main`函数整体运行结果见小组总体设计报告