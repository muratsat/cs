all: run

assemble: assemble.py point.o segment.o line.o ray.o circle.o
	python3 assemble.py

run: main
	./main

main: main.cpp point.o segment.o line.o ray.o circle.o
	g++ -std=c++17 -Wall -Wextra -Werror -pedantic -g \
		-o main main.cpp \
		point.o segment.o line.o ray.o circle.o


point.o: point.cpp
	g++ -c -g point.cpp

segment.o: segment.cpp
	g++ -c -g segment.cpp

line.o: line.cpp
	g++ -c -g line.cpp

ray.o: ray.cpp
	g++ -c -g ray.cpp

circle.o: circle.cpp
	g++ -c -g circle.cpp

clean:
	rm -f main tests *.o geometry.hpp geometry.cpp