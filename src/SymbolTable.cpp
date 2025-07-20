#include "SymbolTable.hpp"
#include <stdexcept>

SymbolTable::SymbolTable(bool debug) : isDebug(debug) {}

void SymbolTable::debugSymbolTable() const {
    if (!isDebug) return;
    
    std::cout << "Symbol Table Debug:\n";
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "Scope " << i << ": ";
        for (const auto& pair : table[i]) {
            std::cout << pair.first << " ";
        }
        std::cout << "\n";
    }
}

void SymbolTable::addScope() {
    table.emplace_back();
}

void SymbolTable::addSymbol(const std::string& symbol, const Value& value) {
    if (table.empty()) {
        throw std::runtime_error("No scope available to add symbol");
    }
    
    if (table.back().find(symbol) != table.back().end()) {
        throw std::runtime_error("Redeclaration in same scope of '" + symbol + "'");
    }
    
    // Initialize with default value if none provided
    if (std::holds_alternative<std::monostate>(value)) {
        table.back()[symbol] = Value(0);
    } else {
        table.back()[symbol] = value;
    }
}

int SymbolTable::doesSymbolExist(const std::string& symbol) const {
    for (int i = static_cast<int>(table.size()) - 1; i >= 0; --i) {
        if (table[i].find(symbol) != table[i].end()) {
            return i;
        }
    }
    return -1;
}

void SymbolTable::updateSymbol(const std::string& symbol, const Value& value) {
    int tableId = doesSymbolExist(symbol);
    if (tableId == -1) {
        throw std::runtime_error("Assignment of undeclared variable '" + symbol + "'");
    }
    table[tableId][symbol] = value;
}

Value SymbolTable::getValue(const std::string& symbol) const {
    int tableId = doesSymbolExist(symbol);
    if (tableId == -1) {
        throw std::runtime_error("'" + symbol + "' is undeclared");
    }
    return table[tableId].at(symbol);
}

void SymbolTable::removeScope() {
    if (table.empty()) {
        throw std::runtime_error("Internal exception: No scope to remove");
    }
    table.pop_back();
}
