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

#include <string>
#include <fstream>
#include <vector>
#include <set>

namespace bookstore {

namespace list {

/**
 * @brief class UnrolledLinkedList
 * @details The main part of the data structure, with the operations below supported
    - Insert, delete, find a data in O(sqrt(n))
    - Running with ram space O(sqrt(n)) and file space O(n)
 */
class UnrolledLinkedList {
  public:
    // The constructor of ull
    UnrolledLinkedList(const std::string &file_name);

    // The destructor of ull
    ~UnrolledLinkedList();

  public:
    // Judge whether the ull is empty
    bool empty() const;

    // Insert 
    void insert(const char *key, const int value);
    void erase(const char *key, const int value);
    std::vector<int> find(const char *key);

  protected:
    // The type of key, of a maximum string len of 64.
    static const size_t kMaxKeyLen = 64 + 5;
    class KeyType;

    // The type of data
    class DataType;

    // The type of block
    static const size_t kMinBlockSize = 128;
    static const size_t kMaxBlockSize = 256;
    class ListBlock;

    // The maximum number of blocks
    static const size_t kMaxBlockCnt = 1000;

  protected:
    // Get the size of ull
    size_t size();

    // Output the data of a block
    void output(ListBlock &cur);

    // Allocate a block
    void allocate(ListBlock &cur);

    // Deallocate a block
    void deallocate(ListBlock &cur);

    // Insert a data to a block
    void insert(ListBlock &cur, const DataType &tmp);

    // Erase a data from the block
    void erase(ListBlock &cur, const DataType &tmp);

    // Find some data in the block
    std::vector<int> find(ListBlock &cur, const char *key);

    // Split a block
    ListBlock split(ListBlock &cur);

    // Merge two blocks
    void merge(ListBlock &cur, ListBlock &del);

  private:
    std::fstream file;
    std::string file_name;

  private:
    std::set<int> free_blocks;
    std::vector<ListBlock> blocks;

};

} // namespace list

} // namespace bookstore
#endif
