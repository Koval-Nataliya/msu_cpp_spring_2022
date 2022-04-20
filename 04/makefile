CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main.o bigint.o
	$(CC) $(FLAGS) main.o bigint.o -o main $(TEST_LIBS)
	
main.o:
	$(CC) $(FLAGS) main.cpp -c $(TEST_LIBS)

bigint.o:
	$(CC) $(FLAGS) bigint.cpp -c $(TEST_LIBS)

test: main.o bigint.o
	g++ -std=c++17 main.o bigint.o -o test $(TEST_LIBS)
	./test

clean:
	rm -f *.o main test
