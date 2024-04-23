#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//Plain Commands
/*

rem = comments

The get, print, goto, and end statements correspond directly to the IML read, write,
branch, and halt instructions, respectively.
    o get only gets a single numeric variable
    o print can print either a single numeric variable or a numeric literal constant
    o Every line of code begins with a line number. Line numbers are strictly
        increasing in the program, but numbers may be skipped. goto transfers control to
        another line

if condition goto lineNumber = Evaluate a condition and transfer control to another line
if the condition is true. The condition compares a variable to another variable or a
numeric constant. Comparisons use = or >.

let = the assignment statement. Assigns a value to a variable. The value may a single
literal constant, a variable, or an arithmetic expression involving two values (each of
which may be literal constants or variables).
*/

enum class TokenType {
    LINE_NUMBER,
    COMMAND,
    VARIABLE,
    NUMERIC_CONSTANT,
    OPERATOR,
    COMMENT
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
public:
    Tokenizer(const std::string& filename) : inputFilename(filename) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::ifstream file(inputFilename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << inputFilename << std::endl;
            return tokens;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                Token token = classifyToken(word);
                if (token.type != TokenType::COMMENT) {
                    tokens.push_back(token);
                }
            }
        }
        file.close();
        return tokens;
    }

private:
    std::string inputFilename;

    Token classifyToken(const std::string& word) {
        Token token;
        if (isLineNumber(word)) {
            token.type = TokenType::LINE_NUMBER;
        } else if (isCommand(word)) {
            token.type = TokenType::COMMAND;
        } else if (isVariable(word)) {
            token.type = TokenType::VARIABLE;
        } else if (isNumericConstant(word)) {
            token.type = TokenType::NUMERIC_CONSTANT;
        } else if (isOperator(word)) {
            token.type = TokenType::OPERATOR;
        } else if (isComment(word)) {
            token.type = TokenType::COMMENT;
        } else {
            std::cerr << "Unrecognized token: " << word << std::endl;
            token.type = TokenType::COMMENT;
        }
        token.value = word;
        return token;
    }

    bool isLineNumber(const std::string& word) {
        return std::all_of(word.begin(), word.end(), ::isdigit);
    }

    bool isCommand(const std::string& word) {
        return (word == "rem" || word == "get" || word == "print" || word == "goto" || word == "if" ||
                word == "let" || word == "end");
    }

    bool isVariable(const std::string& word) {
        return (word.size() == 1 && std::isalpha(word[0]));
    }

    bool isNumericConstant(const std::string& word) {
        return std::all_of(word.begin(), word.end(), ::isdigit);
    }

    bool isOperator(const std::string& word) {
        return (word == "=" || word == ">");
    }

    bool isComment(const std::string& word) {
        return (word == "rem");
    }
};

int main() {
    std::string filename;
    std::cout << "Enter the name of the file to tokenize";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cerr << "No file name." << std::endl;
        return 1;
    }

    Tokenizer tokenizer(filename);
    std::vector<Token> tokens = tokenizer.tokenize();

    std::cout << "Tokens:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Type: ";
        switch (token.type) {
            case TokenType::LINE_NUMBER:
                std::cout << "LINE_NUMBER";
                break;
            case TokenType::COMMAND:
                std::cout << "COMMAND";
                break;
            case TokenType::VARIABLE:
                std::cout << "VARIABLE";
                break;
            case TokenType::NUMERIC_CONSTANT:
                std::cout << "NUMERIC_CONSTANT";
                break;
            case TokenType::OPERATOR:
                std::cout << "OPERATOR";
                break;
            case TokenType::COMMENT:
                std::cout << "COMMENT";
                break;
        }
        std::cout << " Value " << token.value << std::endl;
    }

    return 0;
}