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

// #include "File/FileSystem.h"

#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <set>

namespace bookstore {

namespace list {

class UnrolledLinkedList;

class UnrolledLinkedList {
  public:
    UnrolledLinkedList(const std::string &file_name);
    ~UnrolledLinkedList();

  public:
    size_t size();
    bool empty();
    void clear();

  public:
    void insert(const char *key, const int value);
    std::vector<int> find(const char *key);
    void erase(const char *key, const int value);

  protected:
    // The type of key, of a maximum string len of 64.
    static const size_t kMaxKeyLen = 64 + 5;
    class KeyType;

    // The type of data
    class DataType;

    // The type of block
    static const size_t kMinBlockSize = 128;
    static const size_t kMaxBlockSize = 512;
    class ListBlock;

    static const size_t kMaxBlockCnt = 1000;

  public:
    void allocate(ListBlock &cur);
    void deallocate(ListBlock &cur);
    void insert(ListBlock &cur, const DataType &tmp);
    void erase(ListBlock &cur, const DataType &tmp);
    std::vector<int> find(ListBlock &cur, const char *key);
    ListBlock split(ListBlock &cur); 
    void output(ListBlock &cur);

    std::set<int> free_blocks;
    std::vector<ListBlock> blocks;

    std::fstream file;
    std::string file_name;
};

} // namespace list

} // namespace bookstore
#endif