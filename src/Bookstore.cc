#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"

namespace bookstore {

namespace input {

BookstoreLexer::BookstoreLexer(const std::string &str_in_line, char divide_opt) {
    int siz = str_in_line.size();
    int las = 0;
    for (int i = 0; i < siz; i++)
        if (str_in_line[i] == divide_opt) {
            push_back(str_in_line.substr(las, i - las));
            las = i + 1;
        } else if (i == siz - 1) {
            push_back(str_in_line.substr(las, i - las + 1));
        }
}

BookstoreParser::BookstoreParser(const BookstoreLexer &input) {
    if (!input.size())
        throw Exception(INVALID_INPUT, "Read an empty input line.");
    BookstoreLexer input_str;
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() != 1)
            throw Exception(INVALID_INPUT, "Exit or quit message followed with unexpected parameters.");
        *this = BookstoreParser(QUIT, QUIT_DEF, input_str);
        return;
    }
    if (input[0] == "su") {
        if (input.size() == 2) {
            input_str.push_back(input[1]);
            *this = BookstoreParser(SU, SU_NO_PASSWD, input_str);
            return;
        }
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            *this = BookstoreParser(SU, SU_PASSWD, input_str);
            return;
        }
        throw Exception(INVALID_INPUT, "Su message followed with unexpected parameters.");
    }
    if (input[0] == "logout") {
        if (input.size() != 1)
            throw Exception(INVALID_INPUT, "Logout message followed with unexpected parameters.");
        *this = BookstoreParser(LOGOUT, LOGOUT_DEF, BookstoreLexer());
        return;
    }
    if (input[0] == "register") {
        if (input.size() != 4)
            throw Exception(INVALID_INPUT, "Register message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        *this = BookstoreParser(REG, REG_DEF, input_str);
        return;
    }
    if (input[0] == "passwd") {
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            *this = BookstoreParser(PASSWD, PASSWD_NO_CUR, input_str);
            return;
        }
        if (input.size() == 4) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            input_str.push_back(input[3]);
            *this = BookstoreParser(PASSWD, PASSWD_CUR, input_str);
            return;
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
        *this = BookstoreParser(USERADD, USERADD_DEF, input_str);
        return;
    }
    if (input[0] == "delete") {
        if (input.size() != 2)
            throw Exception(INVALID_INPUT, "Delete message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(DEL, DEL_DEF, input_str);
        return;
    }
    if (input[0] == "show") {
        if (input.size() != 1 && input.size() != 3)
            throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
        if (input.size() == 1) {
            *this = BookstoreParser(SHOW, SHOW_DEF, input_str);
            return;
        }
        BookstoreLexer input_div(input[1], '=');
        if (input_div.size() != 2)
            throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
        input_str.push_back(input_div[1]);
        if (input_div[0] == "-ISBN")
            *this = BookstoreParser(SHOW, SHOW_ISBN, input_str);
        else {
            input_str[0] = input_div[1].substr(1, input_div[1].size() - 2);
            if (input_div[0] == "-name")
                *this = BookstoreParser(SHOW, SHOW_NAME, input_str);
            else if (input_div[0] == "-author")
                *this = BookstoreParser(SHOW, SHOW_AUTHOR, input_str);
            else if (input_div[0] == "-keyword")
                *this = BookstoreParser(SHOW, SHOW_KEYWORD, input_str);
            else throw Exception(INVALID_INPUT, "Show message followed with unexpected parameters.");
        }
        return;
    }
    if (input[0] == "buy") {
        if (input.size() != 3)
            throw Exception(INVALID_INPUT, "Buy message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(BUY, BUY_DEF, input_str);
        return;
    }
    if (input[0] == "select") {
        if (input.size() != 2)
            throw Exception(INVALID_INPUT, "Select message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(SEL, SEL_DEF, input_str);
        return;
    }
    if (input[0] == "modify") {
        if (input.size() < 2)
            throw Exception(INVALID_INPUT, "Modify message followed with unexpected parameters.");
        int siz = input.size();
        for (int i = 1; i < siz; i++) {
            BookstoreLexer input_div(input[i], '=');
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
        *this = BookstoreParser(IMPORT, IMPORT_DEF, input_str);
        return;
    }
    throw Exception(INVALID_INPUT, "Unexpected input message");
}

} // namespace input

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

void Bookstore::AcceptMsg(input::BookstoreParser msg) {
    using namespace input;
    if (msg.func == QUIT)
        throw Exception(QUIT_SYSTEM, "Quit.");
    if (msg.func == SU) {
        if (msg.info == SU_NO_PASSWD) {
            users.UserRegister(msg.args[0].c_str(), "", msg.args[1].c_str());
        } else {
            users.UserRegister(msg.args[0].c_str(), msg.args[1].c_str(), msg.args[2].c_str());
        }
        return;
    }
    if (msg.func == LOGOUT) {
        users.UserLogout();
        return;
    }
    if (msg.func == REG) {
        users.UserRegister(msg.args[0].c_str(), msg.args[1].c_str(), msg.args[2].c_str());
        return;
    }
    if (msg.func == PASSWD) {
        users.ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(), msg.args[2].c_str());
        return;
    }
    throw Exception(UNIMPLEMENTED, "Bookstore doesn't support this operation.");
}

} // namespace bookstore