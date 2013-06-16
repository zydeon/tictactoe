# detect operating system
OS := $(shell uname)
NAME = TicTacToe
FLAGS = -Wall -lm

# compile and run
all: compile 
	./$(NAME)

compile:
	
ifeq ($(OS), Linux)
		g++ $(FLAGS) *.cpp -lGLU -lglut -o $(NAME)
else
ifeq ($(OS), Darwin) # mac
		g++ $(FLAGS) -framework OpenGL -framework GLUT *.cpp -o $(NAME)
endif
endif

clean:
	rm $(NAME)

