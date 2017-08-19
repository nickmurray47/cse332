//Lab 3 Nicholas Murray and John Garza

#include "stdafx.h"
#include "index.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

//take two parameters: reference to a vector of strings and a C-style string
int parse_input(vector<string> &v, const char *s) {

	//declare file stream and open C-style string (file)
	ifstream fstrm;
	fstrm.open(s);
	string line;

	// if the file stream object works
	if (fstrm.is_open()) {

		// as long as stream can extract strings
		while (fstrm >> line) {
			// push back extracted strings to vector
			v.push_back(line);
		}
	}

	else {

		// cast as an int in order to match return type
		return (int)result::fail_open_file;
	}

	fstrm.close();

	return (int)result::success;

}

// a usage function in case the wrong number of arguments is entered
int usage(char*program_name, int argc) {
	cout << "Usage: " << program_name << " NineAlmonds OR \n" << program_name << " MagicSquare [board dimension] [minimum piece value] OR \n" << program_name << " Reversi <Player1> <Player2>" << endl;
	// usage must return an int
	return (int)result::wrong_argc;
}

void make_lowercase(string &str) {
	std::locale loc;
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (std::isalpha(*it, loc))
		{
			if (std::isupper(*it, loc))
			{
				*it = *it + 32;
			}
			else
			{

			}
		}
	}
}

int str_to_int(string input) {

	stringstream converter(input);

	int result = 0;

	if (!(converter >> result)) {
		throw (int)result::extraction_fail;
	}

	return result;

}

void for_bounds_helper(int x, int y, int width, int height, int & width_low, int & width_high, int & height_low, int & height_high) {

/*	for (int search_width = (x - 1); search_width < (x + 2); ++search_width) { //TODO CHECK THE BOUNDS

		for (int search_height = (y - 1); search_height < (y + 2); ++search_height) {
		*/

	if (x - 1 >= 0) {
		width_low = x - 1;
	}
	else {
		width_low = 0;
	}

	if (x + 2 <= width) {
		width_high = x + 2;
	}
	else {
		width_high = width;
	}

	if (y - 1 >= 0) {
		height_low = y - 1;
	}
	else {
		height_low = 0;
	}

	if (y + 2 <= height) {
		height_high = y + 2;
	}
	else {
		height_high = height;
	}

}
