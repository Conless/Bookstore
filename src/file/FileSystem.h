#include <fstream>
#include <string>

namespace bookstore {

namespace file {

/**
 * @brief Class BaseBaseFileSystem
 * @details The base class of the file system
 * @tparam DataType
 */
class BaseFileSystem {
  public:
    // Constructor of the file system, file name required
    BaseFileSystem(const char *file_name) { f.open(file_name, std::ios::in | std::ios::out); }
    // Destructor of the file system
    ~BaseFileSystem() {}

  public:
    template <class DataType> void operator>>(DataType &value) { f.read(reinterpret_cast<char *>(&value), sizeof(value)); }
    template <class DataType>  void operator<<(DataType value) { f.write(reinterpret_cast<char *>(&value), sizeof(value)); }

  protected:
    std::fstream f;
};

class BlockedFileSystem : public BaseFileSystem {
  public:
    BlockedFileSystem(const char *file_name, const size_t _BlockSize) : BaseFileSystem(file_name), BlockSize(_BlockSize) {}
    ~BlockedFileSystem() {}
    template <class DataType> void operator>>(DataType &value) { this->f.read(reinterpret_cast<char *>(&value), BlockSize); }
    template <class DataType> void operator<<(DataType value) {
        this->f.write(reinterpret_cast<char *>(&value), BlockSize);
        this->f.flush();
    }

  public:
    void moveg(int pos) { this->f.seekg(pos * BlockSize); }
    void movep(int pos) { this->f.seekp(pos * BlockSize); }

  private:
    size_t BlockSize;
};

} // namespace file

} // namespace bookstore
