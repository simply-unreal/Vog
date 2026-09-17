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

#include "app/SourceLoader.hpp"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace vog::app {

	std::string load_source(const Flags &options) {
		if (options.input_file.empty()) {
			// A small valid program keeps the CLI useful when invoked without a path.
			return R"(
        fn main() {
            i32 x = 42;
            i32 y = x + 10;
            return y;
        }
    )";
		}

		// Use binary mode so the lexer receives the file bytes without stream translation.
		const std::filesystem::path input_path(options.input_file);
		std::ifstream input(input_path, std::ios::binary);
		if (!input) {
			throw std::runtime_error(
				"failed to open input file: " + input_path.string() + " (working directory: " + std::filesystem::current_path().string() + ")");
		}

		return std::string(
			std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>());
	}

} // namespace vog::app
