#include <iostream>

#include "Bookstore.h"
#include "Bookstore/Exception.h"

void JudgeInput(int argc, char *argv[]) {
    // TODO
    return;
}

namespace bookstore {

namespace input {

Parameter DivideMsg(const std::string &str_in_line, char divide_opt = ' ') {
    Parameter ret_str;
    int siz = str_in_line.size();
    int las = 0;
    for (int i = 0; i < siz; i++)
        if (str_in_line[i] == divide_opt) {
            ret_str.push_back(str_in_line.substr(las, i - las));
            las = i + 1;
        } else if (i == siz - 1) {
            ret_str.push_back(str_in_line.substr(las, i - las + 1));
        }
    return ret_str;
}

InputMsg OperateMsg(const Parameter &input) {
    if (!input.size())
        throw Exception(INVALID_INPUT, "Read an empty input line.");
    Parameter input_str;
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() != 1)
            throw Exception(INVALID_INPUT, "Exit or quit message followed with unexpected parameters.");
        return InputMsg(QUIT, QUIT_DEF, input_str);
    }
    if (input[0] == "su") {
        if (input.size() == 2) {
            input_str.push_back(input[1]);
            return InputMsg(SU, SU_NO_PASSWD, input_str);
        }
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            return InputMsg(SU, SU_PASSWD, input_str);
        }
        throw Exception(INVALID_INPUT, "Su message followed with unexpected parameters.");
    }
    if (input[0] == "logout") {
        if (input.size() != 1)
            throw Exception(INVALID_INPUT, "Logout message followed with unexpected parameters.");
        return InputMsg(LOGOUT, LOGOUT_DEF, std::vector<std::string>());
    }
    if (input[0] == "register") {
        if (input.size() != 4)
            throw Exception(INVALID_INPUT, "Register message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        return InputMsg(REG, REG_DEF, input_str);
    }
    if (input[0] == "passwd") {
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            return InputMsg(PASSWD, PASSWD_NO_CUR, input_str);
        }
        if (input.size() == 4) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            input_str.push_back(input[3]);
            return InputMsg(PASSWD, PASSWD_CUR, input_str);
        }
        throw Exception(INVALID_INPUT, "Passwd message followed with unexpected parameters.");
    }
    if (input[0] == "useradd") {
        if (input.size() != 5)
            throw Exception(INVALID_INPUT, "Useradd message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        input_str.push_back(input[4]);
        return InputMsg(USERADD, USERADD_DEF, input_str);
    }
    if (input[0] == "delete") {
        if (input.size() != 2)
            throw Exception(INVALID_INPUT, "Delete message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        return InputMsg(DEL, DEL_DEF, input_str);
    }
    if (input[0] == "show") {
        if (input.size() != 1 && input.size() != 3)
            throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
        if (input.size() == 1)
            return InputMsg(SHOW, SHOW_DEF, input_str);
        Parameter input_div = DivideMsg(input[1], '=');
        if (input_div.size() != 2)
            throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
        input_str.push_back(input_div[1]);
        if (input_div[0] == "-ISBN")
            return InputMsg(SHOW, SHOW_ISBN, input_str);
        input_str[0] = input_div[1].substr(1, input_div[1].size() - 2);
        if (input_div[0] == "-name")
            return InputMsg(SHOW, SHOW_NAME, input_str);
        if (input_div[0] == "-author")
            return InputMsg(SHOW, SHOW_AUTHOR, input_str);
        if (input_div[0] == "-keyword")
            return InputMsg(SHOW, SHOW_KEYWORD, input_str);
        throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
    }
    if (input[0] == "buy") {
        if (input.size() != 3)
            throw Exception(INVALID_INPUT, "Buy message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        return InputMsg(BUY, BUY_DEF, input_str);
    }
    if (input[0] == "select") {
        if (input.size() != 2)
            throw Exception(INVALID_INPUT, "Select message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        return InputMsg(SEL, SEL_DEF, input_str);
    }
    if (input[0] == "modify") {
        if (input.size() < 2)
            throw Exception(INVALID_INPUT, "Modify message followed with unexpected parameters.");
        int siz = input.size();
        for (int i = 1; i < siz; i++) {
            Parameter input_div = DivideMsg(input[i], '=');
            if (input_div.size() != 2)
                throw Exception(INVALID_INPUT, "Modify message followed with unexpected parameters.");
            input_str.push_back(input_div[0]);
            if (input_div[0] == "-ISBN")
                input_str.push_back(input_div[1]);
            else if (input_div[0] == "-name" || input_div[0] == "-author" || input_div[0] == "-keyword")
                input_str.push_back(input_div[1].substr(1, input_div[1].size() - 2));
            else
                throw Exception(INVALID_INPUT, "Modify message followed with unexpected parameters.");
        }
    }
    if (input[0] == "import") {
        if (input.size() != 3)
            throw Exception(INVALID_INPUT, "Import message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        return InputMsg(IMPORT, IMPORT_DEF, input_str);
    }
    throw Exception(INVALID_INPUT, "Unexpected input message");
}

} // namespace input

} // namespace bookstore

using bookstore::Bookstore;

int main(int argc, char *argv[]) {
    JudgeInput(argc, argv);
    Bookstore master;
    while (true) {
        std::string input;
        getline(std::cin, input);
        try {
            std::vector<std::string> input_div = bookstore::input::DivideMsg(input);
            bookstore::input::InputMsg msg = bookstore::input::OperateMsg(input_div);
            master.AcceptMsg(msg);
        } catch (const Exception &err) {
            // TODO
            std::cout << err.msg << std::endl;
        }
    }
    return 0;
}