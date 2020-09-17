CC = g++

CFLAGS = -g -std=c++14 -w

INCLUDE =

LIBS = -lOpenCL


# (TODO: enter filename without extension)
FILENAME = helloworld

all: $(FILENAME).cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FILENAME).cpp $(LIBS) -o $(FILENAME)

run:
	@./$(FILENAME)	

clean:
	rm ./$(FILENAME) 
