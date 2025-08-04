# 计算机系统III  5.5学分
## 授课教师
~~吴磊~~ 常瑞/周亚金

### 认定
专业基础课

### 分数构成
作业 10%  
  - cache相关计算  
  - cache性能优化的presentation  
实验 60%  
  - Lab1 BHT&BTB 8%  
  - Lab2 Cache Design 8%  
  - Lab3 Virtual Memory 8%  
  - Lab4 User Mode 8%  
  - Lab5 Page fault and fork system call 10%  
  - Lab6 Hardware support page fault and MMU 10%  
  - Project Xpart 8%(超出部分以非等值的形式记入bonus)  
-------total <= 70---------
- 期末 30%  
  单选：15 * 2% = 30%  
  Q&A：70%  

### 学习建议
相比与sys1与sys2，sys3的难度更高，工作量更大，因此需要额外重视  
只有硬件有一次作业和一个cache性能优化的展示，软件部分有许多quiz甚至随堂测试，但不计入总评分数，只是作为练习  
实验中Lab1，2，6为硬件实验，Lab3，4，5为软件实验，难度上：Lab2 >>>>> Lab5,xpart > Lab6 > Lab1,3,4  
xpart的验收采用presentation的形式，不需要跑代码，只需要制作ppt然后讲清楚工作量（，并应对一些提问）即可  
Lab2是整个系统贯通课最难的实验，可能需要大改（重写）硬件框架，预计完成时间可能需要达到50小时以上（通过`verilate_sort`测试可以获得60%的分数），需要更多地请教助教  
OS部分的实验包括思考题需要额外关注细节，即使运行正确也要注意是否会有寄存器信息丢失，csr寄存器都起到了什么作用  
期末考试大题包括：tomasulo+硬件前瞻的填表、MSI protocol、Virtual Memory（Sv39的地址翻译）、File System  

[Homework](homework-1.pdf)  