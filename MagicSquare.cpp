//John Garza and Nicholas Murray

#include "stdafx.h"
#include "MagicSquare.h"
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

//default constructor calls overloaded constructors to avoid repeating logic
MagicSquare::MagicSquare() : MagicSquare((int)params::default_size) {}

//if one parameter is passed, that becomes the board dimension
//chained called to overloaded constructor to avoid repeating logic
MagicSquare::MagicSquare(int board_dimension) : MagicSquare(board_dimension, (int)params::default_piece, (int)params::default_space) {}

//if two parameters are passed, then the second one becomes the lowest piece
MagicSquare::MagicSquare(int board_dimension, int lowest_piece, int long_piece) : GameBase(board_dimension, board_dimension, long_piece) {
	
	for (int i = lowest_piece; i < (lowest_piece + (width*height)); i++) {
		stringstream converter;
		converter << i;
		string rep;
		if (converter >> rep) {
			gamepiece magic_numbers = gamepiece(rep, piece_color::no_color, rep);
			available_pieces.push_back(magic_numbers);
		}

	}

	if (!GameBase::loaded_from_file) { //construct board if one wasn't loaded from file

		for (int i = 0; i < width*height; ++i) {
			board.push_back(gamepiece("empty", piece_color::no_color, " "));
		}
	}
	else { //if a board was loaded from file, remove placed pieces from available vector and add to used vector
	
		for (int i = 0; i < board.size(); ++i) {
			if (board[i].piece_display != " ") { //there is an actual piece here
				gamepiece used = gamepiece(board[i].piece_name, board[i].gp_color, board[i].piece_display);
				available_pieces.erase(std::remove(available_pieces.begin(), available_pieces.end(), used), available_pieces.end());
				used_pieces.push_back(used);
			}
		}

	}
	


}

ostream& MagicSquare::print_gameboard(ostream &o) const {

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

	cout << "Available Pieces: " << flush;
	for (auto it = available_pieces.begin(); it != available_pieces.end(); it++) {
		cout << (*it).piece_display << " " << flush;
	}
	cout << endl;
	return o;
}

//ostream operator for printing out board 
ostream & operator<< (ostream &o,
	const MagicSquare&p)
{
	p.print_gameboard(o);
	return o;
}

void MagicSquare::print() {
	cout << *this << endl;
}

bool MagicSquare::stalemate() {
	if (filled_board_checker()) { //check if board is filled, to prevent errors in sum checker (it assumes every square has a digit)
		return !(sum_checker());
	}
	return false;
}

//returns true if every space on the board is filled; false otherwise
bool MagicSquare::filled_board_checker() {
	for (unsigned int i = 0; i < board.size(); i++) {
		if (board[i].piece_display == " ") {
			return false;
		}
	}
	return true;
}

bool MagicSquare::sum_checker() {

	//convert strings to ints for use in the next section of lab

	vector<int> num_vals;
	for (unsigned int i = 0; i < board.size(); i++) {

		stringstream converter(board[i].piece_display);
		int int_val;
		if (converter >> int_val) {
			num_vals.push_back(int_val);
		}
	}

	//find sum of the first column to use in comparing to the rest
	int sum = 0;
	for (int i = 0; i < width; ++i) {
		sum += num_vals[i];
	}

	//check rows
	for (int x = 0; x < width; x++) {
		int sum_checker = 0;
		for (int y = 0; y < height; y++) {
			sum_checker += num_vals[(width*x) + y];
		}
		if (sum_checker != sum) {
			return false;
		}
	}

	//check columns
	for (int x = 0; x < height; x++) {
		int sum_checker = 0;
		for (int y = 0; y < width; y++) {
			sum_checker += num_vals[(width*x) + y];
		}
		if (sum_checker != sum) {
			return false;
		}
	}

	//check diagonal 1
	int d1_sum = 0;
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (x == y) {
				d1_sum += num_vals[(width*x) + y];
			}
		}
	}
	if (d1_sum != sum) {
		return false;
	}

	//check diagonal 2
	int d2_sum = 0;
	for (int x = (height - 1); x >= 0; x--) {
		for (int y = 0; y < width; y++) {
			if (x == y) {
				d2_sum += num_vals[(width*x) + y];
			}
		}
	}
	if (d1_sum != sum) {
		return false;
	}
	return true;
}

bool MagicSquare::done() {
	if (filled_board_checker()) { //check if board is filled, to prevent errors in sum checker (it assumes every square has a digit)
		return sum_checker();
	}
	return false;
}

int MagicSquare::prompt(int &piece) {
	string input;
	int a = 0, b = 0;

	while (true) {
		cout << "Please pick an available piece or enter 'quit'" << endl;
		//use getline 
		//Sometimes a blank line is entered, if so, getline again 

		getline(cin, input);
		if (input.empty()) {
			getline(cin, input);
		}
		if (input == "quit") {
			return (int)result::user_quit;
		}
		istringstream strm(input);
		if (strm >> a) {
			for (unsigned int i = 0; i < available_pieces.size(); i++) {
				if (available_pieces[i].piece_display == input) {
					piece = a;
					return (int)result::success;
				}
			}
			for (unsigned int i = 0; i < used_pieces.size(); i++) {
				if (used_pieces[i].piece_display == input) {
					return (int)result::piece_already_placed;
				}
			}
		}
	}
}

int MagicSquare::turn() {
	int a = 0, b = 0, c = 0, d = 0, piece_available = 0;
	int &f_x = a, &f_y = b, &p = piece_available;
	// need these because GB prompt only takes unsigned 
	unsigned int temp_fx = f_x, temp_fy = f_y;
	vector<int> move_list;
	bool move_ok = false;

	while (!move_ok) {
		int coordinates = GameBase::prompt(temp_fx, temp_fy);
		if (coordinates != 0) {
			if (coordinates == (int)result::user_quit) {
				return (int)result::user_quit;
			}
			continue;
		}
		int magic_piece = MagicSquare::prompt(p);
		if (magic_piece == (int)result::piece_already_placed) {
			cout << "Piece already used" << endl;
		}
		else {
			move_ok = true;
		}
	}
	//logic for placing a piece 
	string s = to_string(p);
	gamepiece user_piece = gamepiece(s, piece_color::no_color, s);
	if (board[temp_fx*width + temp_fy].piece_display == " ") {
		available_pieces.erase(std::remove(available_pieces.begin(), available_pieces.end(), user_piece), available_pieces.end());
		used_pieces.push_back(user_piece);
		//place the piece at the coordinates 
		board[temp_fx*width + temp_fy] = user_piece;
	}
	else {
		cout << "There is a piece already placed here" << endl;
		return (int)result::piece_already_placed;
	}
	cout << endl;
	cout << *this << endl;

	if (stalemate()) {
		return (int)result::stalemate;
	}

	return (int)result::success;
}
