#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define cls() system("cls")

using namespace std;

///
/// UP		72
/// RIGHT	77
/// DOWN	80
/// LEFT	75
/// ENTER	13
/// SPACE	32
/// p		112
/// P		80
/// 

//////////
int game_size_X = 21, game_size_Y = 9;
char field[21][9], field_shown[21][9];
int bombs = 25;
char bomb = 219;
//////////

void menu_loop();
void menu_renderer();
void game_loop();
void game_renderer(int cursor_X, int cursor_Y);
void field_generator();
void game_over();
void clear_field(int x, int y);

int main() {

	menu_loop();

	while (1) {
		int key = _getch();
		cout << key << endl;
	}

	return 0;
}

///////////////////////////////////////////// MENU
void menu_loop() {
	game_loop();
}

void menu_renderer() {
	cls();
}

///////////////////////////////////////////// GAME
void game_loop() {
	field_generator();
	int cursor_X = game_size_X / 2,
		cursor_Y = game_size_Y / 2;
	bool running = true;
	while (running) {
		game_renderer(cursor_X, cursor_Y);
		int key = _getch();
		switch (key) {
			//            ARROWS
		case 72: //up
			if (cursor_Y > 0) cursor_Y--;
			break;
		case 77: //right
			if (cursor_X < game_size_X - 1) cursor_X++;
			break;
		case 80: //down
			if (cursor_Y < game_size_Y - 1) cursor_Y++;
			break;
		case 75: //left
			if (cursor_X > 0) cursor_X--;
			break;
			//            OTHER
		case 13: //enter
		case 32: //space
			//if (field[cursor_X][cursor_Y] == bomb) { break; running = false; }
			if (field[cursor_X][cursor_Y] == ' ') clear_field(cursor_X, cursor_Y);
			field_shown[cursor_X][cursor_Y] = field[cursor_X][cursor_Y];
			break;
		case 112: //p
			// THERE WILL BE PAUSE SOMEDAY
			break;
		}//switch
	}//while
}

void game_renderer(int cursor_X, int cursor_Y) {
	cls();

	for (int y = 0; y < game_size_Y; y++) {

		for (int x = 0; x < game_size_X; x++) {//LINE1

			if (x == cursor_X && y == cursor_Y) cout << "\\ /";
			else cout << "   ";
		}//for x
		cout << endl;
		for (int x = 0; x < game_size_X; x++) {//LINE2

			cout << " " << field_shown[x][y] << " ";
			//cout << " " << field[x][y] << " ";
		}//for x
		cout << endl;
		for (int x = 0; x < game_size_X; x++) {//LINE3

			if (x == cursor_X && y == cursor_Y) cout << "/ \\";
			else cout << "   ";
		}//for x
		cout << endl;
	}//for y
}

void field_generator() {
	srand(time(NULL)); //giving the rand function the proper seed
	for (int i = 0; i < game_size_Y; i++) { //filling the shown field with blocks
		for (int j = 0; j < game_size_X; j++) {
			field_shown[j][i] = 176;
		}
	}
	for (int i = 0; i < game_size_Y; i++) { //filling the actual field with spaces
		for (int j = 0; j < game_size_X; j++) {
			field[j][i] = ' ';
		}
	}

	for (int i = 0; i < bombs; i++) {
		int x = rand() % game_size_X;
		int y = rand() % game_size_Y;
		if (field[x][y] == bomb) i--;
		field[x][y] = bomb;
	}

	for (int y = 0; y < game_size_Y; y++) {

		for (int x = 0; x < game_size_X; x++) {

			int cnt = 0;

			if (x > 0 && y > 0 && field[x - 1][y - 1] == bomb) cnt++; // up left
			if (y > 0 && field[x][y - 1] == bomb) cnt++; // up
			if (x < game_size_X && y > 0 && field[x + 1][y - 1] == bomb) cnt++; // up right

			if (x > 0 && y < game_size_Y && field[x - 1][y + 1] == bomb) cnt++; // down left
			if (y < game_size_Y && field[x][y + 1] == bomb) cnt++; // down
			if (x < game_size_X && y < game_size_Y && field[x + 1][y + 1] == bomb) cnt++; // down right

			if (x > 0 && field[x - 1][y] == bomb) cnt++; // left
			if (x < game_size_X && field[x + 1][y] == bomb) cnt++; // right

			if (cnt > 0 && field[x][y] != bomb) field[x][y] = cnt + 48;

		}//for x
	}//for y
}

void game_over() {

}

void clear_field(int x, int y) {

}