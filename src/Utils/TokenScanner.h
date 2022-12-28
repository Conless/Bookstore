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
    SHOW_ALL,
    SHOW_ISBN,
    SHOW_NAME,
    SHOW_AUTHOR,
    SHOW_KEYWORD,
    BUY,
    SEL,
    MODIFY,
    IMPORT,
    FINANCE,
    LOG
};

class BookstoreLexer : public std::vector<std::string> {
  public:
    BookstoreLexer() {}
    BookstoreLexer(std::string str_in_line, char divide_opt = ' ');
    const char ** c_str();
};

class BookstoreParser {
  public:
    Function func;
    BookstoreLexer args;
    BookstoreParser(Function func, BookstoreLexer args) : func(func), args(args) {}

  public:
    BookstoreParser(const BookstoreLexer &input);
};

} // namespace input

} // namespace bookstore

#endif
