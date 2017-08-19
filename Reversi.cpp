#include "stdafx.h"
#include "Reversi.h"
#include <sstream>
#include "gamepiece.h"
#include "functions.h"
#include <iostream>

using namespace std;


Reversi::Reversi(std::string name1, std::string name2) : GameBase(8,8), player_black(name1), player_white(name2) {


	if (!GameBase::loaded_from_file) {
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

		player_Turn = "X";
		GameBase::player_turn = "X";
	}

	player_Turn = GameBase::player_turn;
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
 
	int black_counter = 0;
	int white_counter = 0;


	string the_winner = " ";
	if (player_Turn == "X") {
		the_winner = "O";
	}
	else {
		the_winner = "X";
	}

	for (unsigned int i = 0; i < board.size(); ++i) {
		if (board[i].piece_display == "X") {
			++black_counter;
		}
		else if (board[i].piece_display == "O") {
			++white_counter;
		}
	}

	if ((black_counter == 0) || (white_counter == 0)) {
		cout << "Winner: " << the_winner << endl; 
		return true; //board can't be empty, so this conditional means one of the players has removed all their opponent's pieces & won
	}


	if ((black_counter > white_counter) || (black_counter < white_counter)) {
		if ((black_counter + white_counter) == (width*height)) {
			cout << "Winner: " << the_winner << endl;
			return true; //one player has more pieces and the board is full
		}
		else { 
			//handle edge case where num pieces is not equal for both players, but there are no valid moves left
			bool no_valid_moves = true;
			
			for (auto it = board.begin(); it != board.end(); it++) {
				if ((*it).piece_display == " ") { 
					
					int index = std::distance(board.begin(), it); // gets the iterator position, linear coordinate
					if (valid_move(index)) { 
						 
						 
						return false; 
					}
				}
			}
			if (no_valid_moves) {
				cout << "Winner: " << the_winner << endl;
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	return false;
	
}

bool Reversi::stalemate() {

	int black_counter = 0;
	int white_counter = 0;
	for (unsigned int i = 0; i < board.size(); ++i) {
		if (board[i].piece_display == "X") {
			++black_counter;
		}
		else if (board[i].piece_display == "O") {
			++white_counter;
		}
	}

	cout << "black pieces: " << black_counter << " white pieces: " << white_counter << endl;

	if (white_counter == black_counter) {

		if ((black_counter + white_counter) == (width*height)) {

			return true; //board is full and players both have the same number of pieces, so stalemate
		}
		else { //board is not full, but both players have the same # of pieces; must check if any valid moves are left
			bool no_valid_moves = true;
			for (unsigned int i = 0; i < board.size(); ++i) {
				if (board[i].piece_display == " ") {
					if (valid_move(i)) {
						no_valid_moves = false; //only ever flip to false, to track if there's at least one valid move somewhere
					}
				}
			}
			return no_valid_moves;
		}
		
	}

	return false;

}

bool Reversi::turn_helper (string player_piece){
	
	bool player_has_valid_moves = false;

	for (unsigned int i = 0; i < board.size(); ++i) {
		if (board[i].piece_display == " ") {

			
			vector<int> dummy;
			int y_coord = i % 8;
			int x_coord = (i - y_coord) / 8;

			if (valid_move(x_coord, y_coord, dummy, player_piece)) {
				player_has_valid_moves = true;
			}

		}
	}

	return player_has_valid_moves;
}

int Reversi::turn() {
	unsigned int a = 0, b = 0;
	unsigned int &x = a, &y = b;

	if (player_Turn == "X") {
		cout << "Player " << player_black << "'s turn with X pieces" << endl;
		if (!(turn_helper(player_Turn))) {
			cout << "No valid moves, skipping turn" << endl;
			player_Turn = "O";
			GameBase::player_turn = "O";
			return (int)result::success; 
		}
	}
	else {
		cout << "Player " << player_white << "'s turn with O pieces" << endl;
		if (!(turn_helper(player_Turn))) {
			cout << "No valid moves, skipping turn" << endl;
			player_Turn = "X";
			GameBase::player_turn = "X";
			return (int)result::success;
		}
	}

	//if player has a valid move, then continually prompt for correct coordinates

	while (true) {
		int prompt_result = GameBase::prompt(x, y);

		vector<int> pieces_to_remove;

		if (prompt_result == (int)result::user_quit) {
			return (int)result::user_quit;
		}

		if (!(valid_move(x, y, pieces_to_remove, player_Turn))) {
			cout << "Not a valid move!" << endl;
			continue;
		}
	
		if (prompt_result == (int)result::success) { 

			int placed_piece_coord = (x*width) + y;
			if (player_Turn == "X") {
				board[placed_piece_coord] = black_piece;
				
				for (auto it = pieces_to_remove.begin(); it != pieces_to_remove.end(); it++) {
	
					board[(*it)] = black_piece;
				}
				player_Turn = "O";
				GameBase::player_turn = "O";
			}
			else {
				board[placed_piece_coord] = white_piece;

				for (auto it = pieces_to_remove.begin(); it != pieces_to_remove.end(); it++) {
					board[(*it)] = white_piece;
				}
				player_Turn = "X";
				GameBase::player_turn = "X";
			}
			break;
		}
	}
	cout << *this << endl;
	return (int)result::success;
}

//directly called by done/stalemate, which has found a piece already at this position and doesn't care about finding pieces to swap
bool Reversi::valid_move(int input_linear_coord) {

	vector<int> dummy; // done/stalemate don't care, but overload requires this, and writing yet another overload would be a mess
	int y_coord = input_linear_coord % 8;
	int x_coord = (input_linear_coord - y_coord) / 8;

	bool X_result= valid_move(x_coord, y_coord, dummy, "X");
	bool O_result= valid_move(x_coord, y_coord, dummy, "O");

	return (X_result || O_result); 
}

//called indirectly from stalemate via overloaded counterpart, called directly by user attempting to place piece
bool Reversi::valid_move(int x, int y, vector<int> & swap_positions, string input_piece) {
	
	string opp_piece;

	if (input_piece == "X") {
		opp_piece = "O";
	}
	else {
		opp_piece = "X";
	}

	bool valid_moves_found = false;

	int width_low, width_high, height_low, height_high; 
	for_bounds_helper(x, y, width, height, width_low, width_high, height_low, height_high);

	for (int search_width = width_low; search_width < width_high; ++search_width) { 

		for (int search_height = height_low; search_height < height_high; ++search_height) {

			if ((x == search_width) && (y == search_height)) {
				continue; //skip the input coordinate without using an else statement, to avoid nested clutter
			}

			int curr_linear_coord = (search_width*width) + search_height;

			if (board[curr_linear_coord].piece_display == opp_piece) {
				int delta_x = search_width - x;
				int delta_y = search_height - y;
				//scan all squares around a proposed piece placement; if there is a piece of the opposite team in one of these
				//squares, a valid move is possible but still not known: must propogate further in that direction and see if there
				//is a line of opposing pieces capped by a piece of the player's team
				//propogate helper function does this, and stores the coords of opposing pieces to be swapped in swap_positions

				if (propogate_check(search_width, search_height, delta_x, delta_y, input_piece, swap_positions)) {
					valid_moves_found = true; //not the same as valid_moves_found = propogate(...)
					//this is a flag that should only ever be flipped to true if valid moves found, but not changed back to false
				}
			}
		}
	}

	return valid_moves_found;

}

bool Reversi::propogate_check(int start_x, int start_y, int delta_x, int delta_y, string piece_str, vector<int> & swap_positions) {

	bool found_valid_end = false;
	vector<int> possible_swapped_pieces;

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
			possible_swapped_pieces.push_back(curr_index); //store pieces that may need to be swapped from opposing team to user's team

		}

		start_x += delta_x;
		start_y += delta_y;

	}

	if (found_valid_end) {
		for (unsigned int i = 0; i < possible_swapped_pieces.size(); ++i) {
			swap_positions.push_back(possible_swapped_pieces[i]);
		}

	}

	return found_valid_end;

}

std::ostream & operator<<(std::ostream &o, const Reversi &g) {
	g.print_gameboard(o);
	return o;
}
