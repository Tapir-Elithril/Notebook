# 计算机系统III
## 体系结构  
### Fundamentals of computer system Week1 - 2
Classes of computers(by Flynn)  

- SISD(single instruction single data stream):only in theory  
- SIMD(multiple):commonly used  
- MISD:only in theory  
- MIMD:current CPU  
  
Classes of computers(in textbook)  

- desktop/personal  
- server:服务器 security  
- embedded:嵌入式 immediate response  
- personal mobile  
- supercomputer(peak performance + electricity -> cooling)  
  
**Performance**  
The performance(time) can be affected by:  

- Algorithm(time complexity)  
- Programming language,compiler,architecture  
- Processor and memory  
- I/O,OS  
  
**Measuring performance**  
- Single users on a PC  
    minimization of response time   
    minimization of execution time  
- Large data  
    maximization of TP  
- Response time  
- Execution time(CPU time)  
    comprises of user CPU (execution) time and system CPU time  
  
$Performance = \frac{1}{Execution Time}$  
If X is *n* times faster than Y,then $\frac{Performance_X}{Performance_Y} = \frac{Execution Time_Y}{Execution Time_X} = n$

#### 系统量化研究方法 Quantitative approach 
**CPU Performance** 
$CPU\ Execution\ Time = CPU\ Clock\ Cycles * Clock\ Period$  
$CPU\ Execution\ Time = \frac{CPU\ Clock\ Cycles}{Clock\ Rate(freq)}$  
Performance improvement by  

- reduce number of clock cycles  
- increase clock rate  
- trade off clock rate against cycle count  
  
Average cycles per instruction(CPI)  
$CPI = \frac{CPU\ Clock\ Cycles}{Instruction\ Count}$  
![alt text](image.png)  
$CPU\ time = \frac{Instructions}{Program}*\frac{Clock\ Cycles}{Instructions}*\frac{Seconds}{Clock\ Cycles}$  

#### Amdahl's Law(性能优化)  
$Improved\ Execution\ Time = \frac{Affected\ Execution\ Time}{Amount\ of\ Improvement} + Unaffected\ Execution\ Time$  
$T_{improved}=\frac{T_{affected}}{improvement\ factor} + T_{unaffected}$  

局部加速比:improvement factor  
$Speedup_{overall} = \frac{Performance\ for\ entire\ task_{using\ enhancement}}{Performance\ for\ entire\ task_{without\ enhancement}}= \frac{Total\ Execution\ Time_{without\ enhancement}}{Total\ Execution\ Time_{using\ enhancement}}$  

改进比例:$fraction = \frac{Time\ can\ be\ improved}{Total\ Execution\ Time}$ 
![alt text](image-1.png)
$Speedup_{overall} < \frac{1}{1-Fraction_{enhanced}}$

#### Great Architecture Ideas  

- Moore's law:number of transistors doubles every 18-24 months  
- Use abstraction to simplify design  
- Make the common case fast  
- Improve performance via parallelism  
- Improve performance via pipelining  
- Improve performance via prediction  
- Use a hierarchy(分级) of memories  
- Improve dependability(可靠性) via redundancy(备份)  
  
Below the program:  

- parallel nature of processors  
- hierarchical nature of memories  
- compiler decisions  

### Instruction-Level Parallelism(ILP) Week2  
Dependencies  

- Data dependence(RAW-read after write)
- Name dependence:rename
```asm
DIV F2,F6,F4
ADD F6,F0,F12
SUB F8,F6,F14
//anti-dependence(WAR)
DIV F2,F6,F4
ADD S,F0,F12
SUB F8,S,F14
```
```asm
DIV F2,F6,F4
ADD F6,F0,F12
SUB F2,F6,F14
//output-dependence(WAW)
DIV F2,F0,F4
ADD F6,F0,F12
SUB S,F6,F14
```
- Control dependence:Branch hazards  
  
![alt text](image-3.png)  
  
Hazard  

- Structure hazard:add hardware
- Data hazard:Forwarding + stall/scheduling  
- Control hazard:branch prediction  
  
#### Branch prediction  

- static:任选
- dynamic:BTB

Delay slot:forbidden by RISC-V due to prediction  

Dynamic branch prediction  
1.Branch History Table(BHT):2-Bit predictor  
2.Instruction/Data-read/Data-write buffer(Branch-Target Buffer(BTB) in prediction)  
![alt text](image-2.png)  

#### Dynamic Scheduling  
simple pipelining has the limitation:  

In-order
```asm
DIV F4,F0,F2
SUB F10,F4,F6
ADD F12,F6,F14//waiting without data dependencies
```
##### Scoreboard  
Scoreboard algorithm is an approach to schedule the instructions.  

recall:hazard detection in ID  
split ID into two parts:IS(issue) & RO(read operands)  
IS:check structural hazards(in-order)  
RO:check data hazards(out of order)  
cannot flow to IS/RO if a certain hazard exists  
```asm
1.LD  F6,34(R2) //integer unit
//assume the first inst has been completed
2.LD  F2,45(R3) //integer unit structural hazard
3.MUL F0,F2,F4  //F2 F8 F0 F6 data hazard
4.SUB F8,F6,F2
5.DIV F10,F0,F6
6.ADD F6,F8,F2
```

info table design  

- Instruction status table  
![alt text](image-5.png)
- Function component status table  
![alt text](image-7.png)
只有在某条指令执行WB后清空该指令使用的部件的一行，下一个要使用这一部件的指令才能进入IS阶段  
- Register status table
![alt text](image-8.png)
note that register status can be read from function component table,register status table is created just for convenience  

In-class practice:
![alt text](bfe71aabcb33516540fb13d8f421b2f.jpg)

##### Tomasulo  
Tomasulo's approach is to introduce register renaming in hardware to minimize WAW and WAR hazards.  

### Memory Hierarchy(Cache)  


## OS  
### Memory Hierarchy(Main Memory)  

### File System  

### DLP,TLP  

## Final Review  
