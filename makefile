# detect operating system
OS := $(shell uname)
NAME = TicTacToe

# compile and run
all: compile 
	./$(NAME)


compile:
	
ifeq ($(OS), Linux)
		echo 'adiciona cena de compilar para linux'
else
ifeq ($(OS), Darwin) # mac
		g++ -framework OpenGL -framework GLUT $(NAME).cpp -o $(NAME)
endif
endif

clean:
	rm $(NAME)

