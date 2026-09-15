#include "output/TokenPrinter.hpp"

#include "third_party/magic_enum/magic_enum.hpp"

#include <iostream>

namespace vog::output {

void print_tokens(const std::vector<Token>& tokens) {
    for (std::size_t index = 0; index < tokens.size(); ++index) {
        const Token& token = tokens[index];
        std::cout << index << ": "
                  << magic_enum::enum_name(token.type)
                  << " \"" << token.value << "\"\n";
    }
}

}
