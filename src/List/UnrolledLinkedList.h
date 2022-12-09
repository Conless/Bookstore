#include <string>
#include <vector>
#include <fstream>

namespace bookstore {

namespace list {

typedef char KeyType[72];
typedef int DataType;

const size_t kSizeofKey = sizeof(KeyType);
const size_t kSizeofData = sizeof(DataType);
const size_t kSizeofLine = kSizeofKey + kSizeofData * 2;

struct Line {
    std::string key;
    DataType pos, data, next;
    Line() = default;
    Line(std::string key, DataType pos, DataType data, DataType next = 0) : key(key), pos(pos), data(data), next(next) {}
};

class UnrolledLinkedList {
  private:
    const DataType max_list_size = 100;
    std::vector<DataType> head, tail, siz;
    DataType cnt;
    std::fstream file;

    Line ReadLine(DataType pos);
    void WriteLine(DataType pos, Line now);
    DataType InsertData(DataType pos, const std::string key, DataType num, DataType data);
    void Simplify();
    void Output();

  public:
    UnrolledLinkedList(const std::string file_name);
    ~UnrolledLinkedList();
    void insert(const std::string key, DataType data);
    std::vector<DataType> find(const std::string key);
    void erase(const std::string key, DataType data);
};

} // namespace list
} // namespace bookstore