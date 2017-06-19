all: main.cpp
	g++ -o main ./main.cpp -lGL -lGLU -lglut -lSOIL -I.

run: main.cpp
	g++ -o main ./main.cpp -lGL -lGLU -lglut -lSOIL -I.
	tilix -e ./main
