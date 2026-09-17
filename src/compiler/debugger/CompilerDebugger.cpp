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

#include "compiler/debugger/CompilerDebugger.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vog {

	CompilerDebugger::CompilerDebugger(std::vector<vog::Token> tokens, std::string_view source) {
		// Copy inputs because the debugger owns its display data for the window lifetime.
		scroll_offset = 0.0f;
		selected_token_index = 0;

		this->source = source;
		this->tokens = std::move(tokens);
	}

	void CompilerDebugger::run(unsigned int x, unsigned int y) {
		// Reject invalid dimensions before asking SFML to create a native window.
		if (x == 0 || y == 0) {
			throw std::invalid_argument("debugger window dimensions must be non-zero");
		}

		try {
			init_window(x, y);
		} catch (const std::exception &error) {
			std::cerr << "warning: unable to open compiler debugger window: " << error.what() << '\n';
			return;
		}

		// The event loop currently provides the stable shell for future editor rendering.
		while (window.isOpen()) {
			while (const std::optional event = window.pollEvent()) {
				event->visit([&](const auto &eventData) {
					using EventType = std::decay_t<decltype(eventData)>;
					if constexpr (std::is_same_v<EventType, sf::Event::Closed>) {
						window.close();
					}
				});
			}

			// Clear and present each frame even before drawing editor panels.
			window.clear(sf::Color::Black);
			window.display();
		}
	}

	void CompilerDebugger::init_window(unsigned int x, unsigned int y) {
		// Keep this guard here as well because this helper is independently callable.
		if (x == 0 || y == 0) {
			throw std::invalid_argument("window size cannot be zero");
		}

		window.create(
			sf::VideoMode(sf::Vector2u(x, y)),
			"Compiler Debugger");
	}

} // namespace vog