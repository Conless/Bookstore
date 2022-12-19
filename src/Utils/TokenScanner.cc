#include "TokenScanner.h"

#include "Utils/Exception.h"

namespace bookstore {

namespace input {

BookstoreLexer::BookstoreLexer(const std::string &str_in_line,
                               char divide_opt) {
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
        throw UnknownException(INPUT, "Read an empty input line.");
    BookstoreLexer input_str;
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() != 1)
            throw UnknownException(INPUT, 
                "Exit or quit message followed with unexpected parameters.");
        *this = BookstoreParser(QUIT, DEFAULT, input_str);
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
        throw UnknownException(INPUT, 
            "Su message followed with unexpected parameters.");
    }
    if (input[0] == "logout") {
        if (input.size() != 1)
            throw UnknownException(INPUT, 
                "Logout message followed with unexpected parameters.");
        *this = BookstoreParser(LOGOUT, DEFAULT, BookstoreLexer());
        return;
    }
    if (input[0] == "register") {
        if (input.size() != 4)
            throw UnknownException(INPUT, 
                "Register message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        *this = BookstoreParser(REG, DEFAULT, input_str);
        return;
    }
    if (input[0] == "passwd") {
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back("");
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
        throw UnknownException(INPUT, 
            "Passwd message followed with unexpected parameters.");
    }
    if (input[0] == "useradd") {
        if (input.size() != 5)
            throw UnknownException(INPUT, 
                "Useradd message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        input_str.push_back(input[4]);
        *this = BookstoreParser(USERADD, DEFAULT, input_str);
        return;
    }
    if (input[0] == "delete") {
        if (input.size() != 2)
            throw UnknownException(INPUT, 
                "Delete message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(DEL, DEFAULT, input_str);
        return;
    }
    if (input[0] == "show") {
        if (input.size() != 1 && input.size() != 3)
            throw UnknownException(INPUT, 
                "Show message followed with unexpected parameters.");
        if (input.size() == 1) {
            *this = BookstoreParser(SHOW, DEFAULT, input_str);
            return;
        }
        BookstoreLexer input_div(input[1], '=');
        if (input_div.size() != 2)
            throw UnknownException(INPUT, 
                "Show message followed with unexpected parameters.");
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
            else
                throw UnknownException(INPUT, 
                    "Show message followed with unexpected parameters.");
        }
        return;
    }
    if (input[0] == "buy") {
        if (input.size() != 3)
            throw UnknownException(INPUT, 
                            "Buy message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(BUY, DEFAULT, input_str);
        return;
    }
    if (input[0] == "select") {
        if (input.size() != 2)
            throw UnknownException(INPUT, 
                "Select message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(SEL, DEFAULT, input_str);
        return;
    }
    if (input[0] == "modify") {
        if (input.size() < 2)
            throw UnknownException(INPUT, 
                "Modify message followed with unexpected parameters.");
        int siz = input.size();
        input_str.resize(4);
        input_str[0] = input_str[1] = input_str[2] = input_str[3] = "";
        for (int i = 1; i < siz; i++) {
            BookstoreLexer input_div(input[i], '=');
            if (input_div.size() != 2)
                throw UnknownException(INPUT, 
                    "Modify message followed with unexpected parameters.");
            input_str.push_back(input_div[0]);
            if (input_div[0] == "-ISBN")
                input_str[0] = input_div[1];
            else if (input_div[0] == "-name")
                input_str[1] = input_div[1].substr(1, input_div[1].size() - 2);
            else if (input_div[0] == "-author")
                input_str[2] = input_div[1].substr(1, input_div[1].size() - 2);
            else if (input_div[0] == "-keyword")
                input_str[3] = input_div[1].substr(1, input_div[1].size() - 2);
            else
                throw UnknownException(INPUT, 
                    "Modify message followed with unexpected parameters.");
            *this = BookstoreParser(MODIFY, DEFAULT, input_str);
        }
        return;
    }
    if (input[0] == "import") {
        if (input.size() != 3)
            throw UnknownException(INPUT, 
                "Import message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(IMPORT, DEFAULT, input_str);
        return;
    }
    throw InvalidException("Sorry, bookstore doesn't support this operation.");
}

} // namespace input

} // namespace bookstore
