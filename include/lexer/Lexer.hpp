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

#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace vog {

	enum class TokenType {
		// Basic literals and identifiers.
		END_OF_FILE,
		UNKNOWN,
		NULL_LITERAL,

		IDENTIFIER,
		INT_LITERAL,
		FLOAT_LITERAL,
		CHAR_LITERAL,
		STRING_LITERAL,
		BOOL_LITERAL,

		// Arithmetic, bitwise, comparison, and punctuation tokens.
		PLUS,
		MINUS,
		STAR,
		SLASH,
		PERCENT,
		BITWISE_AND,
		BITWISE_OR,
		BITWISE_XOR,
		BITWISE_NOT,
		EQUAL,
		PLUS_EQUAL,
		MINUS_EQUAL,
		LEFT_SHIFT,
		RIGHT_SHIFT,
		LEFT_SHIFT_EQUAL,
		RIGHT_SHIFT_EQUAL,
		EQUAL_EQUAL,
		BANG_EQUAL,
		LESS_THAN,
		GREATER_THAN,
		LESS_EQUAL,
		GREATER_EQUAL,
		AND_EQUAL,
		OR_EQUAL,
		XOR_EQUAL,
		AND,
		OR,
		NOT,
		INCREMENT,
		DECREMENT,
		ARROW,
		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		LBRACKET,
		RBRACKET,
		COMMA,
		DOT,
		COLON,
		SEMICOLON,
		QUESTION,
		QUESTION_QUESTION,

		// Reserved words recognized by the language.
		CONST,
		I8,
		I16,
		I32,
		I64,
		U8,
		U16,
		U32,
		U64,
		F32,
		F64,
		CHAR,
		VOID,
		FN,
		STRUCT,
		CLASS,
		ENUM,
		IF,
		ELSE,
		WHILE,
		FOR,
		RETURN,
		BREAK,
		CONTINUE,
		DO,
		SWITCH,
		CASE,
		DEFAULT,
		IMPORT,
		FROM,
		NEW,
		DELETE
	};

	struct SourceLocation {
		// Source positions are one-based for lines and columns, while offsets are zero-based.
		std::size_t offset = 0;
		std::size_t line = 1;
		std::size_t column = 1;
	};

	struct Token {
		// A token preserves both its semantic category and original source spelling.
		TokenType type = TokenType::UNKNOWN;
		std::string value{};
		SourceLocation location{};
	};

	class Lexer {
	  public:
		// Creates a lexer whose views refer to the supplied source text.
		explicit Lexer(std::string_view source);

		// Consumes and returns the next token.
		Token next();
		// Returns the next token without consuming it.
		const Token &peek();
		// Consumes tokens through the end-of-file marker.
		std::vector<Token> tokenize();
		// Reports whether all source characters have been consumed.
		bool is_at_end() const noexcept;
		// Restores the lexer to its initial position.
		void reset();

	  private:
		Token scan_token();
		Token scan_identifier();
		Token scan_number();
		Token scan_string();
		Token scan_char();
		Token scan_operator();
		char current() const noexcept;
		char peek_char(std::size_t offset = 1) const noexcept;
		bool match(char expected);
		void advance();
		bool skip_whitespace();
		bool skip_comment();
		static TokenType keyword_type(std::string_view text) noexcept;
		Token make_token(TokenType type);
		Token error_token();

	  private:
		std::string_view source_;
		std::size_t start_ = 0;
		std::size_t current_ = 0;
		std::size_t line_ = 1;
		std::size_t column_ = 1;
		std::size_t token_offset_ = 0;
		std::size_t token_line_ = 1;
		std::size_t token_column_ = 1;
		bool has_peeked_ = false;
		Token peeked_token_{};
	};

} // namespace vog