#include "stdafx.h"
#include "Reversi.h"
#include <sstream>
#include "gamepiece.h"

using namespace std;

Reversi::Reversi(std::string name1, std::string name2) : GameBase(8,8), player_black(name1), player_white(name2) {

	for (int i = 0; i < width*height; ++i) {
		board.push_back(gamepiece("empty", piece_color::no_color, " "));
	}

	int index1 = 27;
	int index2 = 36;
	int index3 = 28;
	int index4 = 35;

	board[index1] = black_piece;
	board[index2] = black_piece;
	board[index3] = white_piece;
	board[index4] = white_piece;

}

void Reversi::print() {

	cout << *this << endl;
}

std::ostream & Reversi::print_gameboard(std::ostream & o) const {
	ostringstream board_disp;
	board_disp << left;

	for (int row = (height); row > 0; --row)
	{
		board_disp.width(longest_piece);
		board_disp << row - 1;

		for (int column = 0; column < width; ++column)
		{

			board_disp.width(longest_piece);
			board_disp << board[(width* (column)+(row - 1))].piece_display;
		}
		board_disp << '\n';
	}


	board_disp.width(longest_piece);
	board_disp << "x";

	//prints column axis numbers
	for (int i = 0; i < width; i++) {
		board_disp.width(longest_piece);
		board_disp << i;
	}

	o << board_disp.str() << endl;

	return o;
}

bool Reversi::done() {
	return false;
}

bool Reversi::stalemate() {
	return false;
}

int Reversi::turn() {
	return 0;
}

//NOTE: THIS DOES NOT VALIDATE INPUT COORDINATES
//ONLY PASS THIS FUNCTION VALID INDICES ----------------------------------------------------
bool Reversi::valid_move(int x, int y) {
	
	int input_linear_coord = (x*width) + y; //the position of this coordinate pair in the board vector
	string input_piece = board[input_linear_coord].piece_display;
	string opp_piece;

	if (input_piece == "X") {	//CHECK PLAYER GAME PIECE TODO TODO TODO TODO
		opp_piece = "O";
	}
	else {
		opp_piece = "X";
	}

	for (int search_width = (x - 1); search_width < (x + 2); ++search_width) { //TODO CHECK THE BOUNDS

		for (int search_height = (y - 1); search_height < (y + 2); ++search_height) {

			if ((x == search_width) && (y == search_height)) {
				continue; //skip the input coordinate without using an else statement, to avoid nested clutter
			}

			int curr_linear_coord = (search_width*width) + search_height;

			if (board[curr_linear_coord].piece_display == opp_piece) {
				int delta_x = search_width - x;
				int delta_y = search_height - y;
//				propogate_check(search_width, search_height, delta_x, delta_y, input_color);
				//call propogate
			}


		}

	}

}

bool Reversi::propogate_check(int start_x, int start_y, int delta_x, int delta_y, string piece_str) {

	bool found_valid_end = false;

	while ((start_x < width) && (start_y < height) && (start_x >= 0) && (start_y >= 0)) {
		int curr_index = (start_x * width) + start_y;
		string curr_piece = board[curr_index].piece_display;
		
		if (curr_piece == piece_str) {
			found_valid_end = true;
			break;
		}
		else if (curr_piece == " ") {
			break;
		}
		else { //must be piece of other color
			//push into temp vector
		}

		start_x += delta_x;
		start_y += delta_y;

	}

	//if found valid end, dump temp vector into real to be changed vector

}

std::ostream & operator<<(std::ostream &o, const Reversi &g) {
	g.print_gameboard(o);
	return o;
}
