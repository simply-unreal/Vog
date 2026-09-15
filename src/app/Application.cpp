#include "app/Application.hpp"

#include "app/SourceLoader.hpp"
#include "cli/ArgumentParser.hpp"
#include "cli/Help.hpp"
#include "compiler/debugger/CompilerDebugger.hpp"
#include "lexer/Lexer.hpp"
#include "output/TokenPrinter.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace vog::app {

namespace {

int run_command(const Flags& options) {
    if (options.show_help) {
        cli::print_usage();
        return 0;
    }

    if (options.show_version) {
        std::cout << "Vog version 0.0.1\n";
        return 0;
    }

    const std::string source = load_source(options);
    Lexer lexer(source);
    const std::vector<Token> tokens = lexer.tokenize();

    if (options.show_tokens) {
        output::print_tokens(tokens);
        return 0;
    }

    if (options.enable_debugger) {
        CompilerDebugger debugger(tokens, source);
        debugger.run(1280, 720);
        return 0;
    }

    if (options.verbose) {
        std::cout << "Parsed " << tokens.size() << " tokens successfully.\n";
    }

    return 0;
}

}

int run(int argc, char* argv[]) {
    try {
        return run_command(parse_flags(argc, argv));
    }
    catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
}

}
