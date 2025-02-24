<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
<div align=center>
    <font size=20 face=黑体>
数据库系统<br/><br/> Lab2:SQL数据定义和操作
    </font>
    <font size=5 face=楷体>
<br/><br/>
杨亿酬 3230105697<br/>
2025-2-21 - 2025-
    </font>
</div>

<div STYLE="page-break-after: always;"></div>

### 1.实验目的  

- 掌握关系数据库语言SQL的使用  
- 使所有的SQL作业都能上机通过  
  
### 2.定义列表  

(1)创建书book表  
![alt text](image.png)  
将bno设置为主键并保存  

(2)创建借书卡card表   
```sql
CREATE TABLE card( //CREATE函数创建新表）
	cno char(7) NOT NULL,//name type NOT NULL创建不可为空的列
	name varchar(10) NOT NULL,
	department varchar(40),
	type char(1) CHECK (type in('T','G','U','O')),//CHECK(type in())设置分类选项
	CONSTRAINT PK_card PRIMARY key(cno)//CONSTRAINT设置主键
);
```

(3)创建借书记录borrow表  
```sql
CREATE TABLE borrow(
    cno char(7) NOT NULL,
    bno char(8) NOT NULL,
    borrow_date datetime NOT NULL,
    return_date datetime NOT NULL,
    CONSTRAINT PK_borrow PRIMARY key(cno,bno) //cno,bno联合主键
);
```

### 3.创建数据库表，并输入必要的样本数据(>100种)  

```sql
INSERT INTO book (bno, category, title, press, year, author, price, total, stock)
VALUES
('','','','','','','','','')
...
```

