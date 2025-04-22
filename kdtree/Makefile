all :
	mkdir -p bin
	g++ -Wall -Wextra -I include/ -c src/KDnode.cpp -o bin/KDnode.o
	g++ -Wall -Wextra -I include/ -c src/KDtree.cpp -o bin/KDtree.o
	g++ -Wall -Wextra -I include/ -c src/main.cpp -o bin/main.o
	g++ bin/KDnode.o bin/KDtree.o bin/main.o -o bin/main 

clean:
	rm -vrf bin
