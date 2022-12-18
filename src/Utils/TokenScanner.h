#ifndef BOOKSTORE_TOKENSCANNER_H
#define BOOKSTORE_TOKENSCANNER_H

#include <string>
#include <vector>

namespace bookstore {

namespace input {

enum Function {
    QUIT,
    SU,
    LOGOUT,
    REG,
    PASSWD,
    USERADD,
    DEL,
    SHOW,
    BUY,
    SEL,
    MODIFY,
    IMPORT
};
enum FunctionData {
    DEFAULT,
    SU_PASSWD,
    SU_NO_PASSWD,
    PASSWD_NO_CUR,
    PASSWD_CUR,
    SHOW_ALL,
    SHOW_ISBN,
    SHOW_NAME,
    SHOW_AUTHOR,
    SHOW_KEYWORD,
};

class BookstoreLexer : public std::vector<std::string> {
  public:
    BookstoreLexer() {}
    BookstoreLexer(const std::string &str_in_line, char divide_opt = ' ');
};

class BookstoreParser {
  public:
    Function func;
    FunctionData info;
    BookstoreLexer args;
    BookstoreParser(Function func, FunctionData info, BookstoreLexer args) : func(func), info(info), args(args) {}

  public:
    BookstoreParser(const BookstoreLexer &input);
};

} // namespace input

} // namespace bookstore

#endif