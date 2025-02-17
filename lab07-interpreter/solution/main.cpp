#include "matrix.hpp"
#include <iostream>
#include <unordered_map>
#include <sstream>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

namespace matrix_interpreter {
class Inerpreter {
public:
    void run();

private:
    std::unordered_map<std::string, Matrix> registers;

    void executeCommand(const std::string& command);
    static bool isRegister(const std::string& token);
};

void Inerpreter::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            executeCommand(line);
        } catch (const MatrixExcepion& e) {
            std::cout << e.what() << "\n";
        } catch (const std::bad_alloc&) {
            std::cerr << "Unable to allocate memory\n";
        }
    }    
}
void Inerpreter::executeCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    if (cmd == "exit") {
        std::exit(0);
    } else if (cmd == "load") {
        std::string reg, filename;
        iss >> reg >> filename;
        if (!isRegister(reg)) {
            throw MatrixExcepion("`" + reg + "`is not a register");
        }
        registers[reg].loadFromFile(filename);
    } else if (cmd == "print") {
        std::string reg;
        iss >> reg;
        if (!isRegister(reg)) {
            throw MatrixExcepion("`" + reg + "` is not a register");
        }
        registers[reg].print();
    } else if (cmd == "elem") {
        std::string reg;
        int row, col;
        iss >> reg >> row >> col;
        if (!isRegister(reg)) {
            throw MatrixExcepion("`" + reg + "` is not a register");
        }
        std::cout << registers[reg].getElement(row, col) << "\n";
    } else if (cmd == "add") {
        std::string reg1, reg2;
        iss >> reg1 >> reg2;
        if (!isRegister(reg1) || !isRegister(reg2)) {
            throw MatrixExcepion("`" + reg1 + reg2 + "` is not a register");
        }
        registers[reg1]= registers[reg1] + registers[reg2];
    } else if (cmd == "mul") {
        std::string reg1, reg2;
        iss >> reg1 >> reg2;
        if (!isRegister(reg1) || !isRegister(reg2)) {
            throw MatrixExcepion("`" + reg1 + reg2 + "` is not a register");
        }
        registers[reg1]= registers[reg1] * registers[reg2];
    } else {
        throw MatrixExcepion("Unknown command: `" + cmd + "`");
    }
}

bool Inerpreter::isRegister(const std::string& token) {
    return token.size() == 2 && token[0] == '$' && token[1] >= '0' && token[1] <= 9;
}

    
}  // namespace matrix_interpreter

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    matrix_interpreter::Inerpreter interpreter;
    interpreter.run();
}
