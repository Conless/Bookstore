#include <bits/types/FILE.h>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <string>

namespace bookstore {

namespace file {

template <class DataType> class BaseFileSystem {
  public:
    explicit BaseFileSystem(const std::string _file_name) : file_name(_file_name) {
        std::filesystem::create_directories("data");
        std::ifstream checker("data/" + file_name + ".dat");
        if (!checker.good())
            std::ofstream creater("data/" + file_name + ".dat");
        checker.close();
        file.open("data/" + file_name + ".dat");
    }
    virtual ~BaseFileSystem() = default;
    void insert(int pos, DataType data) {
        file.seekp(sizeof(DataType) * (pos - 1));
        file.write(reinterpret_cast<char *>(&data), sizeof(DataType));
    }
    void erase(int pos) {
        DataType tmp = DataType();
        file.seekp(sizeof(DataType) * (pos - 1));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(DataType));
    }
    DataType find(int pos) {
        DataType ret;
        file.seekg(sizeof(DataType) * (pos - 1));
        file.read(reinterpret_cast<char *>(&ret), sizeof(DataType));
        return ret;
    }

  private:
    std::fstream file;
    std::string file_name;
    size_t size;
};


} // namespace file

} // namespace bookstore
