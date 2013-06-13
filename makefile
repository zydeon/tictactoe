# detect operating system
OS := $(shell uname)
NAME = TicTacToe
FLAGS = -Wall -lm
CLASSES = project.cpp Player.cpp Fence.cpp TicTacToe.cpp RgbImage.cpp Surface.cpp Table.cpp TTTGraphics.cpp

# compile and run
all: compile 
	./$(NAME)


compile:
	
ifeq ($(OS), Linux)
		g++ $(FLAGS) $(CLASSES) -lGLU -lglut -o $(NAME)
else
ifeq ($(OS), Darwin) # mac
		g++ $(FLAGS) -framework OpenGL -framework GLUT -framework ApplicationServices $(CLASSES) -o $(NAME)
endif
endif

clean:
	rm $(NAME)

