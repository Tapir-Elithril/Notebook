# 数据库系统

## Chap 1 Introduction

### 1.2 Definition
[Definition] Database:a collection of **interrelated**/integrated and persistent data  
[Definition] Database Management System(DBMS):A set of programs used to access,update and manage the database  
Properties of DBMS:  

- efficiency and scalability(可扩展性)  
- independency(physical/logical)  
- integrity(完整性) and security  
- concurrent(并发) access and robustness(鲁棒性)(recovery)  
  
### 1.4 Levels of data abstraction  

- Physical level:files  
- Logical level:relationship  
- View level:details of data viewed by the users(detail hidden) e.g. age for course selection  

![alt text](image.png)  
**schemas(模式) and instances(实例)**  
schema:the structure on different level(Physical/Logical/Sub-schema)(表头)  
instance:the actual content  
  
**Independence**  

- Physical:change of logical schema rarely affects the physical schema(unless some data are missed)
- Logical:harder to achieve since the view schema are strongly influenced by the logical schema(change of logical scheme immediately change the data in the view scheme)  

### 1.5 Data models
[Definition] Data model:a collection of conceptual tools for describing——data structure/relationship/semantic(语义)/constraint  
Different types:  

- Entity(object)-Relationship model(E-R)  
- Relational model  
- Object-oriented model  
- Semistructured data model (XML)  
  
![alt text](image-1.png)

![alt text](image-2.png)

### 1.6 Database Language  

- Data definition language(DDL)  
- Data manipulation language(DML)  
- Data control language(DCL)  
  
(1)DDL  
generate tables stored in data dictionary  
```sql
CREATE TABLE account(
    account_number char(10),
    balance integer
);
```
[Definition] Data dictionary:metadata(the data of data) including——database schema,data structure,access methods and constraints,statistical info,authorization
(2)DML  
Insert/Delete/Update/Retrieve data  
query language
(3)SQL(DDL+DML+DCL)  
```sql
SELECT account.balance
FROM depositor,account
WHERE depositor.customer-id = '192-83-7465' and depositor.account-number = account.account-number
//不同表之间的对应
```

### 1.7 Database Users  

- naive users:interface interact  
- application programmer:SQL calls  
- sophisticated users:analytical processing/data mining  
- specialized users

### 1.8 Database Administrator(DBA)  
a good understanding of the enterprise's info resources and needs

### 1.9 Transaction(operation) Management(事务管理)  

atomicity,consistence,isolation,durability(ACID)  
concurrency-control manager(并发控制管理器)  

### 1.10 DBMS structure  
1.storage manager  
responsible for efficient storing,retrieving,updating data  

2.query processor
DDL interpreter,DML compiler,query processing  
query -> parser and translator -> relational algebra expression -> **optimizer** -> execution plan -> evaluation engine -> output  
Optimization:cost estimation  

Application architectures:  
two-tier:app -> db  
three-tier:browser -> web -> db  

## Chap 2 Relational Model  

### 2.1 Definition
[Definition] relation:a table with rows and columns  
[Comparison] relationship:an association among several entities  

### 2.2 Basic Structure  
given sets D<sub>1</sub>,...,D<sub>n</sub>  
a relation *r* is a subset of D<sub>1</sub> x ... x D<sub>n</sub>(Cartesian product)  
e.g.dept_name = {Biology,Finance,History,Music}  
building = {Watson,Painter,Packard}  
budget = {50000,80000,90000,120000}  
Then r = {(Biology,Watson,90000),(Finance,Painter,120000),(History,Painter,50000),(Music,Packard,80000)}is a relation over dept_name x building x budget(total 48 tuples)  
(1)Attribute Types  
domain:the set of allowed values(atomic) of each attribute(属性，表头的元素)  
non-atomic value:multivalued/composite(混合的) attribute  
e.g.tel:138xxx,139xxx(a string difficult to split)  
null:a member of every domain  
(2)Concepts  
relation schema:the structure of the relation  
e.g.(ID=string,name=string,salary=int)  
R=(A<sub>1</sub>,...,A<sub>n</sub>) is a relation schema where A<sub>i</sub> is an attribute  
relation instance:the snapshot of data in the relation  
![alt text](image-3.png)  
(3)Relations are unordered
(4)Keys  
唯一区分一个对象的一个或一些属性  
superkey:a set of attribute sufficient enough to identify a unique tuple  
candidate key:minimal superkey(cannot delete anyone)  
primary key:candidate key defined by user  
(5)Foreign key  
Assume there exists relation r and s: r(A, B, C), s(B, D), we can say that attribute B in relation r is foreign key  
参照关系中外码的值必须在被参照关系中实际存在或为null(不能填不存在的值，如填入一个不存在的专业)  
(6)
