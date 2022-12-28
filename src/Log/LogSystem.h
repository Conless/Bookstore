#ifndef BOOKSTORE_LOG_SYSTEM_H
#define BOOKSTORE_LOG_SYSTEM_H

#include <fstream>

class LogSystem {
  public:
    LogSystem() : fout("data/Bookstore.log") {}

  private:
    std::fstream fout;
        
}

#endif