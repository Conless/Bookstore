#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Book/BookSystem.h"
#include "User/UserSystem.h"
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
    QUIT_DEF,
    SU_PASSWD,
    SU_NO_PASSWD,
    LOGOUT_DEF,
    REG_DEF,
    PASSWD_NO_CUR,
    PASSWD_CUR,
    USERADD_DEF,
    DEL_DEF,
    SHOW_DEF,
    SHOW_ISBN,
    SHOW_NAME,
    SHOW_AUTHOR,
    SHOW_KEYWORD,
    BUY_DEF,
    SEL_DEF,
    MODIFY_ISBN,
    MODIFY_NAME,
    MODIFY_AUTHOR,
    MODIFY_KEYWORD,
    IMPORT_DEF
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

class Bookstore {
  public:
    Bookstore();
    ~Bookstore();

    void ReadData();
    void PrintData();
    void AcceptMsg(input::BookstoreParser);

  private:
    user::UserSystem users;
    book::BookSystem books;
};

} // namespace bookstore

#endif
