#pragma once
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include "Token.hpp"

class Tree;
using TreePtr = std::shared_ptr<Tree>;
using TreeNode = std::variant<TreePtr, TokenPtr>;

class Tree {
public:
    std::string data;
    std::vector<TreeNode> children;
    
    Tree(const std::string& data_name);
    Tree(const std::string& data_name, std::vector<TreeNode> child_nodes);
    
    void addChild(TreeNode child);
    void addChild(const std::string& token_value);
    void addChild(TokenPtr token);
    void addChild(TreePtr tree);
    
    std::string pretty(int indent = 0) const;
    size_t size() const;
    TreeNode& operator[](size_t index);
    const TreeNode& operator[](size_t index) const;
    
private:
    std::string prettyNode(const TreeNode& node, int indent) const;
};
