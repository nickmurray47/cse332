// Nicholas Murray and John Garza, Lab 3 Gamepiece file for gamepiece struct and functions

#include "stdafx.h"
#include "gamepiece.h"
#include "functions.h"
#include <iostream>

using namespace std;

// we pass pc, an enum of type piece_color
string piece_to_lower(piece_color pc) {

	//check each case, hard-coded and from piazza post 
	switch (pc)
	{
	case piece_color::red:
		return "red";
	case piece_color::black:
		return "black";
	case piece_color::white:
		return "white";
	case piece_color::invalid:
		return "invalid";
	case piece_color::no_color:
		return "no color given";
	default:
		return "nothing";
		break;
	}

}

piece_color pc_to_string(std::string str) {

	make_lowercase(str);
	if (str == "red") {
		return piece_color::red;
	}
	else if (str == "black") {
		return piece_color::black;
	}
	else if (str == "white") {
		return piece_color::white;
	}
	else if (str == " " || "") {
		return piece_color::no_color;
	}
	else {
		return piece_color::invalid;
	}

}

//define a struct to represent a game piece
gamepiece::gamepiece(string name, piece_color color, string display)
	: piece_name(name), gp_color(color), piece_display(display)
{}

// default gamepiece for printing an empty board 
gamepiece::gamepiece()
	: piece_name(""), gp_color(piece_color::no_color), piece_display(" ")
{}

//used this function to check that pieces were correct 
ostream & operator<< (ostream &o,
	const gamepiece&p) {
	o << p.piece_name << " " << p.piece_display; // space delimited
	return o;
}

bool operator==(const gamepiece&a, const gamepiece&b) {
	if (a.piece_display == b.piece_display) {
		//if (a.piece_name == b.piece_name) {
			return true;
		//}
	}
	return false;
}