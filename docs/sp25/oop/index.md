# 面向对象程序设计  2.5 学分

## 授课教师
~~许威威~~翁恺

### 认定
专业基础课

### 分数构成
- 平时成绩50%：7次作业  
- 期末考试50%： 
  - 选择题：10*2'  
  - 程序输出题：30'  
  - 程序填空题：30'  
  - 编程/设计题：20'  

### 学习建议
到课人数过少点过一次名，对名单一个个叫名字，可以下课补签，感觉对总评没影响  
7次作业按照学在浙大设置的截止时间提交，需要注意课上可能会提到的特殊要求（翻看智云）  
以下列出一些本人踩过的坑┭┮﹏┭┮：  
Student2 -1：  
Each student can take an arbitrary number of courses. Each record consists of the course id/name and the score the student got.  

Your course number is limited to 9("Chinese", "Math" , "English", "Physics", "Chemistry", "Biology", "History", "Politics" , "Geography"). Try to use map<string, int> to store student course-score pairs.   

eg input file:  
studentA ads 93 oop 91 fds 79  

studentB cg 87 bs 92 os 88  
Fraction -3:  
创建 4/-8 输出流未约分 符号不在最前  
大作业在g++ -std=c++17 -Wall -O0 -march=native -o main xxx.cpp指令编译测试。  
主要针对大量小内存动态分配测试，取100次运行时间的均值来排序。  
对于因为提前申请较大内存或使用较大块导致的速度下降，已在评测中相应调整。  
最终按照运行时间排序，并辅以报告和代码质量评估，在[48, 60]区间内分配成绩。  
xww班级的平时任务是最少的，所以仍然建议选择，并听wk/cx的智云  
注意考试范围是各个老师讲授内容的并集（注意某些老师可能不会讲的`namespace`,`cast`）  
期末考试设计题为在pta主观题文本框里写markdown，不编译，不测试，比较简单，注意不要漏掉`const`，`override`等关键字  
期末考试看似简单但得高分难度不小，本人一度认为批改有问题呜呜，考察比较细且坑很多，程序填空有`const`建议填上  