#pragma once
// Nicholas Murray and John Garza, Lab 3, header file for game pieces and declarations

#include <string>

// enum for different piece colors
enum class piece_color { red, black, white, invalid, no_color, brown };

// function that returns a string, takes an enum piece_color 
std::string piece_to_lower(piece_color);

piece_color pc_to_string(std::string);

//declare a struct to represent a game piece 

struct gamepiece {
	std::string piece_name; // name of a piece
	piece_color gp_color; // game piece color 
	std::string piece_display; // represent how the piece should be displayed when a game board containing it is printed out

	gamepiece();
	gamepiece(std::string, piece_color, std::string);
};

std::ostream & operator<< (std::ostream &,
	const gamepiece &);

bool operator==(const gamepiece&a, const gamepiece&b);