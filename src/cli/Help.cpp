#include "cli/Help.hpp"

#include <iostream>

namespace vog::cli {

void print_usage() {
    std::cout
        << "Usage: Vog [options] [input_file]\n"
        << "  -h, --help                 Show help\n"
        << "  -V, --version              Show version\n"
        << "  -v, --verbose              Enable verbose output\n"
        << "  -o, --output <file>        Write output to file\n"
        << "  --emit <exe|obj|asm>       Set output format\n"
        << "  --target <target>          Set target triple\n"
        << "  -O0|-O1|-O2|-O3            Set optimization level\n"
        << "  -g, --debug                Enable debug output\n"
        << "  -d, --debugger             Launch the visual compiler debugger\n"
        << "  --tokens                   Show token stream\n"
        << "  --ast                      Show AST\n"
        << "  --ir                       Show IR\n"
        << "  --color                    Enable colorized diagnostics\n"
        << "  --no-color                 Disable colorized diagnostics\n"
        << "  --error-limit <n>          Set diagnostic limit\n";
}

}
