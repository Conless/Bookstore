#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Book/BookSystem.h"
#include "User/UserSystem.h"

#include "Utils/TokenScanner.h"
#include <vector>

namespace bookstore {

class Bookstore : public user::UserSystem, public book::BookSystem {
  public:
    Bookstore();
    ~Bookstore();

    void AcceptMsg(const input::BookstoreParser &msg);

  public:
    void output();
};

void PrintHelp();
int JudgeInput(int argc, char *argv[]);

} // namespace bookstore

#endif
