#pragma once
#include <string>
#include <memory>

enum class TokenType {
    STRING,
    NUMBER,
    NAME,
    BOOLEAN,
    OPERATOR,
    KEYWORD,
    DELIMITER,
    END_OF_FILE
};

class Token {
public:
    TokenType type;
    std::string value;
    int line;
    int column;
    
    Token(TokenType t, const std::string& v, int l = 0, int c = 0);
    std::string toString() const;
    bool operator==(const std::string& str) const;
    bool operator==(const Token& other) const;
};

using TokenPtr = std::shared_ptr<Token>;
