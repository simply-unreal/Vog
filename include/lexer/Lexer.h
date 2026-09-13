#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

enum class TokenType {
	/* BASIC */
	END_OF_FILE,
	UNKNOWN,
	NULL_LITERAL,

	IDENTIFIER,
	INT_LITERAL,
	FLOAT_LITERAL,
	CHAR_LITERAL,
	STRING_LITERAL,
	BOOL_LITERAL,

	/* OPERATORS */
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

	/* KEYWORDS */
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
	std::size_t offset = 0;
	std::size_t line = 1;
	std::size_t column = 1;
};

struct Token {
	TokenType type = TokenType::UNKNOWN;

	std::string_view value{};

	SourceLocation location{};
};

class Lexer {
public:
	explicit Lexer(std::string_view source); // Creates a lexer.

	Token next(); // Returns the next token and advances the lexer.

	const Token& peek(); // Returns the next token without advancing the lexer.

	std::vector<Token> tokenize(); // Returns a vector of tokenized source_

	bool is_at_end() const noexcept; // Returns true if lexer is at the end of the source.

	void reset(); // Resets the lexer to beginning of the source.

private:
	Token scan_token(); // Scans the next token based on current character.

	Token scan_identifer(); // Scans a identifier (or a keyword).

	Token scan_number(); // Scans a int literal (or floating point literal).

	Token scan_string(); // Scans a string literal including escape sequences.

	Token scan_char(); // Scans a char literal including escape sequences.

	Token scan_operator(); // Scans a operator.

	char current() const noexcept; // Returns current character

	char peek_char(std::size_t offset = 1) const noexcept; // Returns the character at given offset from current pos.

	bool match(char expected); // Consumes the current character if it matches the expected character.

	void advance(); // Advance the lexer by one character and updates the source location.

	void skip_whitespace(); // Skips whitespace.

	void skip_comment(); // Skips a comment.

	static TokenType keyword_type(std::string_view text) noexcept; // Returns the token associated with a keyword.

	Token make_token(TokenType type); // Creates a token from the current lexers token range.

	Token error_token(); // Creates a token representing a invalid character.

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