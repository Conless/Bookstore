#include "TokenScanner.h"

#include <cctype>
#include <cstring>

#include "Utils/Exception.h"

namespace bookstore {

namespace input {

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
    for (const char &ch : str_in_line)
        if (!isprint(ch))
            throw InvalidException("Invisible char");
    for (int i = 0; i < siz; i++) {
        if (str_in_line[i] == divide_opt) {
            push_back(str_in_line.substr(las, i - las));
            las = i + 1;
            if (divide_opt == '=' && las < str_in_line.size()) {
                push_back(str_in_line.substr(las, str_in_line.size() - las));
                return;
            }
        } else if (i == siz - 1) {
            push_back(str_in_line.substr(las, i - las + 1));
        }
    }
}

bool ValidateUserInfo(const std::string &str) {
    if (str.size() > 30)
        return false;
    for (const char &ch : str) {
        if (!(isalpha(ch) || isdigit(ch) || ch == '_'))
            return false;
    }
    return true;
}
bool ValidateUserName(const std::string &str) { return str.size() <= 30; }
bool ValidateUserPriv(const std::string &str) {
    return str == "1" || str == "3" || str == "7";
}
bool ValidateQuotation(std::string &str) {
    if (str.size() <= 2)
        return false;
    if (str[0] != '\"')
        return false;
    else
        str.erase(0, 1);
    if (str[str.size() - 1] != '\"')
        return false;
    else
        str.erase(str.size() - 1, 1);
    if (str.find('\"') != std::string::npos)
        return false;
    return true;
}
bool ValidateBookISBN(const std::string &str) { return str.size() <= 20; }
bool ValidateBookInfo(const std::string &str) { return str.size() <= 60; }
bool ValidateInt(const std::string &str) {
    if (str.size() > 10)
        return false;
    if (str.size() != 1 && str[0] == '0')
        return false;
    for (const char &ch : str) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}
bool ValidatePosInt(const std::string &str) {
    return ValidateInt(str) && str != "0";
}
bool ValidateDouble(const std::string &str) {
    if (str.size() > 13)
        return false;
    if ((str[0] == '0' && str[1] != '.' && str != "0") || str[0] == '.' ||
        str[str.size() - 1] == '.')
        return false;
    bool dot_flag = 0;
    for (const char &ch : str) {
        if (ch == '.') {
            if (dot_flag)
                return false;
            dot_flag = 1;
        } else if (!isdigit(ch))
            return false;
    }
    return true;
}
bool ValidatePosDouble(const std::string &str) {
    return ValidateDouble(str) && std::stod(str) != 0.0;
}

BookstoreParser::BookstoreParser(const BookstoreLexer &input) {
    if (!input.size())
        throw NormalException(EMPTY_INPUT);
    BookstoreLexer input_str;
    if (input[0] == "exit" || input[0] == "quit") {
        if (input.size() != 1)
            throw InputException(input[0]);
        *this = BookstoreParser(QUIT, input_str);
        return;
    }
    if (input[0] == "su") {
        for (int i = 1; i < input.size(); i++) {
            if (!ValidateUserInfo(input[i]))
                throw InputException(input[0]);
        }
        if (input.size() == 2) {
            input_str.push_back(input[1]);
            input_str.push_back("");
            *this = BookstoreParser(SU, input_str);
        } else if (input.size() == 3) {
            input_str.push_back(input[1]);
            input_str.push_back(input[2]);
            *this = BookstoreParser(SU, input_str);
        } else
            throw InputException(input[0]);
        return;
    }
    if (input[0] == "logout") {
        if (input.size() != 1)
            throw InputException(input[0]);
        *this = BookstoreParser(LOGOUT, BookstoreLexer());
        return;
    }
    if (input[0] == "register") {
        if (input.size() != 4)
            throw InputException(input[0]);
        if (!ValidateUserInfo(input[1]) || !ValidateUserInfo(input[2]) ||
            !ValidateUserName(input[3]))
            throw InputException(input[0]);
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        *this = BookstoreParser(REG, input_str);
        return;
    }
    if (input[0] == "passwd") {
        for (int i = 1; i < input.size(); i++) {
            if (!ValidateUserInfo(input[i]))
                throw InputException(input[0]);
        }
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
        throw InputException(input[0]);
    }
    if (input[0] == "useradd") {
        if (input.size() != 5)
            throw InputException(input[0]);
        if (!ValidateUserInfo(input[1]) || !ValidateUserInfo(input[2]) ||
            !ValidateUserPriv(input[3]) || !ValidateUserName(input[3]))
            throw InputException(input[0]);
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        input_str.push_back(input[3]);
        input_str.push_back(input[4]);
        *this = BookstoreParser(USERADD, input_str);
        return;
    }
    if (input[0] == "delete") {
        if (input.size() != 2)
            throw InputException(input[0]);
        if (!ValidateUserInfo(input[1]))
            throw InputException(input[0]);
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
            else if (input.size() == 3) {
                if (!ValidateInt(input[2]))
                    throw InputException(input[0]);
                input_str.push_back(input[2]);
            } else
                throw InputException(input[0]);
            *this = BookstoreParser(FINANCE, input_str);

        } else {
            if (input.size() > 2)
                throw InputException(input[0]);
            BookstoreLexer input_div(input[1], '=');
            if (input_div.size() != 2)
                throw InputException(input[0]);
            if (!input_div[1].size())
                throw InputException(input[0]);
            if (input_div[0] == "-ISBN") {
                if (!ValidateBookISBN(input_div[1]))
                    throw InputException(input[0]);
                input_str.push_back(input_div[1]);
                *this = BookstoreParser(SHOW_ISBN, input_str);
            } else {
                if (!ValidateQuotation(input_div[1]) ||
                    !ValidateBookInfo(input_div[1]))
                    throw InputException(input[0]);
                input_str.push_back(input_div[1]);
                if (input_div[0] == "-name")
                    *this = BookstoreParser(SHOW_NAME, input_str);
                else if (input_div[0] == "-author")
                    *this = BookstoreParser(SHOW_AUTHOR, input_str);
                else if (input_div[0] == "-keyword")
                    *this = BookstoreParser(SHOW_KEYWORD, input_str);
                else
                    throw InputException(input[0]);
            }
        }
        return;
    }
    if (input[0] == "buy") {
        if (input.size() != 3)
            throw InputException(input[0]);
        if (!ValidateBookISBN(input[1]) || !ValidatePosInt(input[2]))
            throw InputException(input[0]);
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(BUY, input_str);
        return;
    }
    if (input[0] == "select") {
        if (input.size() != 2)
            throw InputException(input[0]);
        if (!ValidateBookISBN(input[1]))
            throw InputException(input[0]);
        input_str.push_back(input[1]);
        *this = BookstoreParser(SEL, input_str);
        return;
    }
    if (input[0] == "modify") {
        if (input.size() < 2)
            throw InvalidException("Modify with no parameters");
        int siz = input.size();
        input_str.resize(5);
        input_str[0] = input_str[1] = input_str[2] = input_str[3] =
            input_str[4] = "";
        for (int i = 1; i < siz; i++) {
            BookstoreLexer input_div(input[i], '=');
            if (input_div.size() != 2)
                throw InputException(input[0]);
            if (!input_div[1].size())
                throw InvalidException("No parameters");
            int opt;
            if (input_div[0] == "-ISBN")
                opt = 0;
            else if (input_div[0] == "-name")
                opt = 1;
            else if (input_div[0] == "-author")
                opt = 2;
            else if (input_div[0] == "-keyword")
                opt = 3;
            else if (input_div[0] == "-price")
                opt = 4;
            else
                throw InputException(input[0]);
            if (input_str[opt] != "")
                throw InvalidException("Repeated modify parameters");
            if (opt == 0) {
                if (!ValidateBookISBN(input_div[1]))
                    throw InputException(input[0]);
            } else if (opt == 4) {
                if (!ValidateDouble(input_div[1]))
                    throw InputException(input[0]);
            } else {
                if (input_div[1].size() <= 2)
                    throw InvalidException("No parameters");
                if (!ValidateQuotation(input_div[1]) ||
                    !ValidateBookInfo(input_div[1]))
                    throw InputException(input[0]);
            }
            input_str[opt] = input_div[1];
        }
        if (input_str[4] == "")
            input_str[4] = "-1";
        *this = BookstoreParser(MODIFY, input_str);
        return;
    }
    if (input[0] == "import") {
        if (input.size() != 3)
            throw InvalidException(
                "Import message followed with unexpected parameters.");
        if (!ValidatePosInt(input[1]) || !ValidatePosDouble(input[2]))
            throw InputException(input[0]);
        input_str.push_back(input[1]);
        input_str.push_back(input[2]);
        *this = BookstoreParser(IMPORT, input_str);
        return;
    }
    throw InvalidException("Sorry, bookstore doesn't support this operation.");
}

} // namespace input

} // namespace bookstore
