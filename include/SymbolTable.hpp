#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <iostream>

using Value = std::variant<std::monostate, int, double, bool, std::string>;

class SymbolTable {
private:
    std::vector<std::unordered_map<std::string, Value>> table;
    bool isDebug;

public:
    SymbolTable(bool debug = false);
    
    void debugSymbolTable() const;
    void addScope();
    void addSymbol(const std::string& symbol, const Value& value = Value{});
    int doesSymbolExist(const std::string& symbol) const;
    void updateSymbol(const std::string& symbol, const Value& value);
    Value getValue(const std::string& symbol) const;
    void removeScope();
};
