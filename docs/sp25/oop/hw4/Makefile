CXX = g++
INCLUDES = -I.
CXXFLAGS = $(INCLUDES) -std=c++17 -Wall -pipe
EXECUTABLES = pdadd.exe pdlist.exe pdshow.exe pdremove.exe
PROGRAM_DIR = program

PROGRAM_EXECUTABLES = $(addprefix $(PROGRAM_DIR)/,$(EXECUTABLES))

all: $(PROGRAM_EXECUTABLES)

$(PROGRAM_DIR):
	mkdir -p $(PROGRAM_DIR)

$(PROGRAM_DIR)/pdadd.exe: pdadd.cpp diary.cpp handler.cpp | $(PROGRAM_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(PROGRAM_DIR)/pdlist.exe: pdlist.cpp diary.cpp handler.cpp | $(PROGRAM_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(PROGRAM_DIR)/pdshow.exe: pdshow.cpp diary.cpp handler.cpp | $(PROGRAM_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(PROGRAM_DIR)/pdremove.exe: pdremove.cpp diary.cpp handler.cpp | $(PROGRAM_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

runpdadd: $(PROGRAM_DIR)/pdadd.exe
	./$(PROGRAM_DIR)/pdadd.exe

runpdlist: $(PROGRAM_DIR)/pdlist.exe
	./$(PROGRAM_DIR)/pdlist.exe

runpdshow: $(PROGRAM_DIR)/pdshow.exe
	./$(PROGRAM_DIR)/pdshow.exe

runpdremove: $(PROGRAM_DIR)/pdremove.exe
	./$(PROGRAM_DIR)/pdremove.exe

test:$(PROGRAM_EXECUTABLES)
	chmod +x test_diary.sh
	./test_diary.sh

clean:
	rm -f $(addprefix $(PROGRAM_DIR)/,$(EXECUTABLES))

.PHONY: all clean runpdadd runpdlist runpdshow runpdremove test