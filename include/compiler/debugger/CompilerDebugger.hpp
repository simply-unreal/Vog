#pragma once

#include <SFML/Graphics.hpp>

#include "lexer/Lexer.hpp"

#include <string>
#include <vector>

namespace vog {

class CompilerDebugger {
public:
	CompilerDebugger(std::vector<vog::Token> tokens, std::string_view source);

	void run(unsigned int x, unsigned int y);

private:
	void init_window(unsigned int x, unsigned int y);
	bool load_font(const std::string& font_path);

	void process_events();
	void handle_event(const sf::Event& event);
	void update();
	void render();

	void draw_source_code();
	void draw_line_numbers();
	void draw_tokens();
	void draw_selection();

	void handle_mouse_click(const sf::Event::MouseButtonPressed& event);
	void handle_key_press(const sf::Event::KeyPressed& event);
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

}