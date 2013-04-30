# detect operating system
OS := $(shell uname)
NAME = TicTacToe

# compile and run
all: compile 
	./$(NAME)


compile:
	
ifeq ($(OS), Linux)
		g++ *.cpp -lGLU -lglut -o $(NAME)
else
ifeq ($(OS), Darwin) # mac
		g++ -framework OpenGL -framework GLUT *.cpp -o $(NAME)
endif
endif

clean:
	rm $(NAME)

