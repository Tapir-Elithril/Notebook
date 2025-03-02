# 单周期CPU设计指导
!!! danger "不要抄袭 不要抄袭 不要抄袭"

[指令集手册](指令集手册.pdf)  
单周期CPU设计最大的困难在于理论的匮乏与例子的缺少，因此以下会补充一些单周期CPU设计相关的理论并以R-Type为例给出单周期CPU设计的方式  
## 单周期CPU相关理论
### RISCV指令集架构
To be implemented
### CPU组成
![数据通路图](image.png)
CPU的数据通路图如上，本质上Core.sv中需要完成的就是线路的连接，而Controller.sv即Control Logic，根据指令(inst)输出对应选择的控制信号  

To be implemented
### 指令执行阶段
指令执行分为五个阶段，具体为：

- IF(Instruction Fetch)  
- ID(Instruction Decode)  
- EX(Execute)  
- MEM(Memory)  
- WB(Write Back)  
  
## R-Type数据通路与控制器设计
To be implemented
### 调试与运行
1.语法错误
常见语法错误
illegal assignment to wire,perhaps intended var
2.`make wave`仿真测试
To be implemented