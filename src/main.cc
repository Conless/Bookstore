#include <iostream>

#include "Bookstore.h"
#include "Exception.h"
#include "utils.h"

void JudgeInput(int argc, char *argv[]) {
    // TODO
    return;
}

InputMsg OperateMsg(const std::vector<std::string> input) {
    if (!input.size())
        throw Exception(INVALID_INPUT, "Read an empty input line.");
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() > 1)
            throw Exception(INVALID_INPUT, "Exit or quit message followed with unexpected parameters.");
        return InputMsg(quit, std::vector<std::string>());
    }
    throw Exception(INVALID_INPUT, "Unexpected input message");
}

int main(int argc, char *argv[]) {
    JudgeInput(argc, argv);
    while (true) {
        std::string input;
        getline(std::cin, input);
        try {
            std::vector<std::string> input_div = DivideMsg(input);
            InputMsg msg = OperateMsg(input_div);
        } catch (const Exception &err) {
            // TODO
        }
    }
    return 0;
}