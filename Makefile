CC = g++
CFLAGS = -g
OBJS = $(shell echo $(wildcard *.cpp) | sed 's/\.cpp/\.o/g')
OBJS += $(shell echo $(wildcard Lesper/*.cpp) | sed 's/\.cpp/\.o/g')
BIN = lesper

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)
%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN) Lesper/test.lesper

clean:
	rm -rf $(BIN) *.o
