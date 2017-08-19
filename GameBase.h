//John Garza and Nicholas Murray

#pragma once

#include "gamepiece.h"
#include "game_board.h"
#include "index.h"


#include <iostream>
#include <memory> //for using a smart pointer 

#include <vector>
#include <fstream>
#include <string>

#ifndef GAMEBASE_H
#define GAMEBASE_H

class GameBase {

public:
	GameBase(int, int);
	GameBase(int, int, int);
	virtual void print() = 0;
	virtual bool stalemate() = 0;
	virtual bool done() = 0;

	virtual int prompt(unsigned int &, unsigned int &);

	virtual int turn() = 0;

	virtual int play();

	//initialize an instance of a game (based on command line arguments) and store in game_ptr
	static void arguments(int, char*[]);

	void save_game(); 

	static std::shared_ptr<GameBase> instance();

protected:
	std::vector<gamepiece> board;
	int width, height;
	unsigned int longest_piece;
	static std::shared_ptr<GameBase> game_ptr;
	int turn_counter;
	static std::string game_type;
	static bool loaded_from_file;
	static std::string player_turn;
};

#endif 