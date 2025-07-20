#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Tree.hpp"
#include "Token.hpp"

class Parser {
private:
    std::vector<TokenPtr> tokens;
    size_t current;
    std::unordered_map<std::string, std::string> emojiMappings;
    
    void initializeEmojiMappings();
    TokenPtr peek();
    TokenPtr advance();
    bool match(const std::string& value);
    bool check(const std::string& value);
    bool isAtEnd();
    
    TreePtr parseStatement();
    TreePtr parseSimpleStatement();
    TreePtr parseCompoundStatement();
    TreePtr parseAssignmentStatement();
    TreePtr parseDeclareStatement();
    TreePtr parseFlowStatement();
    TreePtr parsePrintStatement();
    TreePtr parseIfStatement();
    TreePtr parseWhileStatement();
    TreePtr parseForStatement();
    TreePtr parseExpression();
    TreePtr parseLogicalOrExpression();
    TreePtr parseLogicalAndExpression();
    TreePtr parseInclusiveOrExpression();
    TreePtr parseExclusiveOrExpression();
    TreePtr parseAndExpression();
    TreePtr parseEqualityExpression();
    TreePtr parseAdditiveExpression();
    TreePtr parseMultiplicativeExpression();
    TreePtr parseCastExpression();
    TreePtr parseArgument();
    TreePtr parseSuite();
    TreePtr parseForDecl();
    TreePtr parseForTest();
    TreePtr parseForUpdates();
    
public:
    Parser();
    std::vector<TokenPtr> tokenize(const std::string& text);
    TreePtr parse(const std::string& text);
};
