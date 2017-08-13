#pragma once

//Nicholas Murray and John Garza, Lab 3, header file for board dimensions and functions for printing board 

#include "functions.h"
#include "gamepiece.h"
#include <vector>
#include <fstream>

//declare a function for reading in the dimensions of a game board from an input file stream
int board_dimensions(std::ifstream &, unsigned int&, unsigned int&);

//declare a function for reading piece positions and characteristics from an input file stream 
int read_gamepiece(std::ifstream&, std::vector<gamepiece>&, unsigned int, unsigned int);

// declare a function for printing out pieces on the board
int print_pieces_board(const std::vector<gamepiece> &, unsigned int, unsigned int);