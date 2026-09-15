#include "Vog.hpp"

int main() {
	const std::string source = R"(
		const i32 answer = 1_000_000;
		const u64 hex = 0xDEAD_BEEF;
		const u8 binary = 0b1010_1100;

		const f64 pi = 3.141_592;
		const f32 scientific = 6.02e23;
		const f64 negative = 1.5e-10;
		const f64 positive = 2.5E+4;

		const char newline = '\n';
		const char tab = '\t';
		const char zero = '\0';
		const char slash = '\\';
		const char quote = '\'';

		const char* hello = "Hello, world!";
		const char* escaped = "line1\nline2\t\"quoted\"\\slash";

		answer += 10;
		answer -= 5;
		answer++;
		answer--;
		answer = answer + 1;
		answer = answer - 1;
		answer = answer * 2;
		answer = answer / 2;
		answer = answer % 2;

		x = a & b | c ^ d;
		x &= a;
		x |= b;
		x ^= c;
		x = ~x;

		x <<= 2;
		x >>= 1;

		if (x == y) {}
		if (x != y) {}
		if (x < y) {}
		if (x > y) {}
		if (x <= y) {}
		if (x >= y) {}

		value = a ?? b;

		fn test(i32 a, f64 b) -> void {
			return;
		}

		struct Vec2 {
			f64 x;
			f64 y;
		}

		class Player {
			i32 health;
			i32 mana;
		}

		enum Color {
			RED,
			GREEN,
			BLUE
		}

		if (true) {
			while (false) {
				break;
			}
		}
		else {
			for (i32 i = 0; i < 10; i++) {
				continue;
			}
		}

		do {
			x++;
		} while (x < 100);

		switch (x) {
			case 0:
				return;
			default:
				break;
		}

		import thing from module;

		const i32* ptr = new i32;
		delete ptr;

		// Single-line comment

		/*
			Block comment.
			This should produce no tokens.
		*/

		foo
		foo123
		_foo
		foo_bar
		__internal

		( ) { } [ ] , . : ; ?
	)";

	Lexer lexer(source);

	std::vector<Token> tokens = lexer.tokenize();

	for (const Token& token : tokens) {
		std::cout << "Type: " << magic_enum::enum_name(token.type)
			<< " | Value: [" << token.value << ']'
			<< " | Line: " << token.location.line
			<< " | Column: " << token.location.column
			<< " | Offset: " << token.location.offset << '\n';
	}

	return 0;
}