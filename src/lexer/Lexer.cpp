#include "lexer/Lexer.h"
#include <cctype>
#include <string_view>

static bool valid_digit_separator(std::string_view text) noexcept {
	if (text.empty())
		return false;

	if (text.front() == '_' || text.back() == '_')
		return false;

	for (std::size_t i = 0; i + 1 < text.size(); ++i) {
		if (text[i] == '_' && text[i + 1] == '_')
			return false;
	}

	return true;
}

Lexer::Lexer(std::string_view source) {
	source_ = source;
}

Token Lexer::next() {
	if (has_peeked_) {
		has_peeked_ = false;
		return peeked_token_;
	}

	return scan_token();
}

const Token& Lexer::peek() {
	if (!has_peeked_) {
		peeked_token_ = scan_token();
		has_peeked_ = true;
	}

	return peeked_token_;
}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;

	while (true) {
		Token token = next();
		tokens.push_back(token);

		if (token.type == TokenType::END_OF_FILE) {
			break;
		}
	}

	return tokens;
}

bool Lexer::is_at_end() const noexcept {
	return current_ >= source_.size();
}

void Lexer::reset() {
	start_ = 0;
	current_ = 0;

	line_ = 1;
	column_ = 1;

	token_offset_ = 0;
	token_line_ = 1;
	token_column_ = 1;

	has_peeked_ = false;
	peeked_token_ = {};
}

Token Lexer::scan_token() {
	start_ = current_;
	token_offset_ = current_;
	token_line_ = line_;
	token_column_ = column_;

	if (!skip_whitespace()) {
		return make_token(TokenType::UNKNOWN);
	}

	start_ = current_;
	token_offset_ = current_;
	token_line_ = line_;
	token_column_ = column_;

	if (is_at_end()) {
		return make_token(TokenType::END_OF_FILE);
	}

	const char c = current();

	if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
		return scan_identifier();
	}

	if (std::isdigit(static_cast<unsigned char>(c))) {
		return scan_number();
	}

	switch (c) {
	case '"':
		return scan_string();

	case '\'':
		return scan_char();

	default:
		return scan_operator();
	}
}

Token Lexer::scan_identifier() {
	while (true) {
		const char c = current();

		if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
			advance();
			continue;
		}

		break;
	}

	const std::string_view text = source_.substr(start_, current_ - start_);
	return make_token(keyword_type(text));
}

Token Lexer::scan_number() {
	if (current() == '0' &&
		(peek_char() == 'x' || peek_char() == 'X')) {

		advance();
		advance();

		const std::size_t digits_start = current_;

		while (std::isxdigit(static_cast<unsigned char>(current())) ||
			current() == '_') {
			advance();
		}

		const std::string_view digits =
			source_.substr(digits_start, current_ - digits_start);

		if (!valid_digit_separator(digits)) {
			return make_token(TokenType::UNKNOWN);
		}

		if (std::isalnum(static_cast<unsigned char>(current())) ||
			current() == '_') {

			while (std::isalnum(static_cast<unsigned char>(current())) ||
				current() == '_') {
				advance();
			}

			return make_token(TokenType::UNKNOWN);
		}

		return make_token(TokenType::INT_LITERAL);
	}

	if (current() == '0' &&
		(peek_char() == 'b' || peek_char() == 'B')) {

		advance();
		advance();

		const std::size_t digits_start = current_;

		while (current() == '0' ||
			current() == '1' ||
			current() == '_') {
			advance();
		}

		const std::string_view digits =
			source_.substr(digits_start, current_ - digits_start);

		if (!valid_digit_separator(digits)) {
			return make_token(TokenType::UNKNOWN);
		}

		if (std::isalnum(static_cast<unsigned char>(current())) || current() == '_') {

			while (std::isalnum(static_cast<unsigned char>(current())) ||
				current() == '_') {
				advance();
			}

			return make_token(TokenType::UNKNOWN);
		}

		return make_token(TokenType::INT_LITERAL);
	}

	const std::size_t integer_start = current_;

	while (std::isdigit(static_cast<unsigned char>(current())) || current() == '_') {
		advance();
	}

	const std::string_view integer_part = source_.substr(integer_start, current_ - integer_start);

	if (!valid_digit_separator(integer_part)) {
		return make_token(TokenType::UNKNOWN);
	}

	bool is_float = false;

	if (current() == '.') {
		is_float = true;
		advance();

		const std::size_t fraction_start = current_;

		while (std::isdigit(static_cast<unsigned char>(current())) || current() == '_') {
			advance();
		}

		const std::string_view fraction = source_.substr(fraction_start, current_ - fraction_start);

		if (!valid_digit_separator(fraction)) {
			return make_token(TokenType::UNKNOWN);
		}
	}

	if (current() == 'e' || current() == 'E') {
		is_float = true;
		advance();

		if (current() == '+' || current() == '-') {
			advance();
		}

		const std::size_t exponent_start = current_;

		while (std::isdigit(static_cast<unsigned char>(current())) || current() == '_') {
			advance();
		}

		const std::string_view exponent = source_.substr(exponent_start, current_ - exponent_start);

		if (!valid_digit_separator(exponent)) {
			return make_token(TokenType::UNKNOWN);
		}
	}

	if (std::isalpha(static_cast<unsigned char>(current())) ||
		current() == '_') {

		while (std::isalnum(static_cast<unsigned char>(current())) ||
			current() == '_') {
			advance();
		}

		return make_token(TokenType::UNKNOWN);
	}

	return make_token(is_float ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL);
}

Token Lexer::scan_string() {
	advance();

	while (!is_at_end()) {
		const char c = current();

		if (c == '"') {
			advance();
			return make_token(TokenType::STRING_LITERAL);
		}

		if (c == '\\') {
			advance();

			if (is_at_end()) {
				return make_token(TokenType::UNKNOWN);
			}

			switch (current()) {
			case 'n':
			case 'r':
			case 't':
			case '0':
			case '\\':
			case '"':
			case '\'':
				advance();
				break;

			default:
				advance();
				return make_token(TokenType::UNKNOWN);
			}

			continue;
		}

		if (c == '\n' || c == '\r') {
			return make_token(TokenType::UNKNOWN);
		}

		advance();
	}

	return make_token(TokenType::UNKNOWN);
}

Token Lexer::scan_char() {
	advance();

	if (is_at_end()) {
		return make_token(TokenType::UNKNOWN);
	}

	if (current() == '\\') {
		advance();

		if (is_at_end()) {
			return make_token(TokenType::UNKNOWN);
		}

		switch (current()) {
		case 'n':
		case 'r':
		case 't':
		case '0':
		case '\\':
		case '\'':
		case '"':
			advance();
			break;

		default:
			advance();
			return make_token(TokenType::UNKNOWN);
		}
	}
	else {
		if (current() == '\'' || current() == '\n' || current() == '\r') {
			return make_token(TokenType::UNKNOWN);
		}

		advance();
	}

	if (current() != '\'') {
		while (!is_at_end() && current() != '\'' && current() != '\n' && current() != '\r') {
			advance();
		}

		if (current() == '\'') {
			advance();
		}

		return make_token(TokenType::UNKNOWN);
	}

	advance();

	return make_token(TokenType::CHAR_LITERAL);
}

Token Lexer::scan_operator() {
	const char c = current();

	switch (c) {
	case '+':
		advance();

		if (match('+')) {
			return make_token(TokenType::INCREMENT);
		}

		if (match('=')) {
			return make_token(TokenType::PLUS_EQUAL);
		}

		return make_token(TokenType::PLUS);

	case '-':
		advance();

		if (match('-')) {
			return make_token(TokenType::DECREMENT);
		}

		if (match('=')) {
			return make_token(TokenType::MINUS_EQUAL);
		}

		if (match('>')) {
			return make_token(TokenType::ARROW);
		}

		return make_token(TokenType::MINUS);

	case '*':
		advance();
		return make_token(TokenType::STAR);

	case '/':
		advance();
		return make_token(TokenType::SLASH);

	case '%':
		advance();
		return make_token(TokenType::PERCENT);

	case '&':
		advance();

		if (match('&')) {
			return make_token(TokenType::AND);
		}

		if (match('=')) {
			return make_token(TokenType::AND_EQUAL);
		}

		return make_token(TokenType::BITWISE_AND);

	case '|':
		advance();

		if (match('|')) {
			return make_token(TokenType::OR);
		}

		if (match('=')) {
			return make_token(TokenType::OR_EQUAL);
		}

		return make_token(TokenType::BITWISE_OR);

	case '^':
		advance();

		if (match('=')) {
			return make_token(TokenType::XOR_EQUAL);
		}

		return make_token(TokenType::BITWISE_XOR);

	case '~':
		advance();
		return make_token(TokenType::BITWISE_NOT);

	case '=':
		advance();

		if (match('=')) {
			return make_token(TokenType::EQUAL_EQUAL);
		}

		return make_token(TokenType::EQUAL);

	case '!':
		advance();

		if (match('=')) {
			return make_token(TokenType::BANG_EQUAL);
		}

		return make_token(TokenType::NOT);

	case '<':
		advance();

		if (match('<')) {
			if (match('=')) {
				return make_token(TokenType::LEFT_SHIFT_EQUAL);
			}

			return make_token(TokenType::LEFT_SHIFT);
		}

		if (match('=')) {
			return make_token(TokenType::LESS_EQUAL);
		}

		return make_token(TokenType::LESS_THAN);

	case '>':
		advance();

		if (match('>')) {
			if (match('=')) {
				return make_token(TokenType::RIGHT_SHIFT_EQUAL);
			}

			return make_token(TokenType::RIGHT_SHIFT);
		}

		if (match('=')) {
			return make_token(TokenType::GREATER_EQUAL);
		}

		return make_token(TokenType::GREATER_THAN);

	case '(':
		advance();
		return make_token(TokenType::LPAREN);

	case ')':
		advance();
		return make_token(TokenType::RPAREN);

	case '{':
		advance();
		return make_token(TokenType::LBRACE);

	case '}':
		advance();
		return make_token(TokenType::RBRACE);

	case '[':
		advance();
		return make_token(TokenType::LBRACKET);

	case ']':
		advance();
		return make_token(TokenType::RBRACKET);

	case ',':
		advance();
		return make_token(TokenType::COMMA);

	case '.':
		advance();
		return make_token(TokenType::DOT);

	case ':':
		advance();
		return make_token(TokenType::COLON);

	case ';':
		advance();
		return make_token(TokenType::SEMICOLON);

	case '?':
		advance();

		if (match('?')) {
			return make_token(TokenType::QUESTION_QUESTION);
		}

		return make_token(TokenType::QUESTION);

	default:
		return error_token();
	}
}

char Lexer::current() const noexcept {
	if (is_at_end()) {
		return '\0';
	}

	return source_[current_];
}

char Lexer::peek_char(std::size_t offset) const noexcept {
	const std::size_t index = current_ + offset;

	if (index >= source_.size()) {
		return '\0';
	}

	return source_[index];
}

bool Lexer::match(char expected) {
	if (is_at_end() || current() != expected) {
		return false;
	}

	advance();
	return true;
}

void Lexer::advance() {
	if (is_at_end()) {
		return;
	}

	const char c = source_[current_++];

	if (c == '\n') {
		++line_;
		column_ = 1;
	}
	else {
		++column_;
	}
}

bool Lexer::skip_whitespace() {
	for (;;) {
		while (!is_at_end()) {
			const char c = current();

			if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n') {
				advance();
			}
			else {
				break;
			}
		}

		const std::size_t before_comment = current_;

		if (!skip_comment()) {
			start_ = before_comment;
			token_offset_ = before_comment;

			return false;
		}

		if (current_ == before_comment) {
			break;
		}
	}

	return true;
}

bool Lexer::skip_comment() {
	if (current() != '/') {
		return true;
	}

	if (peek_char() == '/') {
		advance();
		advance();

		while (!is_at_end() && current() != '\n') {
			advance();
		}

		return true;
	}

	if (peek_char() == '*') {
		advance();
		advance();

		while (!is_at_end()) {
			if (current() == '*' && peek_char() == '/') {
				advance();
				advance();
				return true;
			}

			advance();
		}

		return false;
	}

	return true;
}

TokenType Lexer::keyword_type(std::string_view text) noexcept {
	if (text == "null")       return TokenType::NULL_LITERAL;
	if (text == "true")       return TokenType::BOOL_LITERAL;
	if (text == "false")      return TokenType::BOOL_LITERAL;

	if (text == "const")      return TokenType::CONST;

	if (text == "i8")         return TokenType::I8;
	if (text == "i16")        return TokenType::I16;
	if (text == "i32")        return TokenType::I32;
	if (text == "i64")        return TokenType::I64;

	if (text == "u8")         return TokenType::U8;
	if (text == "u16")        return TokenType::U16;
	if (text == "u32")        return TokenType::U32;
	if (text == "u64")        return TokenType::U64;

	if (text == "f32")        return TokenType::F32;
	if (text == "f64")        return TokenType::F64;

	if (text == "char")       return TokenType::CHAR;
	if (text == "void")       return TokenType::VOID;

	if (text == "fn")         return TokenType::FN;
	if (text == "struct")     return TokenType::STRUCT;
	if (text == "class")      return TokenType::CLASS;
	if (text == "enum")       return TokenType::ENUM;

	if (text == "if")         return TokenType::IF;
	if (text == "else")       return TokenType::ELSE;
	if (text == "while")      return TokenType::WHILE;
	if (text == "for")        return TokenType::FOR;
	if (text == "return")     return TokenType::RETURN;
	if (text == "break")      return TokenType::BREAK;
	if (text == "continue")   return TokenType::CONTINUE;

	if (text == "do")         return TokenType::DO;
	if (text == "switch")     return TokenType::SWITCH;
	if (text == "case")       return TokenType::CASE;
	if (text == "default")    return TokenType::DEFAULT;

	if (text == "import")     return TokenType::IMPORT;
	if (text == "from")       return TokenType::FROM;

	if (text == "new")        return TokenType::NEW;
	if (text == "delete")     return TokenType::DELETE;

	return TokenType::IDENTIFIER;
}

Token Lexer::make_token(TokenType type) {
	Token token;

	token.type = type;
	token.value = source_.substr(start_, current_ - start_);

	token.location.offset = token_offset_;
	token.location.line = token_line_;
	token.location.column = token_column_;

	return token;
}

Token Lexer::error_token() {
	if (!is_at_end()) {
		advance();
	}

	return make_token(TokenType::UNKNOWN);
}