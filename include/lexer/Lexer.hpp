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

#include <cstdint>
#include <string>
#include <string_view>

enum class TokenType {
	// SPECIAL AND LITERALS //
	END_OF_FILE,
	UNKNOWN,
	NULL_LITERAL,

	IDENTIFIER,
	INT_LITERAL,
	FLOAT_LITERAL,
	CHAR_LITERAL,
	STRING_LITERAL,
	BOOL_LITERAL,

	// OPERATORS //
	PLUS, // +
	MINUS, // -
	STAR, // *
	SLASH, // /
	PERCENT, // %
	BITWISE_AND, // &
	BITWISE_OR, // |
	BITWISE_XOR, // ^
	BITWISE_NOT, // ~
	EQUAL, // =
	PLUS_EQUAL, // +=
	MINUS_EQUAL, // -=
	LEFT_SHIFT, // <<
	RIGHT_SHIFT, // >>
	LEFT_SHIFT_EQUAL, // <<=
	RIGHT_SHIFT_EQUAL, // >>=
	EQUAL_EQUAL, // ==
	BANG_EQUAL, // !=
	LESS_THAN, // <
	GREATER_THAN, // >
	LESS_EQUAL, // <=
	GREATER_EQUAL, // >=
	AND_EQUAL, // &=
	OR_EQUAL, // |=
	XOR_EQUAL, // ^=
	AND, // &&
	OR, // ||
	NOT, // !
	INCREMENT, // ++
	DECREMENT, // --
	ARROW, // ->
	LPAREN, // (
	RPAREN, // )
	LBRACE, // {
	RBRACE, // }
	LBRACKET, // [
	RBRACKET, // ]
	COMMA, // ,
	DOT, // .
	COLON, // :
	SEMICOLON, // ;
	QUESTION, // ?
	QUESTION_QUESTION, // ??

	// KEYWORDS //
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

struct Span {
	uint64_t start;
	uint64_t end;
};

struct Token {
	TokenType type;
	Span location;
	std::string_view value;
};

class Lexer {
private:
	std::string_view source;
	uint64_t pos = 0;
};