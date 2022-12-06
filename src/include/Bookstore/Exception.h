#include <string>

enum ExceptionType {
    INVALID_INPUT,
    UNIMPLEMENTED,
    UNKNOWN
};

struct Exception {
    ExceptionType opt;
    std::string msg;
    Exception(ExceptionType opt, std::string msg) : opt(opt), msg(msg) {}
};
