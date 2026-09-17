// __     __             ____
// \ \   / /__   __ _   / ___| _     _
//  \ \ / / _ \ / _` | | |   _| |_ _| |_
//   \ V / (_) | (_| | | |__|_   _|_   _|
//    \_/ \___/ \__, |  \____||_|   |_|
//              |___/
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// Copyright (c) 2026 Hunter Scott <simplyunreal323@gmail.com>.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

		int run_command(const Flags &options) {
			// Handle commands that do not require reading or lexing a source file first.
			if (options.show_help) {
				cli::print_usage();
				return 0;
			}

			if (options.show_version) {
				std::cout << "Vog version 0.0.1\n";
				return 0;
			}

			// Loading and lexing are deliberately kept together so every downstream view
			// observes the same immutable source and token sequence.
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

	} // namespace

	int run(int argc, char *argv[]) {
		// The public entry point keeps user-facing failures out of main().
		try {
			return run_command(parse_flags(argc, argv));
		} catch (const std::exception &error) {
			std::cerr << "error: " << error.what() << '\n';
			return 1;
		}
	}

} // namespace vog::app
