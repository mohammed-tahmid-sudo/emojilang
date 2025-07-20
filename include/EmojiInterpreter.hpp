#pragma once
#include <memory>
#include <string>
#include "Tree.hpp"
#include "SymbolTable.hpp"

class EmojiInterpreter {
private:
    SymbolTable symbolTable;
    TreePtr parseTree;
    bool isAssignmentDeclaration;
    
public:
    EmojiInterpreter(TreePtr tree);
    void start();
    
private:
    Value visit(TreePtr tree);
    Value visit(const TreeNode& node);
    void visitChildren(TreePtr tree);
    
    // Statement visitors
    Value visitStatement(TreePtr tree);
    Value visitString(TreePtr tree);
    Value visitName(TreePtr tree);
    Value visitNumber(TreePtr tree);
    Value visitBoolean(TreePtr tree);
    
    // Expression visitors
    Value visitCastExpression(TreePtr tree);
    Value visitAdditiveExpression(TreePtr tree);
    Value visitMultiplicativeExpression(TreePtr tree);
    Value visitEqualityExpression(TreePtr tree);
    Value visitAndExpression(TreePtr tree);
    Value visitExclusiveOrExpression(TreePtr tree);
    Value visitInclusiveOrExpression(TreePtr tree);
    Value visitLogicalAndExpression(TreePtr tree);
    Value visitLogicalOrExpression(TreePtr tree);
    Value visitExp(TreePtr tree);
    
    // Statement execution
    Value visitPrintStatement(TreePtr tree);
    Value visitAssignmentStatement(TreePtr tree);
    Value visitDeclareStatement(TreePtr tree);
    Value visitSuite(TreePtr tree);
    Value visitIfStatement(TreePtr tree);
    Value visitWhileStatement(TreePtr tree);
    Value visitForStatement(TreePtr tree);
    Value visitForDecl(TreePtr tree);
    Value visitForTest(TreePtr tree);
    Value visitForUpdates(TreePtr tree);
    Value visitFlowStatement(TreePtr tree);
    
    // Helper functions
    std::string valueToString(const Value& value);
    double valueToDouble(const Value& value);
    bool valueToBool(const Value& value);
    int valueToInt(const Value& value);
    bool isToken(const TreeNode& node);
    std::string getTokenValue(const TreeNode& node);
};
