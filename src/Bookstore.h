#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Book/BookSystem.h"
#include "User/UserSystem.h"

enum Function { quit, su, logout, reg, passwd, useradd, del, show, buy, sel, modify, import };

struct InputMsg {
    Function func;
    std::vector<std::string> args;
    InputMsg(Function func, std::vector<std::string> args) : func(func), args(args) {}
};

class Bookstore {
  public:
    Bookstore();
    ~Bookstore();

    void ReadData();
    void PrintData();
    void OperateMsg(InputMsg);

  private:
    UserSystem users;
    BookSystem books;
};

#endif
