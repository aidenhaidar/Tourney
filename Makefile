all: maze

maze: main.cpp
	g++ -o maze main.cpp

clean:
	rm -f maze
