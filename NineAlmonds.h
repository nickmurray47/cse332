#pragma once

#include "GameBase.h"
#include "gamepiece.h"
#include "game_board.h"
#include "index.h"
#include <iostream>
#ifndef NINEALMONDS_H
#define NINEALMONDS_H

//declare a class that implements a single player version of the Nine Almonds game  
class NineAlmonds : public GameBase {

public:
	NineAlmonds();
	//ostream operator declared as friend 
	friend std::ostream & operator << (std::ostream&, const NineAlmonds &);

	virtual void print() override;

	void print_starting_board();

	std::ostream& print_current_board(std::ostream&) const;

	// game play functions
	virtual bool done() override; //Lab 3 virtual 

	bool stalemate();

	virtual int prompt(unsigned int &, unsigned int &);

	virtual int turn();

	int valid_move(unsigned int &, unsigned int &, unsigned int &, unsigned int &);

	bool stale_move(int, int, int, int);

private: //member variables only visible in the above functions
		 // private member variables are 5x5 gameboard
	gamepiece almond = gamepiece("almond", piece_color::brown, "A");
	gamepiece empty = gamepiece("", piece_color::no_color, " ");
	int turn_counter = 0;
	int turn_result = 0;
};

//method definitions 
std::ostream & operator << (std::ostream&, const NineAlmonds &);

#endif