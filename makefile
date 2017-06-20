all: main.cpp
	g++ -o main ./main.cpp -lGL -lGLU -lglut -lSOIL -pthread -I.

run: main.cpp
	g++ -o main ./main.cpp -lGL -lGLU -lglut -lSOIL -pthread -I.
	tilix -e ./main
