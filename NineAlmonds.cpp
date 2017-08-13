#pragma once 

#include "stdafx.h"
#include "NineAlmonds.h"
#include "game_board.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

NineAlmonds::NineAlmonds() : GameBase(5, 5) {
	
	if (!GameBase::loaded_from_file) {

	cout << "NineAlmonds constructor" << endl;

		for (int i = 0; i < width*height; ++i)
		{
			board.push_back(gamepiece("empty", piece_color::no_color, " "));
		}
		for (int x = 3; x >= 1; x--)
		{
			for (int y = 1; y <= 3; y++) {
				int index = width*x + y;
				board[index] = almond;
			}
		}
	}
}

void NineAlmonds::print() {
	cout << *this << endl;
}

//creates starting position
void NineAlmonds::print_starting_board() {
	//empty vector of empty gamepieces- essentially clears the board
	for (int i = 0; i < width*height; ++i)
	{
		board.push_back(gamepiece("empty", piece_color::no_color, " "));
	}
	for (int x = 3; x >= 1; x--)
	{
		for (int y = 1; y <= 3; y++) {
			int index = width*x + y;
			board[index] = almond;
		}
	}
}

ostream& NineAlmonds::print_current_board(ostream &o) const {
	//print out the board  

	int spacing = longest_piece;
	ostringstream board_disp;
	board_disp << left;
	cout << endl;

	for (int row = (height); row > 0; --row)
	{
		board_disp << row - 1;
		for (int column = 0; column < width; ++column)
		{
			board_disp.width(spacing);
			board_disp << board[(width* (column)+(row - 1))].piece_display;
		}
		board_disp << '\n';
	}
	//prints column axis numbers
	board_disp << " ";
	for (int i = 0; i < width; i++) {
		board_disp.width(spacing);
		board_disp << i;
	}
	o << board_disp.str() << endl;
	return o;
}

//ostream operator for printing out board
ostream & operator<< (ostream &o,
	const NineAlmonds &p)
{
	return p.print_current_board(o);
}

// function done()
bool NineAlmonds::done() {
	//for every position in vector gameboard, check if empty 
	bool check = true;
	for (int i = 0; i < width*height; i++) {
		if (board[i].piece_display == "A") {
			check = false;
		}
	}
	if (board[12].piece_display == "A" && check == true) {
		cout << "Done is true" << endl;
		return true;
	}
	else {
		return false;
	}
}

//function stalemate()
bool NineAlmonds::stalemate() {
	// if game is done, return false 
	if (NineAlmonds::done()) {
		return false;
	}
	// if there are valid moves, return false, there is a stalemate if a piece exists
	// that is not adjacent to any other pieces 
	for (int i = 0; i < width*height; i++) {
		if (board[i].piece_display == "A") {
			for (int j = 0; j < width*height; j++) {
				if (board[j].piece_display == " ") {
					int y1 = i / width;
					int x1 = i % width;
					int y2 = j / width;
					int x2 = j % width;
					bool stale_result = stale_move(x1, y1, x2, y2);
					//look for a true statement if possible moves 
					if (stale_result) {
						return false;
					}
				}
			}
		}
	}
	// return true if there is a stalemate  
	return true;
}

bool NineAlmonds::stale_move(int x1, int y1, int x2, int y2) {
	// pass the first square's parameters and second square's

	int midRow = (y1 + y2) / 2;
	int midCol = (x1 + x2) / 2;

	//check if an almond is adjacent 
	if (board[y2 * width + x2].piece_display == "A") {
		return false;
	}
	if (board[midRow * width + midCol].piece_display != "A") {
		return false;
	}
	if (board[y1 * width + x1].piece_display != "A") {
		return false;
	}

	//check adjacent and other separated postions 
	if (abs(y1 - y2) != 0 && abs(x1 - x2) != 0) {
		if (abs(y1 - y2) != 2 || abs(x1 - x2) != 2) {
			return false;
		}
	}
	if (abs(y1 - y2) > 2 || abs(x1 - x2) > 2 || abs(x1 - x2) == 1 || abs(y1 - y2) == 1) {
		return false;
	}
	return true;
}


// make a valid move function for checking valid moves and repeat logic from turn()
int NineAlmonds::valid_move(unsigned int &x, unsigned int &y, unsigned int &w, unsigned int &z) {
	// cases are 1. within board range 2. 
	// pass the first square's parameters
	unsigned int first_square = width*x + y;
	unsigned int second_square = width*w + z;
	int midpoint = (first_square + second_square) / 2;

	if (x < 5 && y < 5 && w < 5 && z < 5) {
		if (board[second_square].piece_display == " " && board[first_square].piece_display == "A") {
			if (board[midpoint].piece_display == "A") {
				if (second_square == (first_square + 2)) {
					return (int)result::success;
				}
				else if (second_square == (first_square - 2)) {
					return (int)result::success;
				}
				else if (second_square == (first_square + 8)) {
					return (int)result::success;
				}
				else if (second_square == (first_square - 8)) {
					return (int)result::success;
				}
				else if (second_square == (first_square + 10)) {
					return (int)result::success;
				}
				else if (second_square == (first_square - 10)) {
					return (int)result::success;
				}
				else if (second_square == (first_square + 12)) {
					return (int)result::success;
				}
				else if (second_square == (first_square - 12)) {
					return (int)result::success;
				}
			}
			else {
				return (int)result::no_valid_move;
			}
		}
		else {
			return (int)result::no_valid_move;
		}
	}
	else {
		//square is out of board range
		return (int)result::square_out;
	}
	return (int)result::no_valid_move;
}

int NineAlmonds::prompt(unsigned int &horizontal, unsigned int &vertical) {
	string input;
	string comma = ",";
	unsigned int a = 0, b = 0;


	while (true) {
		cout << "Please make a valid move 'x,y' or enter 'quit'" << endl;
		//use getline 
		//Sometimes a blank line is entered, if so, getline again  
		getline(cin, input);
		if (input.empty()) {
			getline(cin, input);
		}
		size_t found = input.find(comma);
		if (input == "quit") {
			return (int)result::user_quit;
		}
		string space = " ";
		replace(input.begin(), input.end(), ',', ' ');
		istringstream strm(input);
		if (strm >> a) {
			if (strm >> b) {
				//assign stream inputs to passed parameters
				horizontal = a;
				vertical = b;
				return (int)result::success;
			}
		}
	}
	// not all control paths return a value in order to force user to enter a valid input 

}

int NineAlmonds::turn() {
	// a and b are starting coordinates and d and e are ending coordinates 
	unsigned int a = 0, b = 0, c = 0, d = 0;
	unsigned int &f_x = a, &f_y = b, &s_x = c, &s_y = d;
	vector<int> move_list;
	bool move_ok = false;

	// FIRST MOVE 
	// check if valid 
	while (!move_ok) {
		//call prompt the first time 
		int prompt_return = prompt(f_x, f_y);
		// if return is 0 then it is successful 
		if (prompt_return == 0) {
			std::cout << "You entered: " << f_x << " " << f_y << endl;
		}
		else if (prompt_return == (int)result::user_quit) {
			return (int)result::user_quit;
		}

		// call prompt second time for ending coordinates 
		prompt_return = prompt(s_x, s_y);
		if (prompt_return == 0) {
			std::cout << "You entered: " << s_x << " " << s_y << endl;
		}
		else if (prompt_return == (int)result::user_quit) {
			return (int)result::user_quit;
		}
		if (prompt_return != (int)result::user_quit) {
			int first_square = f_x*width + f_y;
			int second_square = s_x*width + s_y;
			int check_valid = (valid_move(f_x, f_y, s_x, s_y));
			int midpoint = (first_square + second_square) / 2;

			if (check_valid == (int)result::success) {
				move_list.push_back(a), move_list.push_back(b), move_list.push_back(c), move_list.push_back(d);
				board[first_square] = empty;
				board[second_square] = almond;
				board[midpoint] = empty;
				std::cout << "Turn Count: " << turn_counter << endl;
				if (stalemate()) {
					return (int)result::stalemate;
				}
				move_ok = true;
			}
		}
		else {
			cout << "Invalid coordinates, please try again" << endl;
		}
	}
	std::cout << *this << endl;
	std::cout << '\n' << flush;

	//print statement for moves 
	std::cout << f_x << "," << f_y << " " << "to " << s_x << "," << s_y << endl;

	while (true) {
		std::cout << "Continue to move this piece y/n or quit to end game" << endl;
		string response;
		//std::cin >> response;
		getline(std::cin, response);

		if (response == "n") {
			return (int)result::switch_piece;
		}
		else if (response == "quit") {
			return (int)result::user_quit;
		}
		else if (response == "y") {
			break;
		}
	}

	// set to second square 
	f_x = s_x;
	f_y = s_y;
	//MOVE CONTINUATION
	bool move_continuation = false;
	while (!move_continuation) {
		//if (response == "y") {
			std::cout << "Enter coordinates for second square" << endl;
			bool check_move = false;
			while (!check_move) {
				//prompt for second coordinates 
				int prompt_return1 = prompt(s_x, s_y);
				if (prompt_return1 == 0) {
					std::cout << "You entered: " << s_x << " " << s_y << endl;
				}
				else if (prompt_return1 == (int)result::user_quit) {
					return (int)result::user_quit;
				}
				int check_valid = (valid_move(f_x, f_y, s_x, s_y));
				if (check_valid == (int)result::success) {
					std::cout << "Valid Move " << endl;
					int first_square = f_x*width + f_y;
					int second_square = s_x*width + s_y;
					int midpoint = (first_square + second_square) / 2;
					board[first_square] = empty;
					board[midpoint] = empty;
					board[second_square] = almond;
					std::cout << *this << endl;
					check_move = true;
					//print out move list 
					move_list.push_back(s_x), move_list.push_back(s_y);
					for (unsigned int i = 0; i < move_list.size() - 2; i = i + 2) {
						std::cout << move_list[i] << ", " << move_list[i + 1] << " to " << flush;
					}
					std::cout << move_list[move_list.size() - 2] << ", " << move_list[move_list.size() - 1] << endl;
					std::cout << "Turn Count: " << turn_counter << endl;
					f_x = s_x, f_y = s_y;
					if (stalemate()) {
						return (int)result::stalemate;
					}
				}
				else if ((check_valid == -7) || (check_valid == -8)) {
					std::cout << "Error: Invalid Coordinates" << endl;
				}
			}


			std::cout << "Continue to move this piece y/n or quit to end game" << endl;
			string response2;
			std::cin >> response2;
			if (response2 == "quit") {
				return (int)result::user_quit;
			}
			else if (response2 == "n") {
				move_continuation = true;
				turn_counter++;
			}
		//}
	}

	std::cout << "User chooses another piece" << endl;
	return (int)result::switch_piece;

}
