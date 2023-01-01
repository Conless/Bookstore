/**
 * @file UnrolledLinkedList.h
 * @author Conless Pan (conlesspan@outlook.com)
 * @brief
 * @version 0.2
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BOOKSTORE_LIST_ULL_H
#define BOOKSTORE_LIST_ULL_H

#include <cstring>
#include <fstream>
#include <set>
#include <string>
#include <vector>

namespace bookstore {

namespace list {

/**
 * @brief Class KeyType
 * @details Package the char array at a size of kMaxKeyLen, enable assignment
 * and comparison.
 */
template <size_t kMaxKeyLen> class KeyType {
  public:
    KeyType() { memset(str, 0, sizeof(str)); }
    explicit KeyType(const char *_str) {
        memset(str, 0, sizeof(str));
        strcpy(str, _str);
    }
    KeyType operator=(const char *_str) {
        memset(str, 0, sizeof(str));
        strcpy(str, _str);
        return *this;
    }
    KeyType(const KeyType &x) {
        memset(str, 0, sizeof(str)), strcpy(str, x.str);
    }

    bool empty() const { return strcmp(str, "") == 0; }
    bool operator<(const KeyType &x) const { return strcmp(str, x.str) < 0; }
    bool operator<(const char *x) const { return strcmp(str, x) < 0; }
    bool operator>(const KeyType &x) const { return strcmp(str, x.str) > 0; }
    bool operator==(const KeyType &x) const { return strcmp(str, x.str) == 0; }
    bool operator==(const char *x) const { return strcmp(str, x) == 0; }
    friend bool operator==(const char *x, const KeyType &y) {
        return strcmp(y.str, x) == 0;
    }
    bool operator!=(const KeyType &x) const { return !(*this == x); }
    bool operator<=(const KeyType &x) const { return !(*this > x); }
    bool operator>=(const KeyType &x) const { return !(*this < x); }
    operator std::string() const { return std::string(str); }

  public:
    char str[kMaxKeyLen];
};

/**
 * @brief Class DataType
 * @details Package the pair of key and value, enable assignment and comparison.
 */
template <size_t kMaxKeyLen> class DataType {
  public:
    KeyType<kMaxKeyLen> key;
    int value;
    DataType() : key(), value(0) {}
    DataType(KeyType<kMaxKeyLen> _key, int _value) : key(_key), value(_value) {}
    bool operator<(const DataType &x) const {
        return key == x.key ? value < x.value : key < x.key;
    }
    bool operator>(const DataType &x) const {
        return key == x.key ? value > x.value : key > x.key;
    }
    bool operator==(const DataType &x) const {
        return key == x.key && value == x.value;
    }
    bool operator!=(const DataType &x) const { return !(*this == x); }
    bool operator<=(const DataType &x) const { return !(*this > x); }
    bool operator>=(const DataType &x) const { return !(*this < x); }
};

/**
 * @brief Class ListBlock
 * @details The type of a whole block, with fixed length kMaxBlockSize + 10.
 * Split when the length of a block is greater than kMaxBlockSize.
 */
template <size_t kMaxKeyLen> class ListBlock {
  public:
    ListBlock() : data(), len(0), pos(0) {}
    ListBlock(size_t _len, size_t _pos) : len(_len), pos(_pos) {}
    ~ListBlock() {}

  public:
    DataType<kMaxKeyLen> *data;
    DataType<kMaxKeyLen> head, tail;
    size_t len;
    size_t pos;
};

/**
 * @brief class UnrolledLinkedList
 * @details The main part of the data structure, with the operations below
 supported
    - Insert, delete, find a data in O(sqrt(n))
    - Running with ram space O(sqrt(n)) and file space O(n)
 */
template <size_t kMaxKeyLen> class UnrolledLinkedList {
  public:
    // The constructor of ull
    UnrolledLinkedList(const std::string &file_name);

    // The destructor of ull
    ~UnrolledLinkedList();

  public:
    // Judge whether the ull is empty
    bool empty() const;

    // Operations
    void insert(const char *key, const int value) {
        insert(KeyType<kMaxKeyLen>(key), value);
    }
    void erase(const char *key, const int value) {
        erase(KeyType<kMaxKeyLen>(key), value);
    }
    std::vector<int> find(const char *key) {
        return find(KeyType<kMaxKeyLen>(key));
    }

    // Operations of custom string
    void insert(const KeyType<kMaxKeyLen> &key, const int value);
    int erase(const KeyType<kMaxKeyLen> &key, const int value);
    std::vector<int> find(const KeyType<kMaxKeyLen> &key);

  protected:
    // The type of block
    static const size_t kMinBlockSize = 128;
    static const size_t kMaxBlockSize = 256;

    // The maximum number of blocks
    static const size_t kMaxBlockCnt = 1000;

  protected:
    // Get the size of ull
    size_t size();

    // Output the data of a block
    void output(ListBlock<kMaxKeyLen> &cur);

    // Allocate a block
    void allocate(ListBlock<kMaxKeyLen> &cur);

    // Deallocate a block
    void deallocate(ListBlock<kMaxKeyLen> &cur);

    virtual bool is_same(const DataType<kMaxKeyLen> &data,
                         const DataType<kMaxKeyLen> &tmp);

    // Insert a data to a block
    void insert(ListBlock<kMaxKeyLen> &cur, const DataType<kMaxKeyLen> &tmp);

    // Erase a data from the block
    int erase(ListBlock<kMaxKeyLen> &cur, const DataType<kMaxKeyLen> &tmp);

    // Find some data in the block
    std::vector<int> find(ListBlock<kMaxKeyLen> &cur,
                          const KeyType<kMaxKeyLen> &key);

    // Split a block
    ListBlock<kMaxKeyLen> split(ListBlock<kMaxKeyLen> &cur);

    void merge_try(int pos);

    // Merge two blocks
    void merge(ListBlock<kMaxKeyLen> &cur, ListBlock<kMaxKeyLen> &del);

  private:
    // Info of the file system
    std::fstream file;
    std::string file_name;

  private:
    // Info of the block system
    std::set<int> free_blocks;
    std::vector<ListBlock<kMaxKeyLen>> blocks;
};

template <size_t kMaxKeyLen>
class UnrolledLinkedListUnique : public UnrolledLinkedList<kMaxKeyLen> {
  public:
    UnrolledLinkedListUnique(const std::string _file_name)
        : UnrolledLinkedList<kMaxKeyLen>(_file_name) {}
    int erase(const KeyType<kMaxKeyLen> &key);
    int find(const KeyType<kMaxKeyLen> &key);

  protected:
    bool is_same(const DataType<kMaxKeyLen> &data,
                 const DataType<kMaxKeyLen> &tmp) override;
};

template class UnrolledLinkedList<25>;
template class UnrolledLinkedList<35>;
template class UnrolledLinkedList<65>;
template class UnrolledLinkedListUnique<25>;
template class UnrolledLinkedListUnique<35>;

} // namespace list

} // namespace bookstore

#endif
