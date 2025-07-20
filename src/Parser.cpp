#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

Parser::Parser() : current(0) {
    initializeEmojiMappings();
}

void Parser::initializeEmojiMappings() {
    emojiMappings = {
        {"📢", "decl"},
        {"😌", "="},
        {"🗿", ","},
        {"👄", ";"},
        {"🖨", "print"},
        {"👉", "("},
        {"👈", ")"},
        {"🍽", "{"},
        {"🥂", "}"},
        {"💿", "while"},
        {"📀", "for"},
        {"🚩", "if"},
        {"🏳", "elif"},
        {"🏁", "else"},
        {"⏸", "break"},
        {"⏩", "continue"},
        {"✔", "true"},
        {"❌", "false"},
        {"➕", "+"},
        {"➖", "-"},
        {"✖", "*"},
        {"➗", "/"},
        {"📎", "%"},
        {"😭", "<"},
        {"😁", ">"},
        {"😁😌", ">="},
        {"😭😌", "<="},
        {"😌😌", "=="},
        {"❗😌", "!="},
        {"⚛", "&"},
        {"☯", "|"},
        {"⚓", "xor"},
        {"😠", "and"},
        {"😇", "or"},
        {"❗", "!"},
        {"〰", "~"}
    };
}

std::vector<TokenPtr> Parser::tokenize(const std::string& text) {
    std::vector<TokenPtr> result;
    std::string::size_type pos = 0;
    
    while (pos < text.length()) {
        // Skip whitespace
        if (std::isspace(text[pos])) {
            pos++;
            continue;
        }
        
        // Skip comments (💩)
        if (pos < text.length()) {
            // Check for UTF-8 comment emoji (💩 is 4 bytes in UTF-8: F0 9F 92 A9)
            if (pos + 4 <= text.length() && 
                (unsigned char)text[pos] == 0xF0 && 
                (unsigned char)text[pos+1] == 0x9F && 
                (unsigned char)text[pos+2] == 0x92 && 
                (unsigned char)text[pos+3] == 0xA9) {
                // Skip to end of line
                while (pos < text.length() && text[pos] != '\n') {
                    pos++;
                }
                continue;
            }
        }
        
        // Handle string literals
        if (text[pos] == '"') {
            pos++;
            std::string str;
            while (pos < text.length() && text[pos] != '"') {
                str += text[pos++];
            }
            if (pos < text.length()) pos++; // Skip closing quote
            result.push_back(std::make_shared<Token>(TokenType::STRING, str));
            continue;
        }
        
        // Handle numbers
        if (std::isdigit(text[pos]) || (text[pos] == '-' && pos + 1 < text.length() && std::isdigit(text[pos + 1]))) {
            std::string num;
            if (text[pos] == '-') {
                num += text[pos++];
            }
            while (pos < text.length() && (std::isdigit(text[pos]) || text[pos] == '.')) {
                num += text[pos++];
            }
            result.push_back(std::make_shared<Token>(TokenType::NUMBER, num));
            continue;
        }
        
        // Handle identifiers
        if (std::isalpha(text[pos]) || text[pos] == '_') {
            std::string id;
            while (pos < text.length() && (std::isalnum(text[pos]) || text[pos] == '_')) {
                id += text[pos++];
            }
            result.push_back(std::make_shared<Token>(TokenType::NAME, id));
            continue;
        }
        
        // Handle multi-character emojis first
        bool foundEmoji = false;
        for (const auto& mapping : emojiMappings) {
            if (pos + mapping.first.length() <= text.length() && 
                text.substr(pos, mapping.first.length()) == mapping.first) {
                result.push_back(std::make_shared<Token>(TokenType::OPERATOR, mapping.first));
                pos += mapping.first.length();
                foundEmoji = true;
                break;
            }
        }
        
        if (!foundEmoji) {
            // Handle single characters
            std::string ch(1, text[pos]);
            result.push_back(std::make_shared<Token>(TokenType::OPERATOR, ch));
            pos++;
        }
    }
    
    result.push_back(std::make_shared<Token>(TokenType::END_OF_FILE, ""));
    return result;
}

TreePtr Parser::parse(const std::string& text) {
    tokens = tokenize(text);
    current = 0;
    
    auto root = std::make_shared<Tree>("stmt");
    
    while (!isAtEnd()) {
        auto stmt = parseStatement();
        if (stmt) {
            root->addChild(stmt);
        }
    }
    
    return root;
}

TokenPtr Parser::peek() {
    if (current >= tokens.size()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE, "");
    }
    return tokens[current];
}

TokenPtr Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::match(const std::string& value) {
    if (check(value)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(const std::string& value) {
    if (isAtEnd()) return false;
    return peek()->value == value;
}

bool Parser::isAtEnd() {
    return current >= tokens.size() || peek()->type == TokenType::END_OF_FILE;
}

// Simplified parsing implementation
TreePtr Parser::parseStatement() {
    if (check("📢")) return parseDeclareStatement();
    if (check("🖨")) return parsePrintStatement();
    if (check("🚩")) return parseIfStatement();
    if (check("💿")) return parseWhileStatement();
    if (check("📀")) return parseForStatement();
    if (check("⏸") || check("⏩")) return parseFlowStatement();
    
    // Try assignment
    if (peek()->type == TokenType::NAME && tokens.size() > current + 1 && tokens[current + 1]->value == "😌") {
        return parseAssignmentStatement();
    }
    
    return parseExpression();
}

TreePtr Parser::parseSimpleStatement() {
    return parseStatement();
}

TreePtr Parser::parseCompoundStatement() {
    if (check("🚩")) return parseIfStatement();
    if (check("💿")) return parseWhileStatement();
    if (check("📀")) return parseForStatement();
    return nullptr;
}

TreePtr Parser::parseAssignmentStatement() {
    auto stmt = std::make_shared<Tree>("assignment_stmt");
    
    auto nameTree = std::make_shared<Tree>("name");
    nameTree->addChild(advance());
    stmt->addChild(nameTree);
    
    advance(); // consume "😌"
    stmt->addChild(parseExpression());
    
    return stmt;
}

TreePtr Parser::parseDeclareStatement() {
    auto stmt = std::make_shared<Tree>("declare_stmt");
    advance(); // consume "📢"
    
    auto nameTree = std::make_shared<Tree>("name");
    nameTree->addChild(advance());
    stmt->addChild(nameTree);
    
    if (match("😌")) {
        stmt->addChild(parseExpression());
    }
    
    while (match("🗿")) {
        nameTree = std::make_shared<Tree>("name");
        nameTree->addChild(advance());
        stmt->addChild(nameTree);
        
        if (match("😌")) {
            stmt->addChild(parseExpression());
        }
    }
    
    return stmt;
}

TreePtr Parser::parseFlowStatement() {
    auto stmt = std::make_shared<Tree>("flow_stmt");
    auto token = advance();
    
    if (token->value == "⏸") {
        auto breakStmt = std::make_shared<Tree>("break_stmt");
        stmt->addChild(breakStmt);
    } else if (token->value == "⏩") {
        auto continueStmt = std::make_shared<Tree>("continue_stmt");
        stmt->addChild(continueStmt);
    }
    
    return stmt;
}

TreePtr Parser::parsePrintStatement() {
    auto stmt = std::make_shared<Tree>("print_stmt");
    advance(); // consume "🖨"
    advance(); // consume "👉"
    
    stmt->addChild(parseExpression());
    
    advance(); // consume "👈"
    return stmt;
}

TreePtr Parser::parseIfStatement() {
    auto stmt = std::make_shared<Tree>("if_stmt");
    advance(); // consume "🚩"
    advance(); // consume "👉"
    
    stmt->addChild(parseExpression()); // condition
    
    advance(); // consume "👈"
    advance(); // consume "🍽"
    
    stmt->addChild(parseSuite()); // body
    
    advance(); // consume "🥂"
    return stmt;
}

TreePtr Parser::parseWhileStatement() {
    auto stmt = std::make_shared<Tree>("while_stmt");
    advance(); // consume "💿"
    advance(); // consume "👉"
    
    stmt->addChild(parseExpression()); // condition
    
    advance(); // consume "👈"
    advance(); // consume "🍽"
    
    stmt->addChild(parseSuite()); // body
    
    advance(); // consume "🥂"
    return stmt;
}

TreePtr Parser::parseForStatement() {
    auto stmt = std::make_shared<Tree>("for_stmt");
    advance(); // consume "📀"
    advance(); // consume "👉"
    
    stmt->addChild(parseForDecl());   // init
    advance(); // consume "👄"
    stmt->addChild(parseForTest());   // condition
    advance(); // consume "👄"
    stmt->addChild(parseForUpdates()); // update
    
    advance(); // consume "👈"
    advance(); // consume "🍽"
    
    stmt->addChild(parseSuite()); // body
    
    advance(); // consume "🥂"
    return stmt;
}

TreePtr Parser::parseExpression() {
    return parseLogicalOrExpression();
}

// Simplified expression parsing
TreePtr Parser::parseLogicalOrExpression() {
    auto expr = parseLogicalAndExpression();
    
    while (check("😇") || check("||")) {
        auto newExpr = std::make_shared<Tree>("logicalorexpression");
        newExpr->addChild(expr);
        newExpr->addChild(advance());
        newExpr->addChild(parseLogicalAndExpression());
        expr = newExpr;
    }
    
    return expr;
}

TreePtr Parser::parseLogicalAndExpression() {
    auto expr = parseInclusiveOrExpression();
    
    while (check("😠") || check("&&")) {
        auto newExpr = std::make_shared<Tree>("logicalandexpression");
        newExpr->addChild(expr);
        newExpr->addChild(advance());
        newExpr->addChild(parseInclusiveOrExpression());
        expr = newExpr;
    }
    
    return expr;
}

TreePtr Parser::parseInclusiveOrExpression() {
    return parseExclusiveOrExpression();
}

TreePtr Parser::parseExclusiveOrExpression() {
    return parseAndExpression();
}

TreePtr Parser::parseAndExpression() {
    return parseEqualityExpression();
}

TreePtr Parser::parseEqualityExpression() {
    auto expr = parseAdditiveExpression();
    
    while (check("😌😌") || check("❗😌") || check("😭") || check("😁") || check("😭😌") || check("😁😌")) {
        auto newExpr = std::make_shared<Tree>("equalityexpression");
        newExpr->addChild(expr);
        newExpr->addChild(advance());
        newExpr->addChild(parseAdditiveExpression());
        expr = newExpr;
    }
    
    return expr;
}

TreePtr Parser::parseAdditiveExpression() {
    auto expr = parseMultiplicativeExpression();
    
    while (check("➕") || check("➖") || check("+") || check("-")) {
        auto newExpr = std::make_shared<Tree>("additiveexpression");
        newExpr->addChild(expr);
        newExpr->addChild(advance());
        newExpr->addChild(parseMultiplicativeExpression());
        expr = newExpr;
    }
    
    return expr;
}

TreePtr Parser::parseMultiplicativeExpression() {
    auto expr = parseCastExpression();
    
    while (check("✖") || check("➗") || check("📎") || check("*") || check("/") || check("%")) {
        auto newExpr = std::make_shared<Tree>("multiplicativeexpression");
        newExpr->addChild(expr);
        newExpr->addChild(advance());
        newExpr->addChild(parseCastExpression());
        expr = newExpr;
    }
    
    return expr;
}

TreePtr Parser::parseCastExpression() {
    auto expr = std::make_shared<Tree>("castexpression");
    
    if (check("❗") || check("〰") || check("!") || check("~")) {
        expr->addChild(advance());
        expr->addChild(parseArgument());
    } else {
        expr->addChild(parseArgument());
    }
    
    return expr;
}

TreePtr Parser::parseArgument() {
    if (check("✔") || check("❌")) {
        auto boolTree = std::make_shared<Tree>("boolean");
        boolTree->addChild(advance());
        return boolTree;
    }
    
    if (peek()->type == TokenType::NUMBER) {
        auto numTree = std::make_shared<Tree>("number");
        numTree->addChild(advance());
        return numTree;
    }
    
    if (peek()->type == TokenType::NAME) {
        auto nameTree = std::make_shared<Tree>("name");
        nameTree->addChild(advance());
        return nameTree;
    }
    
    if (peek()->type == TokenType::STRING) {
        auto strTree = std::make_shared<Tree>("string");
        strTree->addChild(advance());
        return strTree;
    }
    
    if (match("👉")) {
        auto expr = parseExpression();
        advance(); // consume "👈"
        return expr;
    }
    
    throw std::runtime_error("Unexpected token: " + peek()->value);
}

TreePtr Parser::parseSuite() {
    auto suite = std::make_shared<Tree>("suite");
    
    while (!check("🥂") && !isAtEnd()) {
        auto stmt = parseStatement();
        if (stmt) {
            suite->addChild(stmt);
        }
    }
    
    return suite;
}

TreePtr Parser::parseForDecl() {
    auto decl = std::make_shared<Tree>("for_decl");
    
    if (check("📢")) {
        decl->addChild(parseDeclareStatement());
    } else if (peek()->type == TokenType::NAME && tokens.size() > current + 1 && tokens[current + 1]->value == "😌") {
        decl->addChild(parseAssignmentStatement());
    }
    
    return decl;
}

TreePtr Parser::parseForTest() {
    auto test = std::make_shared<Tree>("for_test");
    
    if (!check("👄")) {
        test->addChild(parseExpression());
    }
    
    return test;
}

TreePtr Parser::parseForUpdates() {
    auto updates = std::make_shared<Tree>("for_updates");
    
    if (peek()->type == TokenType::NAME && tokens.size() > current + 1 && tokens[current + 1]->value == "😌") {
        updates->addChild(parseAssignmentStatement());
    }
    
    return updates;
}
