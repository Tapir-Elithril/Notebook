SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)     
OUT = adventure

INCLUDES = -I.

CXXFLAGS = $(INCLUDES)

all: $(OUT)

$(OUT): $(OBJ)
	g++ $(OBJ) -g -o $(OUT)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)

