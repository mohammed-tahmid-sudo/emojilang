#include "Token.hpp"

Token::Token(TokenType t, const std::string& v, int l, int c) 
    : type(t), value(v), line(l), column(c) {}

std::string Token::toString() const {
    return value;
}

bool Token::operator==(const std::string& str) const {
    return value == str;
}

bool Token::operator==(const Token& other) const {
    return type == other.type && value == other.value;
}
