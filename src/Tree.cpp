#include "Tree.hpp"
#include <sstream>

Tree::Tree(const std::string& data_name) : data(data_name) {}

Tree::Tree(const std::string& data_name, std::vector<TreeNode> child_nodes) 
    : data(data_name), children(std::move(child_nodes)) {}

void Tree::addChild(TreeNode child) {
    children.push_back(child);
}

void Tree::addChild(const std::string& token_value) {
    auto token = std::make_shared<Token>(TokenType::STRING, token_value);
    children.push_back(token);
}

void Tree::addChild(TokenPtr token) {
    children.push_back(token);
}

void Tree::addChild(TreePtr tree) {
    children.push_back(tree);
}

std::string Tree::pretty(int indent) const {
    std::stringstream ss;
    std::string indentStr(indent * 2, ' ');
    ss << indentStr << data << "\n";
    
    for (const auto& child : children) {
        ss << prettyNode(child, indent + 1);
    }
    
    return ss.str();
}

std::string Tree::prettyNode(const TreeNode& node, int indent) const {
    std::string indentStr(indent * 2, ' ');
    
    if (std::holds_alternative<TreePtr>(node)) {
        return std::get<TreePtr>(node)->pretty(indent);
    } else if (std::holds_alternative<TokenPtr>(node)) {
        return indentStr + std::get<TokenPtr>(node)->value + "\n";
    }
    
    return "";
}

size_t Tree::size() const {
    return children.size();
}

TreeNode& Tree::operator[](size_t index) {
    return children[index];
}

const TreeNode& Tree::operator[](size_t index) const {
    return children[index];
}
