#pragma once
#include "GameBase.h"

class Reversi : public GameBase {
	friend std::ostream & operator << (std::ostream &, const Reversi &);

public:
	Reversi(std::string, std::string);
	void print();
	std::ostream & print_gameboard(std::ostream&) const;
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();

private:
	std::string player_black, player_white;
	gamepiece black_piece = gamepiece("black", piece_color::black, "X");                //fix
	gamepiece white_piece = gamepiece("white", piece_color::white, "O");                //initialize in constructor
	bool valid_move(int);
	bool valid_move(int, int, std::vector<int> &, std::string);
	bool propogate_check(int, int, int, int, std::string, std::vector<int> &);
	std::string player_Turn = "X"; //fix?
	bool turn_helper(std::string);
};