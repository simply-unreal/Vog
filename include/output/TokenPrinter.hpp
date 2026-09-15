#pragma once

#include "lexer/Lexer.hpp"

#include <vector>

namespace vog::output {

void print_tokens(const std::vector<Token>& tokens);

}
