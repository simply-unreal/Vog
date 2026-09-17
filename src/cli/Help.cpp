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

#include "cli/Help.hpp"

#include <iostream>

namespace vog::cli {

	void print_usage() {
		// Keep the help text in one stream expression so spacing remains deterministic.
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

} // namespace vog::cli
