#pragma once
#include <memory>
#include <unordered_map>
#include "Tree.hpp"

class EmojiTransformer {
private:
    std::unordered_map<std::string, std::string> emojiMappings;
    void initializeMappings();
    
public:
    EmojiTransformer();
    void visit(TreePtr tree);
    
private:
    void visitIfStatement(TreePtr tree);
    void visitBoolean(TreePtr tree);
    void visitCastExpression(TreePtr tree);
    void visitMultiplicativeExpression(TreePtr tree);
    void visitAdditiveExpression(TreePtr tree);
    void visitEqualityExpression(TreePtr tree);
    void visitAndExpression(TreePtr tree);
    void visitExclusiveOrExpression(TreePtr tree);
    void visitInclusiveOrExpression(TreePtr tree);
    void visitLogicalAndExpression(TreePtr tree);
    void visitLogicalOrExpression(TreePtr tree);
    
    std::string getMatch(const std::string& emoji);
    void visitChildren(TreePtr tree);
};
