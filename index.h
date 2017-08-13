#pragma once

// Nicholas Murray and John Garza, Lab 3, header file for errors and other enumerations

//array indices
enum class indices { program_name = 0, game_name = 1, max_argc };

enum class result {
	success = 0, fail_open_file = -1, wrong_argc = -2, getline_err = -3, extraction_fail = -4,
	piece_failure = -5, bad_dimensions = -6, no_valid_move = -7, square_out = -8, switch_piece = -9, user_quit = -10,
	stalemate = -11, piece_already_placed = -12, unrecognized_arg = -13, file_write_fail = -14, fail_close_file = -15
};

enum class exceptions {
	game_set = -1, game_not_set = -2
};

enum class params {
	default_size = 3, default_piece = 1, default_space = 2, min = 2, middle = 3, max = 4
};