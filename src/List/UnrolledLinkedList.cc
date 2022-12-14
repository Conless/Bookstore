/**
 * @file UnrolledLinkedList.cc
 * @author Conless Pan (conlesspan@outlook.com)
 * @brief The implementation for UnrolledLinkedList.h
 * @version 0.2
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "UnrolledLinkedList.h"
#include <algorithm>

namespace bookstore {
namespace list {

class UnrolledLinkedList::KeyType {
  public:
    KeyType() {}
    KeyType(const char *_str) { strcpy(str, _str); }
    KeyType(const KeyType &x) { strcpy(str, x.str); }

    bool operator<(const KeyType &x) const { return strcmp(str, x.str) < 0; }
    bool operator>(const KeyType &x) const { return strcmp(str, x.str) > 0; }
    bool operator==(const KeyType &x) const { return strcmp(str, x.str) != 0; }
    bool operator!=(const KeyType &x) const { return !(*this == x); }
    bool operator<=(const KeyType &x) const { return !(*this > x); }
    bool operator>=(const KeyType &x) const { return !(*this < x); }

  public:
    char str[kMaxKeyLen];
};

class UnrolledLinkedList::DataType {
  public:
    KeyType key;
    ValueType value;
    DataType() {}
    DataType(KeyType _key, ValueType _value) : key(_key), value(_value) {}
    bool operator<(const DataType &x) const { return key == x.key ? value < x.value : key < x.key; }
    bool operator>(const DataType &x) const { return key == x.key ? value > x.value : key > x.key; }
    bool operator==(const DataType &x) const { return key == x.key && value == x.value; }
    bool operator!=(const DataType &x) const { return !(*this == x); }
    bool operator<=(const DataType &x) const { return !(*this > x); }
    bool operator>=(const DataType &x) const { return !(*this < x); }
};

const int BlockSize = 300;

class UnrolledLinkedList::ListBlock {
  public:
    ListBlock() {}
    ~ListBlock() { delete data; }
    void haha() {
        data = new DataType[2];
        data[0] = DataType("b", 2);
        data[1] = DataType("a", 1);
    }
    void read(std::fstream &fin) {
        data = new DataType[2];
        fin.read(reinterpret_cast<char *>(data), BlockSize);
    }
    void write(std::fstream &fout) {
        fout.write(reinterpret_cast<char *>(data), BlockSize);
    }
    void insert(const DataType &tmp) {
        int pos = std::lower_bound(data, data + len, tmp) - data;
        std::copy(data + pos, data + len, data + pos + 1);
        data[pos] = tmp;
        return;
    }
  public:
    DataType *data;
    size_t len;
};

UnrolledLinkedList::UnrolledLinkedList(const char *file_name) { file.open(file_name); }
UnrolledLinkedList::~UnrolledLinkedList() { exit(0); }

void UnrolledLinkedList::haha() {
    ListBlock a, b;
    a.haha();
    file.seekp(0);
    a.write(file);
    puts(a.data[0].key.str);
    puts(a.data[0].key.str);
    file.seekg(0);
    b.read(file);
    puts(b.data[0].key.str);
    puts(b.data[0].key.str);
}

} // namespace list
} // namespace bookstore