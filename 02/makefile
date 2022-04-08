CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main.o tokenParser.o
	$(CC) $(FLAGS) main.o tokenParser.o -o main $(TEST_LIBS)
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c $(TEST_LIBS)

tokenParser.o: tokenParser.hpp tokenParser.cpp
	$(CC) $(FLAGS) tokenParser.cpp -c

test: main.o tokenParser.o
	$(CC) $(FLAGS) main.o tokenParser.o -o test $(TEST_LIBS)
	./test

clean:
	rm -f *.o main test
