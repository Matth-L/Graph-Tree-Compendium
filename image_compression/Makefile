all :
	mkdir -p bin
	g++ -Wall -Wextra -I include/ -c src/quadtree.cpp -o bin/quadtree.o
	g++ -Wall -Wextra -I include/ -c src/main.cpp -o bin/main.o
	g++ bin/quadtree.o bin/main.o -o bin/main 

clean:
	rm -vrf bin