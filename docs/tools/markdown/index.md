# Markdown 常用语法
## 基本格式
```
切换输入模式(vscode):小键盘0
<space><space><\n> # 换行
</br> # 强制换行
<div STYLE="page-break-after: always;"></div> # 换页
<div style="text-align: left;">
  这是左对齐的内容。
</div>

<div style="text-align: center;">
  这是居中的内容。
</div>

<div style="text-align: right;">
  这是右对齐的内容。
</div>

<div style="text-align: justify;">
  这是两端对齐的内容。
</div>
    <font size=<字体大小(数字)> face=<字体名称>>
    ...
    </font>
</div>
```
## 标题
```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```
## 强调
```
*斜体* or _斜体_
**粗体** or __粗体__
***粗斜体***
```
## 列表
```
//无序列表
- 项目1
- 项目2
  - 子项目1
  - 子项目2
//有序列表
1.项目1
2.项目2
    1.子项目1
    2.子项目2
```
## 链接
```
[链接文本](链接地址)
[Google](https://www.google.com) //网址
![图片描述](../../../image/image.png) //图片
```
## 引用
```
> This is a quote.
```
> "The only way to do great work is to love what you do."  
> — Steve Jobs
## 代码
```
这是一个 `行内代码`
显然这段文字已经在一个代码块中了
支持语言：py,js,html,css,java,c,cpp,ruby,php,sql,bash(sh),json,yaml,r,go,markdown
```
## 表格
| 表头1 | 表头2 | 表头3 |
|-------|-------|-------|
| 内容1 | 内容2 | 内容3 |
| 内容4 | 内容5 | 内容6 |  

## 转义字符
```
\*这不是斜体\*
```
\*这不是斜体\*
