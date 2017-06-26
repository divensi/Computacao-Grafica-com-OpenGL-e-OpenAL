all: main.cpp
	clang++ main.cpp -lGL -lGLU -lglut -lalut -lopenal -pthread -o main -lSOIL -std=c++11

run: main.cpp
	clang++ main.cpp -lGL -lGLU -lglut -lalut -lopenal -pthread -o main -lSOIL -std=c++11
	tilix -e ./main
