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

#include "File/FileSystem.h"

#include <cstring>
#include <vector>

namespace bookstore {

namespace list {

typedef unsigned int IndexType;

class UnrolledLinkedList;

class UnrolledLinkedList {
  public:
    UnrolledLinkedList(const char *file_name);
    ~UnrolledLinkedList();

  public:
    size_t size();
    bool empty();
    void clear();

  public:
    void insert(const char *key, const int value);
    std::vector<int> find(const char *key);
    void erase(const char *key, const int data);

    void haha();

  protected:
    

  private:
    // The type of key, of a maximum string len of 64.
    static const size_t kMaxKeyLen = 64 + 1;
    class KeyType;

    // The type of value
    typedef int ValueType;

    // The type of data
    class DataType;

    // The type of block
    static const size_t kMinBlockSize = 128;
    static const size_t kMaxBlockSize = 512;
    class ListBlock;

    static ListBlock buffer;
    std::fstream file;
};



} // namespace list

} // namespace bookstore
#endif