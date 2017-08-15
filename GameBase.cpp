//John Garza and Nicholas Murray

#include "stdafx.h"
#include "GameBase.h"
#include "NineAlmonds.h"
#include "MagicSquare.h"
#include "Reversi.h"

#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

//GameBase::GameBase(int x, int y) : width(x), height(y), longest_piece((int)params::default_space), turn_counter(0), board(vector<gamepiece>()) {};

shared_ptr<GameBase> GameBase::game_ptr = nullptr;

string GameBase::game_type = "Unset";

bool GameBase::loaded_from_file = false;

GameBase::GameBase(int x, int y) : GameBase(x, y, (int)params::default_space) {};

GameBase::GameBase(int x, int y, int n) : width(x), height(y), longest_piece(n), turn_counter(0), board(vector<gamepiece>()) {

	cout << "GameBase constructor" << endl;
	cout << GameBase::game_type << endl;
	
	string filename(GameBase::game_type);
	filename.append(".txt");

	ifstream savefile(filename);

	if (!savefile.is_open()) {
		throw (int)result::fail_open_file;
	}

	string first_line;
	getline(savefile, first_line);
	if (first_line != "NO DATA") {
		
		string piece_count_str;
		getline(savefile, piece_count_str);
		int num_pieces = str_to_int(piece_count_str);

		for (int i = 0; i < num_pieces; ++i) {
			string curr_piece;
			getline(savefile, curr_piece);
			if (curr_piece.empty()) {
				board.push_back(gamepiece("empty", piece_color::no_color, " "));
			}
			else {
				board.push_back(gamepiece(curr_piece, piece_color::no_color, curr_piece));
			}
		}

		string loaded_turn_str;
		getline(savefile, loaded_turn_str); //this discards an empty line
		getline(savefile, loaded_turn_str);
		turn_counter = str_to_int(loaded_turn_str);
		
		cout << "Load complete!" << endl;

		GameBase::loaded_from_file = true;

	}

	savefile.close();

};

void GameBase::arguments(int argc, char*argv[]) {

	if (game_ptr != nullptr) { //singleton control; check to make sure no more than one instance of a game exists at a time
		throw (int)exceptions::game_set;
	}


	if (argc < (int)params::min || argc >(int)params::max) {
		throw (int)result::wrong_argc;
	}


	string game_name(argv[(int)indices::game_name]);

	if (game_name == "NineAlmonds") {
		

		if (argc == (int)params::min) {
			
			game_type = "NineAlmonds";
			
			game_ptr = make_shared<NineAlmonds>();
			
		}
		else {
			
			throw (int)result::wrong_argc;
		}

	}

	else if (game_name == "MagicSquare") {

		if (argc == (int)params::min) {
			game_type = "MagicSquare";
			game_ptr = make_shared<MagicSquare>();
			
		}

		else if (argc == (int)params::middle) {
			stringstream ss(argv[(int)params::min]);
			int dim_board = 0;
			if (ss >> dim_board) {
				if (dim_board > 0) {
					int max_piece = dim_board * dim_board;
					string maxpiecestr = to_string(max_piece);
					int padded_spacing = maxpiecestr.length() + 1;
					game_type = "MagicSquare";
					game_ptr = make_shared<MagicSquare>(MagicSquare(dim_board, 1, padded_spacing));
					
				}
				else {
					cout << "Hit1" << endl;
					throw (int)result::extraction_fail;
				}
			}
			else {
				cout << "Hit2" << endl;
				throw (int)result::extraction_fail;
			}
		}

		else if (argc == (int)params::max) {
			
			int lowest_piece = 0;
			int dim_board = 0;
			int n = 1; // for longest_piece
			stringstream ss(argv[(int)params::min]);
			stringstream ss1(argv[(int)params::middle]);
			if (ss >> dim_board) {
				if (ss1 >> lowest_piece) {

					int highest_piece = lowest_piece + (dim_board*dim_board) - 1;
					string lowpiecestr = to_string(lowest_piece);
					string highpiecestr = to_string(highest_piece);

					if (lowpiecestr.length() > highpiecestr.length()) {
						n = lowpiecestr.length() + 1; //+1 to make sure there's a space between pieces
					}
					else {
						n = highpiecestr.length() + 1;
					}
					game_type = "MagicSquare";
					game_ptr = make_shared<MagicSquare>(MagicSquare(dim_board, lowest_piece, n));
					
				}
				else {
					cout << "Hit3" << endl;
					throw (int)result::extraction_fail;
				}
			}
			else {
				cout << "Hit4" << endl;
				throw (int)result::extraction_fail;
			}
		}
		else {
			throw (int)result::wrong_argc;
		}
	}

	else if (game_name == "Reversi") {
		if (argc == (int)params::max) {
			
			
			
			game_type = "Reversi";

			string first_name = argv[(int)params::min];
			string second_name = argv[(int)params::middle];

			game_ptr = make_shared<Reversi>(Reversi(first_name, second_name));
			
		}
		else {
			
			throw (int)result::wrong_argc;
		}
	}

	else {
		throw (int)result::unrecognized_arg;
	}

}
std::shared_ptr<GameBase> GameBase::instance()
{
	if (game_ptr != nullptr) {
		return game_ptr;
	}
	else {
		throw (int)exceptions::game_not_set;
	}
}

int GameBase::play() {
	//method to begin playing game and handle 1. done 2. stalemate or 3. quit 

	print();
	

	//make sure stalemate and done work correctly 
	while ((!stalemate()) && (!done())) {
		int turn_result = turn();
		++turn_counter;

		if (turn_result == (int)result::user_quit) {
			try {
				save_game();
			}
			catch (int e) {
				throw e;
			}

			return (int)result::user_quit;
		}
		else if (turn_result == (int)result::stalemate) {
			std::cout << "There is a stalemate, game over" << endl;
			return (int)result::stalemate;
		}
	}
	std::cout << "You win! Game finished in " << turn_counter << " turns" << endl;
	return (int)result::success;
}

int GameBase::prompt(unsigned int &horizontal, unsigned int &vertical) {
	string input;
	int a = 0, b = 0;

	while (true) {
		cout << "Please choose a valid space 'x,y' or enter 'quit'" << endl;
		//use getline 
		//Sometimes a blank line is entered, if so, getline again  
		getline(cin, input);
		if (input.empty()) {
			getline(cin, input);
		}
		if (input == "quit") {
			return (int)result::user_quit;
		}
		replace(input.begin(), input.end(), ',', ' ');
		istringstream strm(input);
		if (strm >> a) {
			if (strm >> b) {
				//assign stream inputs to passed parameters

				if (a >= 0 && a < width) {
					if (b >= 0 && b < height) {
						horizontal = a;
						vertical = b;
						return (int)result::success;
					}
				}
			}
		}
	}
	// not all control paths return a value in order to force user to enter a valid input 
}

void GameBase::save_game() {

	string input;

	while (true) {

		cout << "Would you like to save the game before quitting? Yy/Nn" << endl;

		getline(cin, input);

		if ((input == "N") || (input == "n")) {

			string filename(GameBase::game_type);
			filename.append(".txt");

			ofstream savefile(filename);

			if (!savefile.is_open()) {
				throw (int)result::fail_open_file;
			}

			if (!(savefile << "NO DATA")) {
				throw (int)result::file_write_fail;
			}

			savefile.close();

			if (savefile.is_open()) {
				throw (int)result::fail_close_file;
			}

			//return (int)result::success;
			return;
		}

		if ((input == "Y") || (input == "y")) {

			string filename(GameBase::game_type);
			filename.append(".txt");

			ofstream savefile(filename);

			if (!savefile.is_open()) {
				throw (int)result::fail_open_file;
			}

			if (!(savefile << GameBase::game_type << "\n")) {
				throw (int)result::file_write_fail;
			}
			if (!(savefile << board.size() << "\n")) {
				throw (int)result::file_write_fail;
			}
			for (int i = 0; i < board.size(); ++i) {
				if (!(savefile << board[i].piece_display << "\n")) {
					throw (int)result::file_write_fail;
				}
			}
			if (!(savefile << "\n" << turn_counter)) {
				throw (int)result::file_write_fail;
			}
			savefile.close();

			if (savefile.is_open()) {
				throw (int)result::fail_close_file;
			}

			//return (int)result::success;
			return;

		}

	}
	
	
}