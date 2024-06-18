#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return code;
}

void intepret(const std::string &bfCode)
{
    std::vector<char> tape(30000, 0);
    size_t tapePtr = 0;               
    std::stack<size_t> loopStack;    

    for (size_t i = 0; i < bfCode.size(); ++i) {
        switch (bfCode[i]) {
            case '>':
                ++tapePtr;
                if (tapePtr >= tape.size()) {
                    tape.push_back(0); 
                }
                break;
            case '<':
                if (tapePtr > 0) {
                    --tapePtr;
                } else {
                    std::cerr << "Error: Pointer moved to the left of the tape's start!" << std::endl;
                    return;
                }
                break;
            case '+':
                ++tape[tapePtr];
                break;
            case '-':
                --tape[tapePtr];
                break;
            case '.':
                std::cout << tape[tapePtr];
                break;
            case ',':
                tape[tapePtr] = std::cin.get();
                break;
            case '[':
                if (tape[tapePtr] == 0) {
                    int openBrackets = 1;
                    while (openBrackets != 0) {
                        ++i;
                        if (i >= bfCode.size()) {
                            std::cerr << "Error: Mismatched brackets!" << std::endl;
                            return;
                        }
                        if (bfCode[i] == '[') {
                            ++openBrackets;
                        } else if (bfCode[i] == ']') {
                            --openBrackets;
                        }
                    }
                } else {
                    loopStack.push(i);
                }
                break;
            case ']':
                if (loopStack.empty()) {
                    std::cerr << "Error: Mismatched brackets!" << std::endl;
                    return;
                }
                if (tape[tapePtr] != 0) {
                    i = loopStack.top();
                } else {
                    loopStack.pop();
                }
                break;
            default:
                break;
        }
    }

    if (!loopStack.empty()) {
        std::cerr << "Error: Mismatched brackets!" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <brainfuck_file.bf>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    try {
        std::string code = readFile(filename);
        intepret(code);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
