#ifndef BOOKSTORE_EXCEPTION_H
#define BOOKSTORE_EXCEPTION_H

#include <string>

enum ExceptionType {
    STD_INVALID,
    INPUT,
    NORMAL,
    UNIMPLEMENTED,
    UNKNOWN,
    QUIT_SYSTEM,
    ULL_ERASE_NOT_FOUND,
    ULL_INSERTED,
    ULL_NOT_FOUND,
    ULL_DUPLICATED
};

class BaseException {
  public:
    BaseException(ExceptionType _opt, const std::string &_msg)
        : opt(_opt), msg(_msg) {}
    std::string what() const { return msg; }

  private:
    ExceptionType opt;
    std::string msg;
};

class NormalException : public BaseException {
  public:
    NormalException(const ExceptionType &_opt) : BaseException(_opt, "") {}
};

class InvalidException : public BaseException {
  public:
    InvalidException(const std::string &_msg)
        : BaseException(STD_INVALID, _msg) {}
};
class UnknownException : public BaseException {
  public:
    UnknownException(const ExceptionType &_opt, const std::string &_msg)
        : BaseException(_opt, _msg) {}
};

#endif
