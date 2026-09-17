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

#pragma once

#include <SFML/Graphics.hpp>

#include "lexer/Lexer.hpp"

#include <string>
#include <vector>

namespace vog {

	// Displays information inside a small interactive SFML window.
	class CompilerDebugger {
	  public:
		CompilerDebugger(std::vector<vog::Token> tokens, std::string_view source);

		void run(unsigned int x, unsigned int y);

	  private:
		void init_window(unsigned int x, unsigned int y);
		bool load_font(const std::string &font_path);

		void process_events();
		void handle_event(const sf::Event &event);
		void update();
		void render();

		void draw_source_code();
		void draw_line_numbers();
		void draw_tokens();
		void draw_selection();

		void handle_mouse_click(const sf::Event::MouseButtonPressed &event);
		void handle_key_press(const sf::Event::KeyPressed &event);
		void scroll_source(float amount);

		sf::Color get_token_color(TokenType type) const;
		std::size_t get_line_from_offset(std::size_t offset) const;

	  private:
		sf::RenderWindow window;
		sf::Font font;

		std::string source;
		std::vector<Token> tokens;

		std::size_t selected_token_index;
		float scroll_offset;
	};

} // namespace vog