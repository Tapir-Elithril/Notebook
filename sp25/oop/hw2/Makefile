SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)     
OUT = student2

INCLUDES = -I.

CXXFLAGS = $(INCLUDES)

all: $(OUT)

$(OUT): $(OBJ)
	g++ $(OBJ) -o $(OUT)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)

