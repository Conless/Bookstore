#include <fstream>

namespace bookstore {

namespace file {

class FileSystem {
  public:
    FileSystem(const std::string &str);
    std::istream operator>>(int &value);
    std::ostream operator<<(const int &value);

  private:
    std::fstream file;
};

} // namespace file

} // namespace bookstore
