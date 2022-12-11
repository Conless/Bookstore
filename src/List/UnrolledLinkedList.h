/**
 * @file UnrolledLinkedList.h
 * @author Conless Pan (conlesspan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BOOKSTORE_LIST_ULL_H
#define BOOKSTORE_LIST_ULL_H

#include <fstream>
#include <string>
#include <vector>

namespace bookstore {

namespace list {

/**
 * @brief Class UnrolledLinkedList
 * @details The main type of file storage system
 */
class UnrolledLinkedList {
  private:
    // The type of key
    typedef char KeyType[72];

    // The type of data
    typedef int DataType;

    // The type of index
    typedef unsigned int IndexType;

    // The size of those types
    const size_t kSizeofKey = sizeof(KeyType);
    const size_t kSizeofData = sizeof(DataType);
    const size_t kSizeofIndex = sizeof(IndexType);
    const size_t kSizeofNode = kSizeofKey + kSizeofData + kSizeofIndex;

  private:
    /**
     * @brief Structure type Node
     * @details Used to record all the data in a node of ull. Similar to struct node in traditional linkedlist.
     */
    struct Node {
        // The key of this node
        std::string key;
        // The pos of this node, i.e. the place it is located on in file_name.bin
        IndexType pos;
        // The data of this node
        DataType data;
        // The next "pointer" of this node, i.e. the pos of its next node.
        IndexType next;

        // Constructor of Node
        Node() = default;
        // Initializer of Node
        Node(std::string key, IndexType pos, DataType data, IndexType next = 0) // Initializer for Node
            : key(key), pos(pos), data(data), next(next) {}
    };

  private:
    // The maximum size of a single list
    const DataType max_block_size;

    // The head, tail "pointer" of each block
    std::vector<IndexType> head, tail;

    // The size of each block
    std::vector<IndexType> siz;

    // The file name
    std::string file_name;

    // The total number of data, not included the deleted ones
    DataType cnt;

    // The file I/O variable
    std::fstream file;

  public:
    // Constructor of ull
    UnrolledLinkedList(const std::string file_path, const bool inherit_tag = false, const IndexType block_size = 1000);

    // Destructor of ull
    ~UnrolledLinkedList();

  private:
    // Read a node in file_name.bin
    Node ReadNode(IndexType pos);

    // Write or rewrite a node in file_name.bin
    void WriteNode(IndexType pos, Node now);

    // Insert a node in the selected block
    IndexType InsertData(IndexType pos, const std::string key, IndexType num, DataType data);

    // Simplify the ull
    void Simplify();

    // Output the current data of ull
    void Output();

  public:
    // Insert a pair of key and data
    void insert(const std::string key, DataType data);

    // Find a vector of data by the given key
    std::vector<DataType> find(const std::string key);

    // Erase a pair of key and data
    void erase(const std::string key, DataType data);
};

} // namespace list
} // namespace bookstore

#endif
