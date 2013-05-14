#ifndef TICTACTOEGL_HPP
#define TICTACTOEGL_HPP

#define RED   	 1.0, 0.0, 0.0, 1.0
#define GREEN 	 0.0, 1.0, 0.0, 1.0
#define BLUE   	 0.0, 0.0, 1.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0

class TicTacToeGL{
	public:
		static const int XSCREEN = 800;
		static const int YSCREEN = 600;

		static const int XWORLD = 20;
		static const int YWORLD = 20;
		static const int ZWORLD = 20;

		static void initControls();
		// calbacks (need to be static)
		static void inputMouseCb(int x, int y);
		static void inputKeyboardCb(int key, int x, int y);
		static void inputSpecialCb(int key, int x, int y);
		static void display();

		TicTacToeGL(int, char**);
		static void init();
	private:
		static void draw();

};

#endif
