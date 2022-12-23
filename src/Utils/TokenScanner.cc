#include "TokenScanner.h"

#include <cstring>

#include "Utils/Exception.h"

namespace bookstore {

namespace input {

int to_authentity(const Function &func) {
    if (func == QUIT || func == SU || func == REG)
        return 0;
    if (func == LOGOUT || func == PASSWD || func == SHOW_ALL ||
        func == SHOW_ISBN || func == SHOW_NAME || func == SHOW_AUTHOR ||
        func == SHOW_KEYWORD || func == BUY)
        return 1;
    if (func == USERADD || func == SEL || func == MODIFY || func == IMPORT)
        return 3;
    return 7;
}

void SimplifySpace(std::string &str) {
    while (str[0] == ' ')
        str.erase(0, 1);
    while (str[str.size() - 1] == ' ')
        str.erase(str.size() - 1, 1);
    for (int i = 1; i < str.size(); i++)
        if (str[i] == str[i - 1] && str[i] == ' ') {
            str.erase(i, 1);
            i--;
        }
}

BookstoreLexer::BookstoreLexer(std::string str_in_line, char divide_opt) {
    SimplifySpace(str_in_line);
    int las = 0;
    int siz = str_in_line.size();
    for (int i = 0; i < siz; i++) {
        if (!isprint(str_in_line[i]))
            throw InvalidException("Invisible char");
        if (str_in_line[i] == divide_opt) {
            push_back(str_in_line.substr(las, i - las));
            las = i + 1;
        } else if (i == siz - 1) {
            push_back(str_in_line.substr(las, i - las + 1));
        }
    }
}

BookstoreParser::BookstoreParser(const BookstoreLexer &input) {
    if (!input.size())
        throw NormalException(EMPTY_INPUT);
    BookstoreLexer input_str;
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() != 1)
            throw InvalidException(
                "Exit or quit message followed with unexpected parameters.");
        *this = BookstoreParser(QUIT, input_str);
        return;
    }
    if (input[0] == "su") {
        if (input.size() == 2) {
            input_str.push_back(input[1]);
            input_str.push_back("");
            *this = BookstoreParser(SU, input_str);
        } else if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            *this = BookstoreParser(SU, input_str);
        } else
            throw InvalidException(
                "Su message followed with unexpected parameters.");
        return;
    }
    if (input[0] == "logout") {
        if (input.size() != 1)
            throw InvalidException(
                "Logout message followed with unexpected parameters.");
        *this = BookstoreParser(LOGOUT, BookstoreLexer());
        return;
    }
    if (input[0] == "register") {
        if (input.size() != 4)
            throw InvalidException(
                "Register message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        *this = BookstoreParser(REG, input_str);
        return;
    }
    if (input[0] == "passwd") {
        if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back("");
            input_str.push_back(input[2]);
            *this = BookstoreParser(PASSWD, input_str);
            return;
        }
        if (input.size() == 4) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            input_str.push_back(input[3]);
            *this = BookstoreParser(PASSWD, input_str);
            return;
        }
        throw InvalidException(
            "Passwd message followed with unexpected parameters.");
    }
    if (input[0] == "useradd") {
        if (input.size() != 5)
            throw InvalidException(
                "Useradd message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        input_str.push_back(input[4]);
        *this = BookstoreParser(USERADD, input_str);
        return;
    }
    if (input[0] == "delete") {
        if (input.size() != 2)
            throw InvalidException(
                "Delete message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(DEL, input_str);
        return;
    }
    if (input[0] == "show") {
        if (input.size() == 1) {
            *this = BookstoreParser(SHOW_ALL, input_str);
        } else if (input[1] == "finance") {
            if (input.size() == 2)
                ;
            else if (input.size() == 3)
                input_str.push_back(input[2]);
            else
                throw InvalidException("Show Finance message followed "
                                       "with unexpected parameters.");
            *this = BookstoreParser(FINANCE, input_str);

        } else {
            BookstoreLexer input_div(input[1], '=');
            if (input_div.size() != 2)
                throw InvalidException(
                    "Show message followed with unexpected parameters.");
            if (!input_div[1].size())
                throw InvalidException("No parameters");
            input_str.push_back(input_div[1]);
            if (input_div[0] == "-ISBN")
                *this = BookstoreParser(SHOW_ISBN, input_str);
            else {
                if (input_div[1].size() <= 2)
                    throw InvalidException("No parameters");
                if (input_div[1][0] != '\"')
                    throw InvalidException("Quotation mark not found");
                else
                    input_div[1].erase(0, 1);
                if (input_div[1][input_div[1].size() - 1] != '\"')
                    throw InvalidException("Quotation mark not found");
                else
                    input_div[1].erase(input_div[1].size() - 1, 1);
                if (input_div[1].find('\"') != std::string::npos)
                    throw InvalidException("Quotation mark not allowed");
                input_str[0] = input_div[1];
                if (input_div[0] == "-name")
                    *this = BookstoreParser(SHOW_NAME, input_str);
                else if (input_div[0] == "-author")
                    *this = BookstoreParser(SHOW_AUTHOR, input_str);
                else if (input_div[0] == "-keyword")
                    *this = BookstoreParser(SHOW_KEYWORD, input_str);
                else
                    throw InvalidException(
                        "Show message followed with unexpected parameters.");
            }
        }
        return;
    }
    if (input[0] == "buy") {
        if (input.size() != 3)
            throw InvalidException(
                "Buy message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(BUY, input_str);
        return;
    }
    if (input[0] == "select") {
        if (input.size() != 2)
            throw InvalidException(
                "Select message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        *this = BookstoreParser(SEL, input_str);
        return;
    }
    // if (input[0] == "modify") {
    //     if (input.size() < 2)
    //         throw InvalidException("Modify with no parameters");
    //     int siz = input.size();
    //     input_str.resize(5);
    //     input_str[0] = input_str[1] = input_str[2] = input_str[3] =
    //         input_str[4] = "";
    //     for (int i = 1; i < siz; i++) {
    //         BookstoreLexer input_div(input[i], '=');
    //         if (input_div.size() != 2)
    //             throw InvalidException(
    //                 "Modify message followed with unexpected parameters.");
    //         if (!input_div[1].size())
    //             throw InvalidException("No parameters");
    //         int opt;
    //         if (input_div[0] == "-ISBN")
    //             opt = 0;
    //         else if (input_div[0] == "-name")
    //             opt = 1;
    //         else if (input_div[0] == "-author")
    //             opt = 2;
    //         else if (input_div[0] == "-keyword")
    //             opt = 3;
    //         else if (input_div[0] == "-price")
    //             opt = 4;
    //         else
    //             throw InvalidException(
    //                 "Modify message followed with unexpected parameters.");
    //         if (input_str[opt] != "")
    //             throw InvalidException("Repeated modify parameters");
    //         if (opt != 0 && opt != 4) {
    //             if (input_div[1].size() <= 2)
    //                 throw InvalidException("No parameters");
    //             if (input_div[1][0] != '\"')
    //                 throw InvalidException("Quotation mark not found");
    //             else
    //                 input_div[1].erase(0, 1);
    //             if (input_div[1][input_div[1].size() - 1] != '\"')
    //                 throw InvalidException("Quotation mark not found");
    //             else
    //                 input_div[1].erase(input_div[1].size() - 1, 1);
    //             // if (input_div[1].size() <= 2 || input_div[1][0] != '\"' ||
    //             //     input_div[1][input_div[1].size() - 1] != '\"')
    //             //     throw InvalidException("Quotation not found");
    //             // input_div[1].erase(0, 1);
    //             // input_div[1].erase(input_div[1].size() - 1, 1);
    //             if (input_div[1].find('\"') != std::string::npos)
    //                 throw InvalidException("Quotation mark not allowed");
                
    //             // if (input_div[1].find('\"') != std::string::npos)
    //             //     throw InvalidException("Quotation mark not allowed");
    //         }
    //         if (!input_div.size())
    //             throw InvalidException("Check length");
    //         input_str[opt] = input_div[1];
    //     }
    //     *this = BookstoreParser(MODIFY, input_str);
    //     return;
    // }
    if (input[0] == "import") {
        if (input.size() != 3)
            throw InvalidException(
                "Import message followed with unexpected parameters.");
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(IMPORT, input_str);
        return;
    }
    throw InvalidException("Sorry, bookstore doesn't support this operation.");
}

} // namespace input

} // namespace bookstore
