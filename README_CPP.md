# emojilang (C++ Version)
Programming language where you can code using emojis 😌

## Overview
This is a complete C++ port of the original Python-based emojilang interpreter. It includes all the core functionality: parsing, emoji transformation, and execution of emoji-based programs.

## Features
- **Complete C++ Implementation**: No Python dependencies
- **Emoji-to-Text Transformation**: Converts emoji operators to standard operators
- **Full Language Support**: Variables, loops, conditionals, expressions, and more
- **Symbol Table Management**: Proper scoping for variables
- **Abstract Syntax Tree**: Tree-based program representation

## Building

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.16 or later

### Compilation

#### Option 1: Using CMake (Recommended)
```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
make

# Run the executable
./bin/emojilang
```

#### Option 2: Using Simple Makefile
```bash
# Build using simple Makefile
make

# Run the executable
./build/emojilang

# Clean build files
make clean

# Run tests
make test
```

## Usage

### Running test files
```bash
./bin/emojilang                    # Runs all .emo files in tests/ directory
./bin/emojilang tests/factorial.emo   # Run specific file
./bin/emojilang your_program.emo   # Run your own emoji program
```

### Syntax

| emoji | Semantic |
|-------|----------|
| `✖`, `➕`, `➖`, `➗`, `📎` | `*`, `+`, `-`, `/` ,`%` |
| `💿`, `📀` |`while`, `for` |
| `🚩`, `🏁`, `🏳` | `if`, `else`, `elif` |
| `⏸`, `⏩` | `break`, `continue` |
| `😌`, `😌😌`, `😁`, `😭`, `😁😌`, `😭😌`, `❗😌`| `=`, `==`, `>`, `<`, `>=`, `<=`, `!=` |
| `⚛`, `☯`, `⚓`, `〰`| (bitwise) `&`, `\|`, `^`, `~` |
| `😠`, `😇`, `❗` | (logical) `and`, `or`, `not` |
| `💩` (comments starts with '💩')| `//`, `#` (comments) |
| `📢` | declare variable |
| `🖨` | `print()` (print to console) |
| `👉`, `👈` | `(`, `)` |
| `🍽`, `🥂` | `{`, `}` |
| `🗿` | `,` |
| `👄` | `;` |
| `✔`, `❌` | `true`, `false` |

## Architecture

The C++ implementation consists of several key components:

### Core Classes
- **Token**: Represents lexical tokens with type and value
- **Tree**: Abstract Syntax Tree node implementation
- **Parser**: Tokenizes and parses emoji language syntax
- **EmojiTransformer**: Converts emoji symbols to plain text equivalents
- **EmojiInterpreter**: Executes the parsed and transformed program
- **SymbolTable**: Manages variable scoping and storage

### Files Structure
```
include/
├── Token.hpp              # Token representation
├── Tree.hpp               # AST node structure
├── Parser.hpp             # Parser and tokenizer
├── EmojiTransformer.hpp   # Emoji-to-text conversion
├── EmojiInterpreter.hpp   # Program execution engine
└── SymbolTable.hpp        # Variable scope management

src/
├── main.cpp               # Main application entry point
├── Token.cpp              # Token implementation
├── Tree.cpp               # AST implementation
├── Parser.cpp             # Parser implementation
├── EmojiTransformer.cpp   # Transformer implementation
├── EmojiInterpreter.cpp   # Interpreter implementation
└── SymbolTable.cpp        # Symbol table implementation
```

## Sample Programs

### Hello World
```
🖨👉"Hello World From The EMOJILANG 🤗"👈
```

### Factorial Calculation
```
📢 ans 😌 1
📀👉📢 i 😌 1👄 i 😭😌 10👄 i 😌 i ➕ 1👈🍽
    ans 😌 ans ✖ i
🥂
🖨👉ans👈
```

### Fibonacci Series
```
📢 f0 😌 0 🗿 f1 😌 1
📢 i 😌 0
💿👉i 😭 10👈🍽
    🖨👉f0👈
    📢 tmp 😌 f0
    f0 😌 f1
    f1 😌 f1 ➕ tmp
    i 😌 i ➕ 1
🥂
```

## Differences from Python Version

1. **No External Dependencies**: The C++ version doesn't require the Lark parsing library
2. **Static Typing**: Uses C++ type system with std::variant for dynamic values
3. **Memory Management**: Uses smart pointers for automatic memory management
4. **Performance**: Generally faster execution compared to the Python interpreter
5. **Compilation**: Requires compilation step but produces standalone executable

## Contributing

Feel free to contribute to this C++ port of emojilang! Areas for improvement:
- Enhanced error reporting and debugging
- Additional emoji operators
- Performance optimizations
- More comprehensive test coverage
- IDE/editor support for .emo files

## License

Same as the original Python version.

**_NOTE:_** This C++ version maintains full compatibility with the original emoji language syntax while providing a standalone, dependency-free implementation.
