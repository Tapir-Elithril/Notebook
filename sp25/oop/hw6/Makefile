SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)     
OUT = vector

INCLUDES = -I.

CXXFLAGS = $(INCLUDES)

all: $(OUT)

$(OUT): $(OBJ)
	g++ $(OBJ) -o $(OUT)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

run: $(OUT)
	rm $(OBJ)
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)

