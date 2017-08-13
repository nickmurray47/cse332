//John Garza and Nicholas Murray

#pragma once
#include "GameBase.h"

#ifndef MAGICSQUARE_H
#define MAGICSQUARE_H

class MagicSquare : public GameBase {


public:
	MagicSquare();
	MagicSquare(int);
	MagicSquare(int, int, int);

	friend std::ostream & operator << (std::ostream&, const MagicSquare &);
	virtual void print();
	virtual bool stalemate();
	virtual bool done();
	std::ostream& print_gameboard(std::ostream&) const;
	virtual int prompt(int &);
	virtual int turn();

	bool filled_board_checker();
	bool sum_checker();

private:
	std::vector<gamepiece> available_pieces;
	std::vector<gamepiece> used_pieces;
};

//method definitions
//std::ostream & operator << (std::ostream&, const MagicSquare&);

#endif 