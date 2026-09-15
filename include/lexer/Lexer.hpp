#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace vog {

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
	std::string value{};
	SourceLocation location{};
};

class Lexer {
public:
	explicit Lexer(std::string_view source);

	Token next();
	const Token& peek();
	std::vector<Token> tokenize();
	bool is_at_end() const noexcept;
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