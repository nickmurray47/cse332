// Nicholas Murray and John Garza, Lab 3, game board definitions 

#include "stdafx.h"
#include "functions.h"
#include "index.h"
#include "game_board.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//define a function for reading in the dimensions of a game board from an input file stream
int board_dimensions(ifstream &file, unsigned int&a, unsigned int&b) {

	string s;
	if (getline(file, s)) {
		stringstream strm(s);

		if (strm >> a) {

			if (strm >> b) {
				return (int)result::success;
			}
			else {
				return (int)result::extraction_fail;
			}
		}

		else {
			return (int)result::extraction_fail;
		}
	}
	else {
		return (int)result::getline_err;
	}

}

//function for determining piece positions on board 
int read_gamepiece(std::ifstream&strm, vector<gamepiece>&piece_positions, unsigned int board_width, unsigned int board_height) {

	string s;
	if (strm.is_open())
	{
		while (getline(strm, s))
		{
			string p_color, p_name, p_display;
			unsigned int x = 0, y = 0;
			stringstream strm(s);

			// check conditions of stream
			//extract five values, the piece color, piece name, a string for display, x and y for placement 
			if (strm >> p_color >> p_name >> p_display >> x >> y) {
				piece_color pc = pc_to_string(p_color);
				if (pc != piece_color::invalid) {
					if (x < board_width && y<board_height) {
						//cout << color << name << representation << horiz << vert << endl; 
						int index = board_width * y + x;
						//cout << index << endl; 
						gamepiece gp = gamepiece(p_name, pc, p_display);
						piece_positions[index] = gp;

					}
					else {
						return (int)result::piece_failure;
					}
				}
				else {
					return (int)result::piece_failure;
				}
			}
		}
	}

	else {
		return (int)result::fail_open_file;
	}
	strm.close();

	return (int)result::success;
}

//print out board with vertical in descending order and width in ascending 
int print_pieces_board(const vector<gamepiece> &display, unsigned int width, unsigned int height) {

	//0, 0 as lower left hand
	// check dimensions of board

	int size = width*height;
	if (display.size() != size) {
		return (int)result::bad_dimensions;
	}
	else {

		for (unsigned int row = (height - 1); row >= 0; --row) {

			for (unsigned int column = 0; column <= (width - 1); ++column) {
				//if it aligns
				if (column == (width - 1)) {
					cout << display[((width)* row + column)].piece_display << endl;
				}
				else {
					cout << display[((width)* row + column)].piece_display;
				}
			}
		}
		return (int)result::success;
	}
}
