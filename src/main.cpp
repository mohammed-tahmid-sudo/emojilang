#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include "Parser.hpp"
#include "EmojiTransformer.hpp"
#include "EmojiInterpreter.hpp"

int main(int argc, char* argv[]) {
    try {
        Parser parser;
        
        std::cout << "STATUS: Parser Generated Successfully" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        
        std::vector<std::string> testFileNames;
        bool isTest = true;
        
        if (argc > 1) {
            for (int i = 1; i < argc; i++) {
                testFileNames.push_back(argv[i]);
            }
            isTest = false;
        } else {
            // Load test files from tests directory
            std::filesystem::path testsDir("tests");
            if (std::filesystem::exists(testsDir) && std::filesystem::is_directory(testsDir)) {
                for (const auto& entry : std::filesystem::directory_iterator(testsDir)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".emo") {
                        testFileNames.push_back(entry.path().filename().string());
                    }
                }
            }
        }
        
        for (const std::string& fileName : testFileNames) {
            std::string text;
            std::string fullPath;
            
            try {
                if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".emo") {
                    if (isTest) {
                        fullPath = "tests/" + fileName;
                    } else {
                        fullPath = fileName;
                    }
                    
                    std::ifstream file(fullPath);
                    if (!file.is_open()) {
                        std::cerr << "STATUS: error in reading the file " << fullPath << std::endl;
                        continue;
                    }
                    
                    std::string line;
                    while (std::getline(file, line)) {
                        text += line + "\n";
                    }
                    file.close();
                } else {
                    std::cout << "Please give a valid file to execute... that ends with .emo" << std::endl;
                    continue;
                }
            } catch (const std::exception& e) {
                std::cerr << "STATUS: error in reading the file " << fullPath << std::endl;
                continue;
            }
            
            text += "\n";
            
            try {
                TreePtr tree = parser.parse(text);
                std::cout << "STATUS: " << fileName << " Parsed Successfully" << std::endl;
                
                // Transform emojis to plain text
                EmojiTransformer transformer;
                transformer.visit(tree);
                
                // Execute the program
                EmojiInterpreter interpreter(tree);
                interpreter.start();
                
                std::cout << "STATUS: " << fileName << " ran without any interrupt" << std::endl;
                std::cout << "-----------------------------------------------------------------------------" << std::endl;
                
            } catch (const std::exception& e) {
                std::cerr << "ERROR in " << fileName << ": " << e.what() << std::endl;
                std::cout << "-----------------------------------------------------------------------------" << std::endl;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
