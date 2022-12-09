#include <string>
#include <vector>

namespace bookstore {

namespace list {

typedef char KeyType[10];
typedef int DataType;

const int kSizeOfKey = sizeof(KeyType);
const int kSizeOfData = sizeof(DataType);
const int kSizeOfLine = kSizeOfKey + kSizeOfData * 2;

struct Line {
    std::string key;
    int data, next;
};

class UnrolledLinkedList {
  private:
    class Block;
    const int max_list_size = 10;
    std::string file_path;
    std::vector<int> head, tail;
    int cnt;
    typedef std::pair<std::string, int> pr;
    // std::list<std::list<pr>> data_list;

    Line ReadLine(int pos);
    int InsertData(int pos, const std::string key);

  public:
    UnrolledLinkedList(const std::string file_name);
    ~UnrolledLinkedList();
    void insert(const std::string key, DataType data);
};

} // namespace list
} // namespace bookstore