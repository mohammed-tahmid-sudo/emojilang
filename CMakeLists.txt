cmake_minimum_required(VERSION 3.16)
project(emojilang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Add executable
add_executable(emojilang
    src/main.cpp
    src/EmojiInterpreter.cpp
    src/EmojiTransformer.cpp
    src/Parser.cpp
    src/SymbolTable.cpp
    src/Token.cpp
    src/Tree.cpp
)

# Include directories
target_include_directories(emojilang PRIVATE include)

# Set output directory
set_target_properties(emojilang PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Compiler flags
target_compile_options(emojilang PRIVATE -Wall -Wextra -O2)
