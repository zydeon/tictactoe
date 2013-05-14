# detect operating system
OS := $(shell uname)
NAME = TicTacToe
FLAGS = -Wall
CLASSES = Player.cpp Fence.cpp TicTacToe.cpp TicTacToeGL.cpp 

# compile and run
all: compile 
	./$(NAME)


compile:
	
ifeq ($(OS), Linux)
		g++ $(FLAGS) $(CLASSES) -lGLU -lglut -o $(NAME)
else
ifeq ($(OS), Darwin) # mac
		g++ $(FLAGS) -framework OpenGL -framework GLUT $(CLASSES) -o $(NAME)
endif
endif

clean:
	rm $(NAME)

