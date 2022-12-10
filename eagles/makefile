all:
	@echo "make mother - to compile and run mother.cpp"
	@echo "make children - to compile and run children.cpp"
	@echo "make exit - to compile and run exit.cpp"


mother: mother.out
	./mother.out

mother.out: src/mother.cpp src/eagle.cpp src/bird.cpp
	g++ -o mother.out src/mother.cpp src/eagle.cpp src/bird.cpp


children.out: src/children.cpp src/eaglet.cpp src/bird.cpp
	g++ -o children.out src/children.cpp src/eaglet.cpp src/bird.cpp

children: children.out
	./children.out


exit: exit.out
	./exit.out

exit.out: src/exit.cpp src/eagle.cpp src/bird.cpp
	g++ -o exit.out src/exit.cpp src/eagle.cpp src/bird.cpp

clean:
	rm -f *.out
