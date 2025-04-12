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
CREATE TABLE card( //CREATE函数创建新表
	cno char(7) NOT NULL,--name type NOT NULL创建不可为空的列
	name varchar(10) NOT NULL,
	department varchar(40),
	type char(1) CHECK (type in('T','G','U','O')),--CHECK(type in())设置分类选项
	CONSTRAINT PK_card PRIMARY key(cno)--CONSTRAINT设置主键
);
```

(3)创建借书记录borrow表  
```sql
CREATE TABLE borrow(
    cno char(7) NOT NULL,
    bno char(8) NOT NULL,
    borrow_date datetime NOT NULL,
    return_date datetime NOT NULL,
    -- CONSTRAINT PK_borrow PRIMARY key(cno,bno) 不设置主键，否则无法重复插入
);
```

### 3.创建数据库表，并输入必要的样本数据(>100种)  

```sql
INSERT INTO book (bno, category, title, press, year, author, price, total, stock)
VALUES
('','','','','','','','',''),
...
```
使用LLM生成数据，对三张表各插入100种数据
```sql
select count(*) as row_count from <table>
-- 确认插入100种样本数据
```

### 4.用SQL实现以下查询  
1. 求总藏书量、藏书总金额，总库存册数、最高价、最低价。
![alt text](image-1.png)
2. 列出藏书在10本以上的书（书名、作者、出版社、年份，库存量）。
![alt text](image-2.png)
3. 哪些出版社的藏书种类数超过100种。
由于插入数据数量有限，超过100种的出版社数量为0，用超过1种的出版社检测语句正确性
![alt text](image-3.png) 
![alt text](image-4.png)
   
4. 目前实际已借出多少册书？
   假设藏书量 - 库存量 = 借出量 
![alt text](image-5.png)
   
5. 列出出版年份最久远的书。
![alt text](image-6.png)

6. “数据库系统原理教程，王珊编著，清华大学出版社，1998年出版”还有几本？
![alt text](image-7.png)   

7. 哪本借书证未归还的图书最多？ 
![alt text](image-10.png)
note:sql server要求子查询必须有别名

8. 求平均每本借书证的借书册数。
![alt text](image-9.png)   

9. 哪个系的同学平均借书册数最多？
![alt text](image-14.png)
```sql
select department from
(
	select 
		card.department, 
		count(card.cno) as student_number, 
		count(case when borrow.cno is not null then 1 end) as borrow_number,
		cast(count(case when borrow.cno is not null then 1 end) as float) / 
		nullif(count(card.cno), 0) as average
	from
		card
	left join
		borrow on card.cno = borrow.cno
	group by 
		card.department
		) 
as subquery
where average = (select max(average) from 
(
	select 
		cast(count(case when borrow.cno is not null then 1 end) as float) / 
		nullif(count(card.cno), 0) as average
	from
		card
	left join
		borrow on card.cno = borrow.cno
	group by 
		card.department
) as inner_query
);
```

10. 最近两年都未被借过的书。
![alt text](image-15.png)
    
11. 列出那些借了图书逾期未归还的借书证号和图书名，并算出相应的罚金（假设罚金按书价的0.1％/每天 计算）。
设置从还书日期 - 结束日期超过21天为逾期
![alt text](image-16.png)
    
12.  列出从未借过书的借书证。
![alt text](image-13.png)

13.  列出去年出借数量最多的5种图书。
![alt text](image-11.png)
    
14.  正常情况下，每种图书的总藏量与库存量之差应等于该图书借出后未归还的数量，否则是一种异常情况。请找出存在这种异常情况的图书。
![alt text](image-12.png)