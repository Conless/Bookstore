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
 * @brief Class KeyType
 * @details Package the char array at a size of kMaxKeyLen, enable assignment and comparison.
 */
class UnrolledLinkedList::KeyType {
  public:
    KeyType() { memset(str, 0, sizeof(str)); }
    KeyType(const char *_str) { memset(str, 0, sizeof(str)), strcpy(str, _str); }
    KeyType(const KeyType &x) { memset(str, 0, sizeof(str)), strcpy(str, x.str); }

    bool operator<(const KeyType &x) const { return strcmp(str, x.str) < 0; }
    bool operator>(const KeyType &x) const { return strcmp(str, x.str) > 0; }
    bool operator==(const KeyType &x) const { return strcmp(str, x.str) == 0; }
    bool operator!=(const KeyType &x) const { return !(*this == x); }
    bool operator<=(const KeyType &x) const { return !(*this > x); }
    bool operator>=(const KeyType &x) const { return !(*this < x); }

  public:
    char str[kMaxKeyLen];
};

/**
 * @brief Class DataType
 * @details Package the pair of key and value, enable assignment and comparison.
 */
class UnrolledLinkedList::DataType {
    friend class ListBlock;

  public:
    KeyType key;
    int value;
    DataType() : key(), value(0) {}
    DataType(KeyType _key, int _value) : key(_key), value(_value) {}
    bool operator<(const DataType &x) const { return key == x.key ? value < x.value : key < x.key; }
    bool operator>(const DataType &x) const { return key == x.key ? value > x.value : key > x.key; }
    bool operator==(const DataType &x) const { return key == x.key && value == x.value; }
    bool operator!=(const DataType &x) const { return !(*this == x); }
    bool operator<=(const DataType &x) const { return !(*this > x); }
    bool operator>=(const DataType &x) const { return !(*this < x); }
};

/**
 * @brief Class ListBlock
 * @details The type of a whole block, with fixed length kMaxBlockSize + 10. Split when the length of a block is greater than
 * kMaxBlockSize.
 */
class UnrolledLinkedList::ListBlock {
    // Can only be directly operated by ull class
    friend class UnrolledLinkedList;

  public:
    ListBlock() : data(), len(0), pos(0) {}
    ListBlock(size_t _len, int _pos) : len(_len), pos(_pos) {}
    ~ListBlock() {}

  public:
    DataType *data;
    DataType head, tail;
    size_t len;
    int pos;
};

/**
 * @brief Construct a new Unrolled Linked List:: Unrolled Linked List object
 * @details First judge whether to inherit the previous data. Then init the data.
 * @param file_name
 */
UnrolledLinkedList::UnrolledLinkedList(const std::string &_file_name) : file_name(_file_name) {
    std::filesystem::create_directory("data"); // create a new directory for data storage
    std::string log_file = "data/" + file_name + ".log";
    std::string dat_file = "data/" + file_name + ".dat";
    std::ifstream InputLog(log_file); // Open the log file to read history
    blocks.clear(); // Initialize the block system
    blocks.push_back(ListBlock()); // Insert a head block
    for (int i = 1; i <= kMaxBlockCnt; i++)
        free_blocks.insert(i);
    if (InputLog.good()) {
        file.open(dat_file);
        int T;
        InputLog >> T;
        for (int i = 1; i <= T; i++) {
            size_t _len;
            int _pos;
            InputLog >> _len >> _pos;
            blocks.push_back(ListBlock(_len, _pos));
            allocate(blocks[i]);
            blocks[i].head = blocks[i].data[0];
            blocks[i].tail = blocks[i].data[blocks[i].len - 1];
            deallocate(blocks[i]);
            free_blocks.erase(_pos);
        }
    } else {
        std::ofstream tmp(dat_file, std::ios::out | std::ios::trunc);
        tmp.close();
        file.open(dat_file);
    }
}

/**
 * @brief Destroy the Unrolled Linked List:: Unrolled Linked List object
 * @details The destructor of ull, which write the log file into the file system for next use.
 */
UnrolledLinkedList::~UnrolledLinkedList() {
    std::string log_file = "data/" + file_name + ".log";
    std::ofstream OutputLog(log_file, std::ios::out | std::ios::trunc);
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
bool UnrolledLinkedList::empty() const { return blocks.size() == 0; }

/**
 * @brief Insert a data into ull
 * @details Judge the correct block to insert the data and insert it.
 * @param key
 * @param value
 */
void UnrolledLinkedList::insert(const char *key, const int value) {
    DataType tmp(key, value);
    int len = blocks.size() - 1;
    if (!len) {
        blocks.push_back(ListBlock(0, 1));
        free_blocks.erase(1);
        insert(blocks[1], tmp);
    } else {
        int len = blocks.size() - 1;
        int pos = 0;
        for (int i = 1; i <= len; i++) {
            if (tmp <= blocks[i].tail) {
                insert(blocks[i], tmp);
                pos = i;
                break;
            }
        }
        if (!pos)
            insert(blocks[pos = len], tmp);
        if (blocks[pos].len >= kMaxBlockSize)
            blocks.insert(blocks.begin() + pos + 1, split(blocks[pos]));
    }
}

/**
 * @brief Erase a data from ull
 * @details Find which block the data is in and erase it.
 * @param key
 * @param value
 */
void UnrolledLinkedList::erase(const char *key, const int value) {
    DataType tmp(key, value);
    int len = blocks.size() - 1;
    if (!len)
        throw Exception(UNKNOWN, "Given data was not found.");
    int pos = 0;
    for (int i = 1; i <= len; i++) {
        if (tmp <= blocks[i].tail) {
            erase(blocks[i], tmp);
            pos = i;
            break;
        }
    }
    if (!pos)
        throw Exception(UNKNOWN, "Given data was not found.");
    if (!blocks[pos].len) {
        free_blocks.insert(blocks[pos].pos);
        blocks.erase(blocks.begin() + pos);
        return;
    }
    if (pos != 1 && blocks[pos].len + blocks[pos - 1].len <= kMinBlockSize) {
        merge(blocks[pos - 1], blocks[pos]);
        free_blocks.insert(blocks[pos].pos);
        blocks.erase(blocks.begin() + pos);
        return;
    }
    if (pos != len && blocks[pos].len + blocks[pos + 1].len <= kMinBlockSize) {
        merge(blocks[pos], blocks[pos + 1]);
        free_blocks.insert(blocks[pos + 1].pos);
        blocks.erase(blocks.begin() + pos + 1);
        return;
    }
    return;
}

/**
 * @brief Find the key in ull
 * @details Find all the values corresponding to the given key.
 * @param key
 * @return std::vector<int>
 */
std::vector<int> UnrolledLinkedList::find(const char *key) {
    int len = blocks.size() - 1;
    if (!len)
        return std::vector<int>();
    std::vector<int> ret;
    ret.clear();
    for (int i = 1; i <= len; i++) {
        if (blocks[i].head.key > key)
            break;
        else if (blocks[i].tail.key >= key) {
            std::vector<int> ret_tmp = find(blocks[i], key);
            ret.insert(ret.end(), ret_tmp.begin(), ret_tmp.end());
        }
    }
    return ret;
}

/**
 * @brief Get the size of the whole ull when testing
 * @details Count the size of each blocks and add them up.
 * @return size_t
 */
size_t UnrolledLinkedList::size() {
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
void UnrolledLinkedList::output(ListBlock &cur) {
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
void UnrolledLinkedList::allocate(ListBlock &cur) {
    cur.data = new DataType[kMaxBlockSize];
    file.seekg(sizeof(DataType) * kMaxBlockSize * (cur.pos - 1));
    file.read(reinterpret_cast<char *>(cur.data), sizeof(DataType) * cur.len);
}

/**
 * @brief Deallocate a block
 * @details Free the space of a block and write it to the file system.
 * @param cur
 */
void UnrolledLinkedList::deallocate(ListBlock &cur) {
    // DataType *a = new DataType;
    file.seekp(sizeof(DataType) * kMaxBlockSize * (cur.pos - 1));
    file.write(reinterpret_cast<char *>(cur.data), sizeof(DataType) * cur.len);
    delete[] cur.data;
}

/**
 * @brief Insert a data to a block
 * @details Insert a pair of key and value to the block in order. Using binary search, with total time cost O(sqrt(n))
 * @param cur
 * @param tmp
 */
void UnrolledLinkedList::insert(ListBlock &cur, const DataType &tmp) {
    allocate(cur);
    int pos = std::lower_bound(cur.data, cur.data + cur.len, tmp) - cur.data;
    if (cur.data[pos] == tmp) {
        deallocate(cur);
        throw Exception(UNKNOWN, "Given data has already been inserted.");
    }
    if (!pos)
        cur.head = tmp;
    if (pos == cur.len)
        cur.tail = tmp;
    for (int i = cur.len; i >= pos + 1; i--)
        cur.data[i] = cur.data[i - 1];
    cur.len++;
    cur.data[pos] = tmp;
    deallocate(cur);
    return;
}

/**
 * @brief Erase a data from the block
 * @details Delete a pair of key and value of the block in order. Using binary search, with total time cost O(sqrt(n))
 * @param cur
 * @param tmp
 */
void UnrolledLinkedList::erase(ListBlock &cur, const DataType &tmp) {
    allocate(cur);
    int pos = std::lower_bound(cur.data, cur.data + cur.len, tmp) - cur.data;
    if (cur.data[pos] != tmp) {
        deallocate(cur);
        throw Exception(UNKNOWN, "Given data was not found.");
    }
    if (!pos && cur.len != 1)
        cur.head = cur.data[pos + 1];
    if (pos == cur.len - 1 && cur.len != 1)
        cur.tail = cur.data[pos - 1];
    std::copy(cur.data + pos + 1, cur.data + cur.len, cur.data + pos);
    cur.len--;
    deallocate(cur);
    return;
}

/**
 * @brief Find some data in the block
 * @details Return all the corresponding values in current block in order
 * @param cur
 * @param key
 * @return std::vector<int>
 */
std::vector<int> UnrolledLinkedList::find(ListBlock &cur, const char *key) {
    allocate(cur);
    std::vector<int> ret;
    ret.clear();
    if (cur.len) {
        int pos = std::lower_bound(cur.data, cur.data + cur.len, DataType(key, 0)) - cur.data;
        for (; pos < cur.len; pos++) {
            if (cur.data[pos].key > key)
                break;
            ret.push_back(cur.data[pos].value);
        }
    }
    deallocate(cur);
    return ret;
}

/**
 * @brief Split a block
 * @details When the size of a block is larger than expected, split into two blocks by the middle.
 * @param cur
 * @return UnrolledLinkedList::ListBlock
 */
UnrolledLinkedList::ListBlock UnrolledLinkedList::split(ListBlock &cur) {
    ListBlock nex(cur.len, cur.pos);
    allocate(cur);
    allocate(nex);
    nex.len >>= 1;
    cur.len -= nex.len;
    for (int i = 0; i < nex.len; i++)
        nex.data[i] = cur.data[i + cur.len];
    cur.tail = cur.data[cur.len - 1];
    nex.head = nex.data[0];
    nex.tail = nex.data[nex.len - 1];
    deallocate(cur);
    int nex_pos = *(free_blocks.begin());
    free_blocks.erase(nex_pos);
    nex.pos = nex_pos;
    deallocate(nex);
    return nex;
}

void UnrolledLinkedList::merge(ListBlock &cur, ListBlock &del) {
    allocate(cur);
    allocate(del);
    for (int i = 0; i < del.len; i++)
        cur.data[cur.len + i] = del.data[i];
    cur.len += del.len;
    cur.tail = cur.data[cur.len - 1];
    deallocate(cur);
    deallocate(del);
    free_blocks.insert(del.pos);
}

} // namespace list
} // namespace bookstore
