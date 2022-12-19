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
#include <cstring>
#include <filesystem>
#include <iostream>

#include "Utils/Exception.h"

namespace bookstore {

namespace list {

/**
 * @brief Construct a new Unrolled Linked List:: Unrolled Linked List object
 * @details First judge whether to inherit the previous data. Then init the
 * data.
 * @param file_name
 */
template <size_t kMaxKeyLen>
UnrolledLinkedList<kMaxKeyLen>::UnrolledLinkedList(
    const std::string &_file_name)
    : file_name(_file_name) {
    std::filesystem::create_directory(
        "data"); // create a new directory for data storage
    std::string log_file = "data/" + file_name + ".log";
    std::string dat_file = "data/" + file_name + ".dat";
    std::ifstream InputLog(log_file);
    blocks.clear();                            // Initialize the block system
    blocks.push_back(ListBlock<kMaxKeyLen>()); // Insert a head block
    for (int i = 1; i <= kMaxBlockCnt; i++)
        free_blocks.insert(i); // Initialize the free_blocks set
    if (InputLog.good()) {     // Found the history log
        file.open(dat_file);
        int T;
        InputLog >> T;
        for (int i = 1; i <= T; i++) {
            size_t _len;
            int _pos;
            InputLog >> _len >> _pos;
            blocks.push_back(ListBlock<kMaxKeyLen>(_len, _pos));
            allocate(blocks[i]);
            blocks[i].head = blocks[i].data[0];
            blocks[i].tail = blocks[i].data[blocks[i].len - 1];
            deallocate(blocks[i]);
            free_blocks.erase(_pos);
        }
    } else { // Create a new data file
        std::ofstream tmp(dat_file, std::ios::out);
        tmp.close();
        file.open(dat_file);
    }
}

/**
 * @brief Destroy the Unrolled Linked List:: Unrolled Linked List object
 * @details The destructor of ull, which write the log file into the file system
 * for next use.
 */
template <size_t kMaxKeyLen>
UnrolledLinkedList<kMaxKeyLen>::~UnrolledLinkedList() {
    std::string log_file = "data/" + file_name + ".log";
    std::ofstream OutputLog(
        log_file,
        std::ios::out); // Write the log into file system
    int len = blocks.size() - 1;
    OutputLog << len << '\n';
    for (int i = 1; i <= len; i++)
        OutputLog << blocks[i].len << ' ' << blocks[i].pos << '\n';
    OutputLog.close();
}

/**
 * @brief Judge whether the ull is empty
 * @return true when empty
 * @return false when not empty
 */
template <size_t kMaxKeyLen>
bool UnrolledLinkedList<kMaxKeyLen>::empty() const {
    return blocks.size() == 0;
}

/**
 * @brief Insert a data into ull
 * @details Judge the correct block to insert the data and insert it.
 * @param key
 * @param value
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::insert(const KeyType<kMaxKeyLen> &key,
                                            const int value) {
    DataType tmp(key, value);
    int len = blocks.size() - 1;
    if (!len) { // Insert the first data
        blocks.push_back(ListBlock<kMaxKeyLen>(0, 1));
        free_blocks.erase(1);
        insert(blocks[1], tmp);
    } else {
        int len = blocks.size() - 1;
        int pos = 0;
        for (int i = 1; i <= len; i++) {
            if (tmp <= blocks[i].tail) { // Find the block to insert into
                insert(blocks[i], tmp);
                pos = i;
                break;
            }
        }
        if (!pos) // Insert the data into the last block
            insert(blocks[pos = len], tmp);
        if (blocks[pos].len >= kMaxBlockSize) // Larger than the maximum size
            blocks.insert(blocks.begin() + pos + 1, split(blocks[pos]));
    }
}

/**
 * @brief Erase a data from ull
 * @details Find which block the data is in and erase it.
 * @param key
 * @param value
 */
template <size_t kMaxKeyLen>
int UnrolledLinkedList<kMaxKeyLen>::erase(const KeyType<kMaxKeyLen> &key,
                                          const int value) {
    DataType tmp(key, value);
    int len = blocks.size() - 1, val;
    if (!len)
        throw NormalException(ULL_ERASE_NOT_FOUND);
    int pos = 0;
    for (int i = 1; i <= len; i++) {
        if (tmp <= blocks[i].tail) { // Found the block to erase from
            val = erase(blocks[i], tmp);
            pos = i;
            break;
        }
    }
    if (!pos) // Not found given data
        throw NormalException(ULL_ERASE_NOT_FOUND);
    if (!blocks[pos].len) { // The block becomes empty
        free_blocks.insert(blocks[pos].pos);
        blocks.erase(blocks.begin() + pos);
        return val;
    }
    merge_try(pos);
    return val;
}

/**
 * @brief Find the key in ull
 * @details Find all the values corresponding to the given key.
 * @param key
 * @return std::vector<int> (the corresponding values)
 */
template <size_t kMaxKeyLen>
std::vector<int>
UnrolledLinkedList<kMaxKeyLen>::find(const KeyType<kMaxKeyLen> &key) {
    int len = blocks.size() - 1;
    if (!len) // return an empty vector
        return std::vector<int>();
    std::vector<int> ret;
    ret.clear();
    for (int i = 1; i <= len; i++) {
        if (blocks[i].head.key >
            key) // the minimum key of the current block is already too large
            break;
        else if (blocks[i].tail.key >= key) {
            std::vector<int> ret_tmp = find(blocks[i], key);
            ret.insert(ret.end(), ret_tmp.begin(),
                       ret_tmp.end()); // connect the return vector to the end
        }
    }
    return ret;
}

/**
 * @brief Get the size of the whole ull when testing
 * @details Count the size of each blocks and add them up.
 * @return size_t (the size of the ull)
 */
template <size_t kMaxKeyLen> size_t UnrolledLinkedList<kMaxKeyLen>::size() {
    size_t ret = 0;
    for (const auto &cur : blocks)
        ret += cur.len;
    return ret;
}

/**
 * @brief Output the data of a block when testing
 * @details Output all the data of a block. Only used when debugging.
 * @param cur
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::output(ListBlock<kMaxKeyLen> &cur) {
    allocate(cur);
    for (int i = 0; i < cur.len; i++)
        std::cout << cur.data[i].key.str << " " << cur.data[i].value << '\n';
    deallocate(cur);
}

/**
 * @brief Allocate a block
 * @details Register the space of a block and read it from the file system.
 * @param cur
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::allocate(ListBlock<kMaxKeyLen> &cur) {
    cur.data = new DataType<kMaxKeyLen>[kMaxBlockSize]; // register the space
    file.seekg(sizeof(DataType<kMaxKeyLen>) * kMaxBlockSize *
               (cur.pos - 1)); // set the position to read at
    file.read(reinterpret_cast<char *>(cur.data),
              sizeof(DataType<kMaxKeyLen>) * cur.len); // read the data
}

/**
 * @brief Deallocate a block
 * @details Free the space of a block and write it to the file system.
 * @param cur
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::deallocate(ListBlock<kMaxKeyLen> &cur) {
    file.seekp(sizeof(DataType<kMaxKeyLen>) * kMaxBlockSize *
               (cur.pos - 1)); // set the position to write at
    file.write(reinterpret_cast<char *>(cur.data),
               sizeof(DataType<kMaxKeyLen>) * cur.len); // write the data
    delete[] cur.data;                                  // release the space
}
template <size_t kMaxKeyLen>
bool UnrolledLinkedList<kMaxKeyLen>::is_same(const DataType<kMaxKeyLen> &data,
                                             const DataType<kMaxKeyLen> &tmp) {
    return data.key == tmp.key && data.value == tmp.value;
}

/**
 * @brief Insert a data to a block
 * @details Insert a pair of key and value to the block in order. Using binary
 * search, with total time cost O(sqrt(n))
 * @param cur
 * @param tmp
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::insert(ListBlock<kMaxKeyLen> &cur,
                                            const DataType<kMaxKeyLen> &tmp) {
    allocate(cur);  // allocate the current block
    if (!cur.len) { // first node of the block
        cur.data[0] = cur.head = cur.tail = tmp;
        cur.len++;
        deallocate(cur);
        return;
    }
    int pos = std::lower_bound(cur.data, cur.data + cur.len, tmp) - cur.data;
    if (is_same(cur.data[pos], tmp) ||
        (pos &&
         is_same(cur.data[pos - 1], tmp))) { // the data has been inserted
        deallocate(cur);
        throw NormalException(ULL_INSERTED);
    }
    if (!pos) // update the info of head and tail
        cur.head = tmp;
    if (pos == cur.len)
        cur.tail = tmp;
    for (int i = cur.len; i >= pos + 1; i--) // move the data
        cur.data[i] = cur.data[i - 1];
    cur.len++;
    cur.data[pos] = tmp;
    deallocate(cur); // Deallocate the current block
    return;
}

/**
 * @brief Erase a data from the block
 * @details Delete a pair of key and value of the block in order. Using binary
 * search, with total time cost O(sqrt(n))
 * @param cur
 * @param tmp
 * @return int (the pos of data)
 */
template <size_t kMaxKeyLen>
int UnrolledLinkedList<kMaxKeyLen>::erase(ListBlock<kMaxKeyLen> &cur,
                                          const DataType<kMaxKeyLen> &tmp) {
    allocate(cur); // allocate the current block
    int pos = std::lower_bound(cur.data, cur.data + cur.len, tmp) - cur.data;
    int value = tmp.value;
    if (!is_same(cur.data[pos], tmp)) {
        deallocate(cur);
        throw NormalException(ULL_ERASE_NOT_FOUND);
    }
    if (!pos && cur.len != 1) // update the info of head and tail
        cur.head = cur.data[pos + 1];
    if (pos == cur.len - 1 && cur.len != 1)
        cur.tail = cur.data[pos - 1];
    cur.len--;
    for (int i = pos; i < cur.len; i++) // move the data
        cur.data[i] = cur.data[i + 1];
    deallocate(cur); // deallocate the current block
    return value;
}

/**
 * @brief Find some data in the block
 * @details Return all the corresponding values in current block in order
 * @param cur
 * @param key
 * @return std::vector<int> (the corresponding values)
 */
template <size_t kMaxKeyLen>
std::vector<int>
UnrolledLinkedList<kMaxKeyLen>::find(ListBlock<kMaxKeyLen> &cur,
                                     const KeyType<kMaxKeyLen> &key) {
    allocate(cur); // allocate the current block
    std::vector<int> ret;
    ret.clear();
    int pos = std::lower_bound(cur.data, cur.data + cur.len,
                               DataType<kMaxKeyLen>(key, 0)) -
              cur.data;
    for (; pos < cur.len; pos++) {
        if (cur.data[pos].key > key) // has finished the search
            break;
        ret.push_back(cur.data[pos].value);
    }
    deallocate(cur); // deallocate the current block
    return ret;
}

/**
 * @brief Split a block
 * @details When the size of a block is larger than expected, split into two
 * blocks by the middle.
 * @param cur
 * @return UnrolledLinkedList<kMaxKeyLen>::ListBlock (the info of the next
 * block)
 */
template <size_t kMaxKeyLen>
ListBlock<kMaxKeyLen>
UnrolledLinkedList<kMaxKeyLen>::split(ListBlock<kMaxKeyLen> &cur) {
    ListBlock<kMaxKeyLen> nex(cur.len, cur.pos);
    allocate(cur); // allocate the current block
    allocate(nex); // allocate the next block
    nex.len >>= 1; // the length of the next block
    cur.len -= nex.len;
    for (int i = 0; i < nex.len; i++) // move the data
        nex.data[i] = cur.data[i + cur.len];
    cur.tail = cur.data[cur.len - 1];
    nex.head = nex.data[0];
    nex.tail = nex.data[nex.len - 1];
    deallocate(cur); // deallocate the current block
    int nex_pos = *(free_blocks.begin());
    free_blocks.erase(nex_pos);
    nex.pos = nex_pos;
    deallocate(nex); // deallocate the next block
    return nex;
}
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::merge_try(int pos) {
    if (pos != 1 && blocks[pos].len + blocks[pos - 1].len <=
                        kMinBlockSize) { // Less than the minimum size, merge
                                         // with the previous
        merge(blocks[pos - 1], blocks[pos]);
        free_blocks.insert(blocks[pos].pos);
        blocks.erase(blocks.begin() + pos);
        return;
    }
    if (pos != blocks.size() - 1 &&
        blocks[pos].len + blocks[pos + 1].len <=
            kMinBlockSize) { // Less than the minimum size, merge with the next
        merge(blocks[pos], blocks[pos + 1]);
        free_blocks.insert(blocks[pos + 1].pos);
        blocks.erase(blocks.begin() + pos + 1);
        return;
    }
}

/**
 * @brief Merge two blocks
 * @details When the sum of the size of two blocks is less than expected, merge
 * them into a single block.
 * @param cur
 * @param del
 */
template <size_t kMaxKeyLen>
void UnrolledLinkedList<kMaxKeyLen>::merge(ListBlock<kMaxKeyLen> &cur, ListBlock<kMaxKeyLen> &del) {
    allocate(cur); // allocate the current block
    allocate(del); // allocate the block to be deleted
    for (int i = 0; i < del.len; i++)
        cur.data[cur.len + i] = del.data[i];
    cur.len += del.len;
    cur.tail = cur.data[cur.len - 1];
    deallocate(cur);             // deallocate the current block
    deallocate(del);             // deallocate the block to be deleted
    free_blocks.insert(del.pos); // free the block
}
template <size_t kMaxKeyLen>
int UnrolledLinkedListUnique<kMaxKeyLen>::erase(const KeyType<kMaxKeyLen> &key) {
    return UnrolledLinkedList<kMaxKeyLen>::erase(key, 0);
}
template <size_t kMaxKeyLen>
int UnrolledLinkedListUnique<kMaxKeyLen>::find(const KeyType<kMaxKeyLen> &key) {
    std::vector<int> ret = UnrolledLinkedList<kMaxKeyLen>::find(key);
    if (ret.empty())
        throw NormalException(ULL_NOT_FOUND);
    if (ret.size() >= 2)
        throw NormalException(ULL_DUPLICATED);
    return ret[0];
}
template <size_t kMaxKeyLen>
bool UnrolledLinkedListUnique<kMaxKeyLen>::is_same(
    const DataType<kMaxKeyLen> &data,
    const DataType<kMaxKeyLen> &tmp) {
    return data.key == tmp.key;
}

} // namespace list
} // namespace bookstore
