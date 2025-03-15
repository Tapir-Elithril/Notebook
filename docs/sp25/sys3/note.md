# 计算机系统III
## 体系结构  
### Fundamentals of computer system Week1
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

### Instruction-Level Parallelism(ILP) Week2 - 3 
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
note that register status can be read from function component table,register status table is created just for convenience.  

In-class practice:
![alt text](bfe71aabcb33516540fb13d8f421b2f.jpg)

##### Tomasulo  
Tomasulo's approach is to introduce **register renaming** in hardware to minimize WAW and WAR hazards.  
```asm
1.LD  F6,34(R2) 
2.LD  F2,45(R3) 
3.MUL F0,F2,F4  
4.SUB F8,F6,F2
5.DIV F10,F0,F6
6.ADD F6,F8,F2
```
Reservation Station(RS保留站):防止因硬件冲突导致指令无法流入(上例中的4.SUB与6.ADD),在RS中执行乱序  
Command Data Bus(CDB):将指令需要的值替换为保留站的结果(6.ADD中F8的值即为adder RS的结果,保留站的名称替代了寄存器的名称),通过广播的方式使结果分布控制  
执行阶段简化为IS,EX,WB三阶段,没有解决顺序写回的问题  
IS:检查保留站是否还有空位 
EX:保留站中乱序执行,如果操作数未全部ready则等待,操作数已经ready的先执行  
WB:CDB同时将结果写入寄存器和需要的RS  
Register status Qi记录寄存器与RS的对应关系  
Instruction status table,Function component status table,Register status table(Field Qi) are still needed.

Limitation:

- Structual complexity  
- performance limited by Common Data Bus  
- correctness not guaranteed  
  
The limitations on ILP approaches directly led to the movement to multicore.

In-class practice:
![alt text](73594853addbe984fa7f1755da7374b.png)

Instructions come out in order:Waiting sofa(buffer)

#### Hardware-Based Speculation 硬件前瞻
Reorder buffer(ROB) before writing back to registers
extend the stages of every instruction into:IS,EX,WB,Commit  
Commit:In-order write back —— the key of speculation  

- Function component status table:ROB No. in column dest in  
- ROB table:the current stages of the relevant instructions  
- Register status table:ROB row shows the registers to be written and the corresponding ROB No.
  
In-class practice:前三列同Tomasulo  
Commit列:5,6,17,18,58,59  

!!! danger "60个周期的表格变化，每个格子会填会算"  

- Precise exception  
- easily extend to other(e.g. integer)units  
- complex hardware(CDB)  
  
#### Exploiting ILP Using Multiple Issue and Static Scheduling  

- n-issue Superscalar  
- VLIW  
- Super pipeline  
  
Dynamic scheduling is more dependent on hardware,while static scheduling may not.  

Multi-issue based on dynamic scheduling:
双流入流出Tomasulo:  
![alt text](image-9.png)  
bottleneck:data-dependent branches & ALU
With Speculation:  
![alt text](image-10.png)  
前瞻执行：不需要等待分支结果，因为不一定要提交  
Branches are a critical performance limiter(especially with data-dependent ones),but speculation helps.  
##### VLIW
operation slots  
parallel execution in EX  
```asm
Loop:fld    f0,0(x1)
     fadd.d f4,f0,f2
     fsd    f4,0(x1)
     addi   x1,x1,-8
     bne    x1,x2,Loop
```
指令乱序/循环展开

- code length increases  
- lockstep mechanism  
- machine code incompability  

##### Superpipeline
IF IS RF EX (DF DS TC) WB

### Memory Hierarchy(Cache) Week4 - 5  
#### Introduction

- Registers  
- Cache  
- Memory  
- Storage  
  
  
- Mechanical memory  
- Electronic memory  
  SRAM:static random access memory(Cache)
  DRAM:dynamic ~(Main memory)
    DDR2(double data rate上升沿和下降沿都能传数据),DDR3,DDRSDRAM
  Flash
  ROM:read-only memory
    PROM,EPROM
- Optical memory
  
Temporal/Spatial locality时空局部性  

Cache:a safe place for hiding or storing things.  

hit/miss:whether the processor can or cannot find a requested data in the cache  
hit rate/miss rate/hit time/miss penalty  

Block run:A fixed-size collection of data containing the data we need retrieved from the memory  
Spatial locality:likely need other data within the same block soon  

#### Technology Trend
SRAM
DRAM
SDRAM(Synchronous DRAM)
DDR SDRAM
HBM:High Bandwidth Memory DRAM
SSD
HDD/TAPE

#### Memory Hierarchy
##### Cache Miss
Latency:the time to retrieve the first word of the book  
Bandwidth:the time to retrieve the rest of the book  

Miss causes  

- Compulsory:first reference(cache is empty)  
- Capacity:blocks discarded and later retrieved  
- Conflict:program makes repeated references to multiple addresses from different blocks that map to the same location in the cache  

desktop users:average latency  
server:memory bandwidth(multiple users)  
embedded:power and battery life/real-time response/small memory  

Everything is a cache.  
Registers -> L1-Cache -> L2-Cache -> Memory -> Disk  

Cache Size = Block Size * Sets + Related info(Indexes)

#### Cache Design
##### 1.Where can a block be placed in the upper level?(Block placement)
###### Direct mapped
(Block address) modulo (Number of blocks in the cache):循环分配  
e.g.Cache number = 8(0-7)   
Memory 1,9,17,25 -> Cache 1  
[Problem]low space usage & high conflict probability  
###### Fully associative
Block can go anywhere in cache  
###### n-way Set associative
Each memory block maps to a cache group(n cache blocks in each group) and put memory block into certain cache block in casual  
for most caches:n <= 4

##### 2.How is a block found if it is in the upper level?(Block Identification)
Every block has an address tag that stores the main memory address of the data stored in the block 
valid bit  
index selects the set/block
direct map:tag + set index + offset  
hit if valid_bit == 1'b1 && tag == mem_addr  

##### 3.Which block should be replaced on a cache/main memory miss?(Block Replacement)
Random,LRU,FIFO

##### 4.What happens on a write?(Write Strategy)
Write Back or Write Through(with Write Buffer)

#### Memory System Performance

#### *Storage Systems



## OS  
### Main Memory Week7 - 10

### File System Week11 - 14

### DLP,TLP Week15

## Final Review Week16
