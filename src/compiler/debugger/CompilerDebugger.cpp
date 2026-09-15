#include "compiler/debugger/CompilerDebugger.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vog {

CompilerDebugger::CompilerDebugger(std::vector<vog::Token> tokens, std::string_view source) {
	scroll_offset = 0.0f;
	selected_token_index = 0;

	this->source = source;
	this->tokens = std::move(tokens);
}

void CompilerDebugger::run(unsigned int x, unsigned int y) {
	if (x == 0 || y == 0) {
		throw std::invalid_argument("debugger window dimensions must be non-zero");
	}

	try {
		init_window(x, y);
	}
	catch (const std::exception& error) {
		std::cerr << "warning: unable to open compiler debugger window: " << error.what() << '\n';
		return;
	}

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			event->visit([&](const auto& eventData) {
				using EventType = std::decay_t<decltype(eventData)>;
				if constexpr (std::is_same_v<EventType, sf::Event::Closed>) {
					window.close();
				}
			});
		}

		window.clear(sf::Color::Black);
		window.display();
	}
}

void CompilerDebugger::init_window(unsigned int x, unsigned int y) {
	if (x == 0 || y == 0) {
		throw std::invalid_argument("window size cannot be zero");
	}

	window.create(
		sf::VideoMode(sf::Vector2u(x, y)),
		"Compiler Debugger"
	);
}

}