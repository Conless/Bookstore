#ifndef BOOKSTORE_LOG_SYSTEM_H
#define BOOKSTORE_LOG_SYSTEM_H

#include "Utils/TokenScanner.h"
#include "Utils/Printer.h"

#include <fstream>

namespace bookstore {

namespace log {

typedef std::pair<std::string, int> UserData;

class LogSystem {
  public:
    LogSystem();
    void WriteInput(const std::string &str);
    void WriteInvalid(const std::string &str);
    void WriteLog(const UserData &cur, const UserData &tmp, const bookstore::input::BookstoreParser &msg);

  private:
    Printer fout;

};

} // namespace log
} // namespace bookstore

#endif