CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main.o allocator.o
	$(CC) $(FLAGS) main.o allocator.o -o main
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

allocator.o: allocator.hpp allocator.cpp
	$(CC) $(FLAGS) allocator.cpp -c

test: main.o allocator.o
	 main.o allocator.o -o test $(TEST_LIBS)
	./test

clean:
	rm -f *.o main
