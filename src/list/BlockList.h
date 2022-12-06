#include <list>
#include <vector>

namespace bookstore {

namespace list {

template <class KeyType, class DataType> class BlockList {
  public:
    void insert(const KeyType &key, const DataType &value);
    void remove(const KeyType &key, const DataType &value);
    std::vector<DataType> find(const KeyType &key);

  private:
    const int max_list_size = 10;
    typedef std::pair<KeyType, DataType> pr;
    std::list<std::list<pr>> data_list;
};



} // namespace list
} // namespace bookstore