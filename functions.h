#pragma once

// Nicholas Murray and John Garza Lab 3, file from first lab  

#include <string>
#include <vector>

//function for parsing input 
int parse_input(std::vector<std::string> &, const char*);

// usage function
int usage(char*, int);

//function to take a reference to a C++ style string and changes it to lowercase
void make_lowercase(std::string &);

int str_to_int(std::string);