SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
OUT = test

INCLUDES = -I.

# 区分 Debug 和 Release 标志
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG -march=native

# 默认使用 Release 模式
BUILD_MODE ?= release

ifeq ($(BUILD_MODE),debug)
    CXXFLAGS = $(INCLUDES) $(DEBUG_FLAGS)
else
    CXXFLAGS = $(INCLUDES) $(RELEASE_FLAGS)
endif

all: $(OUT)

$(OUT): $(OBJ)
	g++ $(OBJ) -o $(OUT) $(CXXFLAGS)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

# 添加不同的构建目标
debug:
	$(MAKE) BUILD_MODE=debug

release:
	$(MAKE) BUILD_MODE=release

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all debug release run clean