#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Book/BookSystem.h"
#include "User/UserSystem.h"

#include "Utils/TokenScanner.h"
#include <vector>

namespace bookstore {

class Bookstore {
  public:
    Bookstore();
    ~Bookstore();

    void ReadData();
    void PrintData();
    void AcceptMsg(const input::BookstoreParser &msg);

  public:
    void output();

  private:
    user::UserSystem users;
    book::BookSystem books;
    std::string selected;
};

} // namespace bookstore

#endif
