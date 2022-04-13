CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o main $(TEST_LIBS)
	
main.o:
	$(CC) $(FLAGS) main.cpp -c $(TEST_LIBS)

matrix.o:
	$(CC) $(FLAGS) matrix.cpp -c $(TEST_LIBS)

test: main.o matrix.o
	g++ -std=c++17 main.o matrix.o -o test $(TEST_LIBS)
	./test

clean:
	rm -f *.o main test
