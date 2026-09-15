#pragma once

#include <string>
#include <vector>

namespace vog {

struct Flags {
	bool show_help = false;
	bool show_version = false;
	bool verbose = false;

	std::string input_file;
	std::string output_file;

	std::string emit;
	std::string target;

	int optimization_level = 0;
	bool debug = false;

	bool Wall = false;
	bool Wextra = false;
	bool Werror = false;
	std::vector<std::string> disable_warnings;

	bool show_tokens = false;
	bool show_ast = false;
	bool show_ir = false;
	bool enable_debugger = false;

	bool color = true;
	unsigned int error_limit = 20;
};

using flags = Flags;

}