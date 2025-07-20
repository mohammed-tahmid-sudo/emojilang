#include "EmojiInterpreter.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>

EmojiInterpreter::EmojiInterpreter(TreePtr tree) 
    : symbolTable(false), parseTree(tree), isAssignmentDeclaration(false) {}

void EmojiInterpreter::start() {
    symbolTable.addScope();
    visit(parseTree);
}

Value EmojiInterpreter::visit(TreePtr tree) {
    if (!tree) return Value{};
    
    if (tree->data == "stmt") return visitStatement(tree);
    if (tree->data == "string") return visitString(tree);
    if (tree->data == "name") return visitName(tree);
    if (tree->data == "number") return visitNumber(tree);
    if (tree->data == "boolean") return visitBoolean(tree);
    if (tree->data == "castexpression") return visitCastExpression(tree);
    if (tree->data == "additiveexpression") return visitAdditiveExpression(tree);
    if (tree->data == "multiplicativeexpression") return visitMultiplicativeExpression(tree);
    if (tree->data == "equalityexpression") return visitEqualityExpression(tree);
    if (tree->data == "andexpression") return visitAndExpression(tree);
    if (tree->data == "exclusiveorexpression") return visitExclusiveOrExpression(tree);
    if (tree->data == "inclusiveorexpression") return visitInclusiveOrExpression(tree);
    if (tree->data == "logicalandexpression") return visitLogicalAndExpression(tree);
    if (tree->data == "logicalorexpression") return visitLogicalOrExpression(tree);
    if (tree->data == "exp") return visitExp(tree);
    if (tree->data == "print_stmt") return visitPrintStatement(tree);
    if (tree->data == "assignment_stmt") return visitAssignmentStatement(tree);
    if (tree->data == "declare_stmt") return visitDeclareStatement(tree);
    if (tree->data == "suite") return visitSuite(tree);
    if (tree->data == "if_stmt") return visitIfStatement(tree);
    if (tree->data == "while_stmt") return visitWhileStatement(tree);
    if (tree->data == "for_stmt") return visitForStatement(tree);
    if (tree->data == "for_decl") return visitForDecl(tree);
    if (tree->data == "for_test") return visitForTest(tree);
    if (tree->data == "for_updates") return visitForUpdates(tree);
    if (tree->data == "flow_stmt") return visitFlowStatement(tree);
    
    // Default: visit children
    visitChildren(tree);
    return Value{};
}

Value EmojiInterpreter::visit(const TreeNode& node) {
    if (std::holds_alternative<TreePtr>(node)) {
        return visit(std::get<TreePtr>(node));
    } else if (std::holds_alternative<TokenPtr>(node)) {
        return std::get<TokenPtr>(node)->value;
    }
    return Value{};
}

void EmojiInterpreter::visitChildren(TreePtr tree) {
    for (const auto& child : tree->children) {
        visit(child);
    }
}

Value EmojiInterpreter::visitStatement(TreePtr tree) {
    Value result;
    for (const auto& child : tree->children) {
        result = visit(child);
    }
    return result;
}

Value EmojiInterpreter::visitString(TreePtr tree) {
    if (!tree->children.empty() && isToken(tree->children[0])) {
        return getTokenValue(tree->children[0]);
    }
    return std::string{};
}

Value EmojiInterpreter::visitName(TreePtr tree) {
    if (!tree->children.empty() && isToken(tree->children[0])) {
        std::string name = getTokenValue(tree->children[0]);
        return symbolTable.getValue(name);
    }
    return Value{};
}

Value EmojiInterpreter::visitNumber(TreePtr tree) {
    if (!tree->children.empty() && isToken(tree->children[0])) {
        std::string numStr = getTokenValue(tree->children[0]);
        try {
            if (numStr.find('.') != std::string::npos) {
                return std::stod(numStr);
            } else {
                return std::stoi(numStr);
            }
        } catch (const std::exception&) {
            return 0;
        }
    }
    return 0;
}

Value EmojiInterpreter::visitBoolean(TreePtr tree) {
    if (!tree->children.empty() && isToken(tree->children[0])) {
        std::string boolStr = getTokenValue(tree->children[0]);
        return boolStr == "true" || boolStr == "✔";
    }
    return false;
}

Value EmojiInterpreter::visitCastExpression(TreePtr tree) {
    if (tree->children.size() == 1) {
        return visit(tree->children[0]);
    } else if (tree->children.size() == 2) {
        std::string op = getTokenValue(tree->children[0]);
        Value operand = visit(tree->children[1]);
        
        if (op == "!" || op == "not" || op == "❗") {
            return !valueToBool(operand);
        } else if (op == "~" || op == "〰") {
            return ~valueToInt(operand);
        }
    }
    return Value{};
}

Value EmojiInterpreter::visitAdditiveExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "+" || op == "➕") {
            if (std::holds_alternative<int>(value) && std::holds_alternative<int>(right)) {
                value = std::get<int>(value) + std::get<int>(right);
            } else {
                value = valueToDouble(value) + valueToDouble(right);
            }
        } else if (op == "-" || op == "➖") {
            if (std::holds_alternative<int>(value) && std::holds_alternative<int>(right)) {
                value = std::get<int>(value) - std::get<int>(right);
            } else {
                value = valueToDouble(value) - valueToDouble(right);
            }
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitMultiplicativeExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "*" || op == "✖") {
            if (std::holds_alternative<int>(value) && std::holds_alternative<int>(right)) {
                value = std::get<int>(value) * std::get<int>(right);
            } else {
                value = valueToDouble(value) * valueToDouble(right);
            }
        } else if (op == "/" || op == "➗") {
            value = valueToDouble(value) / valueToDouble(right);
        } else if (op == "%" || op == "mod" || op == "📎") {
            value = valueToInt(value) % valueToInt(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitEqualityExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    std::stringstream ss;
    ss << valueToString(visit(tree->children[0])) << " ";
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        ss << op << " ";
        ss << valueToString(visit(tree->children[i + 1])) << " ";
    }
    
    std::string expr = ss.str();
    // Simple evaluation - in a real implementation, you'd want proper expression evaluation
    // For now, we'll handle basic cases
    if (expr.find("==") != std::string::npos) {
        Value left = visit(tree->children[0]);
        Value right = visit(tree->children[2]);
        return valueToString(left) == valueToString(right);
    }
    
    return false;
}

Value EmojiInterpreter::visitAndExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "&" || op == "⚛") {
            value = valueToInt(value) & valueToInt(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitExclusiveOrExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "^" || op == "xor" || op == "⚓") {
            value = valueToInt(value) ^ valueToInt(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitInclusiveOrExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "|" || op == "☯") {
            value = valueToInt(value) | valueToInt(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitLogicalAndExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "&&" || op == "and" || op == "😠") {
            value = valueToBool(value) && valueToBool(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitLogicalOrExpression(TreePtr tree) {
    if (tree->children.empty()) return Value{};
    
    Value value = visit(tree->children[0]);
    
    for (size_t i = 1; i < tree->children.size(); i += 2) {
        if (i + 1 >= tree->children.size()) break;
        
        std::string op = getTokenValue(tree->children[i]);
        Value right = visit(tree->children[i + 1]);
        
        if (op == "||" || op == "or" || op == "😇") {
            value = valueToBool(value) || valueToBool(right);
        }
    }
    
    return value;
}

Value EmojiInterpreter::visitExp(TreePtr tree) {
    if (!tree->children.empty()) {
        return visit(tree->children[0]);
    }
    return Value{};
}

Value EmojiInterpreter::visitPrintStatement(TreePtr tree) {
    if (!tree->children.empty()) {
        Value value = visit(tree->children[0]);
        std::cout << valueToString(value) << std::endl;
    }
    return Value{};
}

Value EmojiInterpreter::visitAssignmentStatement(TreePtr tree) {
    if (tree->children.size() >= 2) {
        std::string symbol;
        
        // Get symbol name from name tree
        if (std::holds_alternative<TreePtr>(tree->children[0])) {
            auto nameTree = std::get<TreePtr>(tree->children[0]);
            if (!nameTree->children.empty() && isToken(nameTree->children[0])) {
                symbol = getTokenValue(nameTree->children[0]);
            }
        }
        
        Value value = visit(tree->children[1]);
        
        if (isAssignmentDeclaration) {
            symbolTable.addSymbol(symbol, value);
        } else {
            symbolTable.updateSymbol(symbol, value);
        }
        
        symbolTable.debugSymbolTable();
    }
    return Value{};
}

Value EmojiInterpreter::visitDeclareStatement(TreePtr tree) {
    isAssignmentDeclaration = true;
    
    for (const auto& child : tree->children) {
        if (std::holds_alternative<TreePtr>(child)) {
            auto childTree = std::get<TreePtr>(child);
            if (childTree->data == "name") {
                if (!childTree->children.empty() && isToken(childTree->children[0])) {
                    std::string symbol = getTokenValue(childTree->children[0]);
                    symbolTable.addSymbol(symbol);
                }
            } else if (childTree->data == "assignment_stmt") {
                visit(child);
            }
        }
    }
    
    isAssignmentDeclaration = false;
    symbolTable.debugSymbolTable();
    return Value{};
}

Value EmojiInterpreter::visitSuite(TreePtr tree) {
    for (size_t i = 0; i < tree->children.size(); ++i) {
        if (std::holds_alternative<TreePtr>(tree->children[i])) {
            Value ret = visit(tree->children[i]);
            if (std::holds_alternative<std::string>(ret)) {
                std::string retStr = std::get<std::string>(ret);
                if (retStr == "break" || retStr == "continue") {
                    return ret;
                }
            }
        }
    }
    return Value{};
}

Value EmojiInterpreter::visitIfStatement(TreePtr tree) {
    for (size_t i = 0; i < tree->children.size(); ++i) {
        if (std::holds_alternative<TokenPtr>(tree->children[i])) {
            std::string token = getTokenValue(tree->children[i]);
            if (token == "if" || token == "elif" || token == "🚩" || token == "🏳") {
                if (i + 2 < tree->children.size()) {
                    Value cond = visit(tree->children[i + 1]);
                    if (valueToBool(cond)) {
                        symbolTable.addScope();
                        Value ret = visit(tree->children[i + 2]);
                        symbolTable.removeScope();
                        return ret;
                    }
                }
            } else if (token == "else" || token == "🏁") {
                if (i + 1 < tree->children.size()) {
                    symbolTable.addScope();
                    Value ret = visit(tree->children[i + 1]);
                    symbolTable.removeScope();
                    return ret;
                }
            }
        }
    }
    return Value{};
}

Value EmojiInterpreter::visitWhileStatement(TreePtr tree) {
    if (tree->children.size() >= 2) {
        while (true) {
            Value cond = visit(tree->children[0]);
            if (!valueToBool(cond)) break;
            
            symbolTable.addScope();
            Value ret = visit(tree->children[1]);
            symbolTable.removeScope();
            
            if (std::holds_alternative<std::string>(ret) && std::get<std::string>(ret) == "break") {
                break;
            }
        }
    }
    return Value{};
}

Value EmojiInterpreter::visitForStatement(TreePtr tree) {
    if (tree->children.size() >= 4) {
        symbolTable.addScope(); // outer scope
        
        visit(tree->children[0]); // for_decl
        
        while (true) {
            Value cond = visit(tree->children[1]); // for_test
            if (!valueToBool(cond)) break;
            
            symbolTable.addScope(); // inner scope
            Value ret = visit(tree->children[3]); // loop body
            symbolTable.removeScope();
            
            if (std::holds_alternative<std::string>(ret) && std::get<std::string>(ret) == "break") {
                break;
            }
            
            visit(tree->children[2]); // for_updates
        }
        
        symbolTable.removeScope();
    }
    return Value{};
}

Value EmojiInterpreter::visitForDecl(TreePtr tree) {
    visitChildren(tree);
    return Value{};
}

Value EmojiInterpreter::visitForTest(TreePtr tree) {
    if (tree->children.empty()) {
        return true; // infinite loop condition
    }
    return visit(tree->children[0]);
}

Value EmojiInterpreter::visitForUpdates(TreePtr tree) {
    visitChildren(tree);
    return Value{};
}

Value EmojiInterpreter::visitFlowStatement(TreePtr tree) {
    for (const auto& child : tree->children) {
        if (std::holds_alternative<TreePtr>(child)) {
            auto childTree = std::get<TreePtr>(child);
            if (childTree->data == "break_stmt") {
                return std::string("break");
            } else if (childTree->data == "continue_stmt") {
                return std::string("continue");
            }
        }
    }
    return Value{};
}

// Helper functions
std::string EmojiInterpreter::valueToString(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) {
        return "0";
    } else if (std::holds_alternative<int>(value)) {
        return std::to_string(std::get<int>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    return "";
}

double EmojiInterpreter::valueToDouble(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) {
        return 0.0;
    } else if (std::holds_alternative<int>(value)) {
        return static_cast<double>(std::get<int>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(value)) {
        try {
            return std::stod(std::get<std::string>(value));
        } catch (const std::exception&) {
            return 0.0;
        }
    }
    return 0.0;
}

bool EmojiInterpreter::valueToBool(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) {
        return false;
    } else if (std::holds_alternative<int>(value)) {
        return std::get<int>(value) != 0;
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value) != 0.0;
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
    } else if (std::holds_alternative<std::string>(value)) {
        std::string str = std::get<std::string>(value);
        return !str.empty() && str != "false" && str != "0";
    }
    return false;
}

int EmojiInterpreter::valueToInt(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) {
        return 0;
    } else if (std::holds_alternative<int>(value)) {
        return std::get<int>(value);
    } else if (std::holds_alternative<double>(value)) {
        return static_cast<int>(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1 : 0;
    } else if (std::holds_alternative<std::string>(value)) {
        try {
            return std::stoi(std::get<std::string>(value));
        } catch (const std::exception&) {
            return 0;
        }
    }
    return 0;
}

bool EmojiInterpreter::isToken(const TreeNode& node) {
    return std::holds_alternative<TokenPtr>(node);
}

std::string EmojiInterpreter::getTokenValue(const TreeNode& node) {
    if (std::holds_alternative<TokenPtr>(node)) {
        return std::get<TokenPtr>(node)->value;
    }
    return "";
}
