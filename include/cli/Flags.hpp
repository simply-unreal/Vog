// __     __             ____
// \ \   / /__   __ _   / ___| _     _
//  \ \ / / _ \ / _` | | |   _| |_ _| |_
//   \ V / (_) | (_| | | |__|_   _|_   _|
//    \_/ \___/ \__, |  \____||_|   |_|
//              |___/
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// Copyright (c) 2026 Hunter Scott <simplyunreal323@gmail.com>.
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense,  and/or  sell
// copies  of the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR
// IMPLIED, INCLUDING BUT NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE LIABLE FOR ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <string>
#include <vector>

namespace vog {

	struct Flags {
		// General command selection and output settings.
		bool show_help = false;
		bool show_version = false;
		bool verbose = false;

		// Input and output paths are empty when the corresponding option is omitted.
		std::string input_file;
		std::string output_file;

		std::string emit;
		std::string target;

		// Compiler behavior and diagnostics.
		int optimization_level = 0;
		bool debug = false;

		bool Wall = false;
		bool Wextra = false;
		bool Werror = false;
		std::vector<std::string> disable_warnings;

		// Optional compiler introspection views.
		bool show_tokens = false;
		bool show_ast = false;
		bool show_ir = false;
		bool enable_debugger = false;

		bool color = true;
		unsigned int error_limit = 20;
	};

	using flags = Flags;

} // namespace vog