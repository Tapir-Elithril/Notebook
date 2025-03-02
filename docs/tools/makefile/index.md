# Makefile

!!! note "参考[makefile介绍](https://seisman.github.io/how-to-write-makefile/introduction.html)"  

## Introduction  
GNU Make 是一个用于自动化编译的工具，它通过读取 Makefile 文件中的规则来执行编译过程。Makefile 文件中包含了一系列的规则，描述了源文件之间的依赖关系，以及如何编译和链接这些源文件。(来自sys2-lab4)  
## 语法
### 基本格式  
```makefile
target ... : prerequisites ...
    recipe
    ...
    ...
# 指令内容前一定要使用tab缩进，不能使用空格
# \表示换行 方便阅读使用

main.o: main.c
    gcc -c main.c -o main.o
```
target:目标文件(obj file)  
prerequisite:依赖  
recipe:命令  
### target构建  
```makefile
C_SRC := $(wildcard *.c)
ASM_SRC := $(wildcard *.S)
OBJ := $(C_SRC:.c=.o) $(ASM_SRC:.S=.o)
```
使用wildcard自动匹配所有相同名称类型的文件，将目标对象赋值给OBJ  
### 定义变量
```makefile
CC = gcc
CFLAGS = -c
CPPFLAGS := -I$(CURDIR)/../include # 依赖的位置
```
定义变量来存储编译器、编译选项等，提高代码的可维护性  
**自动变量**：  
$@: 目标文件名  
$<: 第一个依赖文件 
$^: 所有依赖文件（去重）  
例如：  
```makefile
%.o: %.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<
# $< : %.c
# $@ : %.o
# gcc -c -I./../include -c %.c
```

### 伪目标
不生成同名文件，仅用于执行命令的操作，用`.PHONY`标记  
常见标记：
```makefile
.PHONY: clean all

all:$(OBJ)
# 执行make all编译产生所有OBJ文件，all本身不是一个要创建的文件

clean:
	rm -f *.o
```
### 路径传递
变量可以在多个文件夹的makefile之间传递(使用export)，一个具体的示例如下:  
对于以下目录结构  
```text linenums="0"
.
├── kernel
│   ├── Makefile
│   ├── arch
│   │   └── riscv
│   │       ├── Makefile
│   │       ├── include
│   │       │   ├── mm.h
│   │       │   ├── print.h
│   │       │   ├── printk.h
│   │       │   ├── private_kdefs.h
│   │       │   ├── proc.h
│   │       │   └── sbi.h
│   │       └── kernel
│   │           ├── Makefile
│   │           ├── clock.c
│   │           ├── entry.S
│   │           ├── head.S
│   │           ├── main.c
│   │           ├── mm.c
│   │           ├── printk.c
│   │           ├── proc.c
│   │           ├── sbi.c
│   │           ├── trap.c
│   │           └── vmlinux.lds
│   ├── include
│   │   ├── ctype.h
│   │   ├── inttypes.h
│   │   ├── limits.h
│   │   ├── riscv-asm.h
│   │   ├── stdarg.h
│   │   ├── stddef.h
│   │   ├── stdint.h
│   │   ├── stdio.h
│   │   ├── stdlib.h
└── └── └── string.h
    
```

```makefile
# In ./kernel/Makefile:
CROSS_ := riscv64-linux-gnu-
export GCC := $(CROSS_)gcc
export LD := $(CROSS_)ld
export OBJCOPY := $(CROSS_)objcopy
export OBJDUMP := $(CROSS_)objdump
export NM := $(CROSS_)nm

ISA := rv64ia_zicsr_zifencei
ABI := lp64

export CPPFLAGS := -I$(CURDIR)/include
export CFLAGS := -march=$(ISA) -mabi=$(ABI) -mcmodel=medany \
	-ffreestanding -fno-builtin -ffunction-sections -fdata-sections \
	-nostartfiles -nostdlib -nostdinc -static -ggdb -Og \
	-Wall -Wextra -std=gnu11
export LDFLAGS := -lgcc -Wl,--nmagic -Wl,--gc-sections
# In ./kernel/arch/riscv/Makefile:
CPPFLAGS += -I$(CURDIR)/include
# In ./kernel/arch/riscv/kernel/Makefile:
%.o: %.S
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c $<

%.o: %.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<
```