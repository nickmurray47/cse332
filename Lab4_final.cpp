// Lab3_Murray_Garza.cpp : Defines the entry point for the console application.
//John Garza and Nicholas Murray

#include "stdafx.h"
#include "GameBase.h"
#include "NineAlmonds.h"
#include "Reversi.h"

using namespace std;

int main(int argc, char * argv[])
{
	
	try {
		GameBase::arguments(argc, argv);
	}
	catch (int e)
	{
		if (e == (int)result::wrong_argc) {
			return usage(argv[(int)indices::program_name], (int)indices::game_name);

		}
		else if (e == (int)exceptions::game_set) {
			cout << "Game is already set" << endl;
			return e;
		}
		else if (e == (int)result::extraction_fail) {
			cout << "A system error occurred, please try again" << endl;
			return e;
		}
		else if (e == (int)result::unrecognized_arg) {
			cout << "Unrecognized argument" << endl;
			return usage(argv[(int)indices::program_name], (int)indices::game_name);
		}
	}

	shared_ptr<GameBase> get_game;
	int result = 0;

	try {
		get_game = GameBase::instance();
	}
	catch (int e)
	{
		if (e == (int)result::extraction_fail) {
			return e;
		}
		else if (e == (int)exceptions::game_not_set) {
			cout << "Game is not set" << endl;
			return e;
		}
		else {
			return e;
		}
	}

	
	try {
		result = get_game->play();
	}
	catch (int e)
	{
		if (e == (int)result::extraction_fail) {
			return e;
		}
		else if (e == (int)exceptions::game_not_set) {
			cout << "Game is not set" << endl;
			return e;
		}

		else if (e == (int)result::fail_open_file) {
			return e;
		}
		else if (e == (int)result::file_write_fail) {
			return e;
		}
		else if (e == (int)result::fail_close_file) {
			return e;
		}


		else {
			return e;
		}
	}


	if (result != (int)result::success) {
		return result;
	}

	return (int)result::success;

}

