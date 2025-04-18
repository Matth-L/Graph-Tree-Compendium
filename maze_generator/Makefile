all :
	mkdir -p bin
	g++ -Wall -Wextra -I include/ -c src/Cell.cpp -o bin/Cell.o
	g++ -Wall -Wextra -I include/ -c src/Maze.cpp -o bin/Maze.o
	g++ -Wall -Wextra -I include/ -c src/Dijkstra.cpp -o bin/Dijkstra.o
	g++ -Wall -Wextra -I include/ -c src/AStar.cpp -o bin/Astar.o
	g++ -Wall -Wextra -I include/ -c src/Main.cpp -o bin/Main.o
	g++ bin/Cell.o bin/Maze.o bin/Dijkstra.o bin/Astar.o bin/Main.o -o main 

clean:
	rm -rf bin
	rm main