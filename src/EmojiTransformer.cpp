#include "EmojiTransformer.hpp"
#include <iostream>

EmojiTransformer::EmojiTransformer() {
    initializeMappings();
}

void EmojiTransformer::initializeMappings() {
    emojiMappings = {
        {"😭", "<"},
        {"😁", ">"},
        {"😁😌", ">="},
        {"😭😌", "<="},
        {"😌😌", "=="},
        {"❗😌", "!="}
    };
}

void EmojiTransformer::visit(TreePtr tree) {
    if (!tree) return;
    
    if (tree->data == "if_stmt") {
        visitIfStatement(tree);
    } else if (tree->data == "boolean") {
        visitBoolean(tree);
    } else if (tree->data == "castexpression") {
        visitCastExpression(tree);
    } else if (tree->data == "multiplicativeexpression") {
        visitMultiplicativeExpression(tree);
    } else if (tree->data == "additiveexpression") {
        visitAdditiveExpression(tree);
    } else if (tree->data == "equalityexpression") {
        visitEqualityExpression(tree);
    } else if (tree->data == "andexpression") {
        visitAndExpression(tree);
    } else if (tree->data == "exclusiveorexpression") {
        visitExclusiveOrExpression(tree);
    } else if (tree->data == "inclusiveorexpression") {
        visitInclusiveOrExpression(tree);
    } else if (tree->data == "logicalandexpression") {
        visitLogicalAndExpression(tree);
    } else if (tree->data == "logicalorexpression") {
        visitLogicalOrExpression(tree);
    }
    
    visitChildren(tree);
}

void EmojiTransformer::visitChildren(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TreePtr>(child)) {
            visit(std::get<TreePtr>(child));
        }
    }
}

void EmojiTransformer::visitIfStatement(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "🚩") {
                token->value = "if";
            } else if (token->value == "🏳") {
                token->value = "elif";
            } else if (token->value == "🏁") {
                token->value = "else";
            }
        }
    }
}

void EmojiTransformer::visitBoolean(TreePtr tree) {
    if (!tree->children.empty() && std::holds_alternative<TokenPtr>(tree->children[0])) {
        auto token = std::get<TokenPtr>(tree->children[0]);
        if (token->value == "✔") {
            token->value = "true";
        } else if (token->value == "❌") {
            token->value = "false";
        }
    }
}

void EmojiTransformer::visitCastExpression(TreePtr tree) {
    if (tree->children.size() <= 1) return;
    
    if (std::holds_alternative<TokenPtr>(tree->children[0])) {
        auto token = std::get<TokenPtr>(tree->children[0]);
        if (token->value == "❗") {
            token->value = "!";
        } else if (token->value == "〰") {
            token->value = "~";
        }
    }
}

void EmojiTransformer::visitMultiplicativeExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "✖") {
                token->value = "*";
            } else if (token->value == "➗") {
                token->value = "/";
            } else if (token->value == "📎") {
                token->value = "%";
            }
        }
    }
}

void EmojiTransformer::visitAdditiveExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "➕") {
                token->value = "+";
            } else if (token->value == "➖") {
                token->value = "-";
            }
        }
    }
}

void EmojiTransformer::visitEqualityExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (emojiMappings.find(token->value) != emojiMappings.end()) {
                token->value = emojiMappings[token->value];
            }
        }
    }
}

void EmojiTransformer::visitAndExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "⚛") {
                token->value = "&";
            }
        }
    }
}

void EmojiTransformer::visitExclusiveOrExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "⚓") {
                token->value = "xor";
            }
        }
    }
}

void EmojiTransformer::visitInclusiveOrExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "☯") {
                token->value = "|";
            }
        }
    }
}

void EmojiTransformer::visitLogicalAndExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "😠") {
                token->value = "and";
            }
        }
    }
}

void EmojiTransformer::visitLogicalOrExpression(TreePtr tree) {
    for (auto& child : tree->children) {
        if (std::holds_alternative<TokenPtr>(child)) {
            auto token = std::get<TokenPtr>(child);
            if (token->value == "😇") {
                token->value = "or";
            }
        }
    }
}

std::string EmojiTransformer::getMatch(const std::string& emoji) {
    if (emojiMappings.find(emoji) != emojiMappings.end()) {
        return emojiMappings[emoji];
    }
    return emoji;
}
