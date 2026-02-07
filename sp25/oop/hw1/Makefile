SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)     
OUT = student1   

all: $(OUT)

$(OUT): $(OBJ)
	g++ $(OBJ) -o $(OUT)

%.o: %.cpp
	g++ -c $< -o $@

run:$(OUT) 
	./$(OUT) 

clean:
	rm -f $(OBJ) $(OUT) 
