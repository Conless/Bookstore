/**
 * @file UnrolledLinkedList.cc
 * @author Conless Pan (conlesspan@outlook.com)
 * @brief The implementation for UnrolledLinkedList.h
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "UnrolledLinkedList.h"

#include <cstring>
#include <iostream>

// Use to deal with exceptions
#include "Utils/Exception.h"

namespace bookstore {

namespace list {

/**
 * @brief Construct a new Unrolled Linked List:: Unrolled Linked List object
 * @details Create a new ull, or inherit the data from the last test point
 * @param file_path
 * @param inherit_tag
 * @param block_size
 */
UnrolledLinkedList::UnrolledLinkedList(const std::string file_path, const bool inherit_tag, const IndexType block_size)
    : file_name(file_path), max_block_size(block_size) {
    // The file_name.bin is used to storage all key and data, written in binary text. Here use it to determine whether to
    // inherit data from former test points
    std::ifstream input(file_name + ".bin");

    // Initialize and clear
    cnt = 0;
    head.clear();
    tail.clear();
    siz.clear();

    if (inherit_tag && input.good()) { // If the program should inherit data
        // The file_name.dat is used to storage key data which was saved in RAM, i.e. cnt, head, tail and siz. So here the
        // program first read the key data of the last ull
        input.close();
        input.open(file_name + ".dat");

        // Inputing...
        IndexType len; // The number of blocks, similarly hereafter
        input >> cnt >> len;
        while (len--) {
            IndexType head_num, tail_num, siz_num;
            input >> head_num >> tail_num >> siz_num;
            head.push_back(head_num);
            tail.push_back(tail_num);
            siz.push_back(siz_num);
        }
    } else { // Create a new file_name.bin and reset it as a clear file
        std::ofstream create(file_name + ".bin", std::ios::out | std::ios::trunc);
        create.close();
    }

    // Open the binary data file
    file.open(file_name + ".bin", std::ios::in | std::ios::out);

    return;
}

/**
 * @brief Destroy the Unrolled Linked List:: Unrolled Linked List object
 * @details Destory a ull, and output its key data for reuse
 */
UnrolledLinkedList::~UnrolledLinkedList() {
    // The file_name.dat is used to storage key data which was saved in RAM, i.e. cnt, head, tail and siz. Here the program
    // record them in normal text mode
    std::ofstream output(file_name + ".dat", std::ios::out | std::ios::trunc);
    // Outputing...
    IndexType len = head.size();
    output << cnt << " " << len << '\n';
    for (IndexType i = 0; i < len; i++)
        output << head[i] << ' ' << tail[i] << ' ' << siz[i] << '\n';
    output.close();
    return;
}

/**
 * @brief Read a node in file_name.bin
 * @details Read the key of KeyType(std::string), pos of IndexType(uint), data of DataType(int) and next of IndexType(uint) in
 * the binary file
 * @param pos
 * @return Node
 */
UnrolledLinkedList::Node UnrolledLinkedList::ReadNode(IndexType pos) {
    Node ret;
    ret.pos = pos;
    // Move the read head, (pos - 1) suggests that the selected data is located at the (pos - 1)th node of binary file
    file.seekg((pos - 1) * kSizeofNode);

    // Inputing...
    KeyType str;
    file.read(str, kSizeofKey);
    ret.key = str;
    file.read(reinterpret_cast<char *>(&ret.data), kSizeofData);
    file.read(reinterpret_cast<char *>(&ret.next), kSizeofIndex);
    return ret;
}

/**
 * @brief Write or rewrite a node in file_name.bin
 * @details Write the key of KeyType(std::string), pos of IndexType(uint), data of DataType(int) and next of IndexType(uint) in
 * the binary file
 * @param pos
 * @param now
 */
void UnrolledLinkedList::WriteNode(IndexType pos, Node now) {
    // Move the write head, (pos - 1) suggests that the selected data is located at the (pos - 1)th node of binary file
    file.seekp((pos - 1) * kSizeofNode);

    // Outputing...
    KeyType key_str;
    strcpy(key_str, now.key.c_str());
    file.write(key_str, kSizeofKey);
    file.write(reinterpret_cast<char *>(&now.data), kSizeofData);
    file.write(reinterpret_cast<char *>(&now.next), kSizeofIndex);
    return;
}

/**
 * @brief Insert a node in the selected block
 * @details Insert a new node in the selected block in order
 * @param pos
 * @param key
 * @param num
 * @param data
 * @return UnrolledLinkedList::IndexType
 */
UnrolledLinkedList::IndexType UnrolledLinkedList::InsertData(IndexType pos, const std::string key, IndexType num,
                                                             DataType data) {
    // Increase the size of the current block
    siz[pos]++;

    // Read the data of the head node of the current block
    Node now = ReadNode(head[pos]);
    if (key < now.key || (key == now.key && data < now.data)) {
        head[pos] = num;
        return now.pos;
    }

    // Search the node in the block one by one
    while (true) {
        // Get the pos of the next
        IndexType nex_pos = now.next;

        if (!nex_pos) { // If next is null, i.e. we've arrived to the tail, then just insert the node here
            tail[pos] = num;
            now.next = num;
            WriteNode(now.pos, now);
            return 0;
        }

        Node nex = ReadNode(nex_pos); // Or determine whether the node can be inserted between
        if (key < nex.key || (key == nex.key && data < nex.data)) {
            now.next = num;
            WriteNode(now.pos, now);
            return nex_pos;
        }

        // Move to the next node
        now = nex;
    }
}

/**
 * @brief Simplify the ull
 * @details Simplify a ull in two following ways. First, find if there're some large blocks and divide them. Then, find if
 * there're some consecutive small blocks and merge them.
 */
void UnrolledLinkedList::Simplify() {
    IndexType len = head.size();
    for (IndexType i = 0; i < len; i++) {
        if (siz[i] >= max_block_size * 2) { // If we find a large block, divide it from the mid
            // Start from the head node
            Node now = ReadNode(head[i]), las;
            for (IndexType j = 1; j < max_block_size; j++)
                now = ReadNode(now.next);
            // Here now := the last node of the first block, with max_block_size
            tail.insert(tail.begin() + i + 1, tail[i]);
            tail[i] = now.pos;
            IndexType tmp = now.next;
            now.next = 0;
            // Rewrite the tail node
            WriteNode(now.pos, now);

            // Get the data of the head node of the new block
            now = ReadNode(tmp);
            head.insert(head.begin() + i + 1, now.pos);
            siz.insert(siz.begin() + i + 1, siz[i] - max_block_size);
            siz[i] -= max_block_size;
        } else if (i < len - 1) {
            if (siz[i] + siz[i + 1] <= max_block_size) { // If we find a small block, which, can be merged with the next block
                // Read the data of the tail
                Node now = ReadNode(tail[i]);
                // Connext it with the head of the next block
                now.next = head[i + 1];
                WriteNode(now.pos, now);
                // Edit the data
                siz[i] += siz[i + 1];
                tail[i] = tail[i + 1];
                siz.erase(siz.begin() + i + 1);
                head.erase(siz.begin() + 1);
                tail.erase(tail.begin() + 1);
            }
        }
    }
}

/**
 * @brief Output the current data of ull
 *
 */
void UnrolledLinkedList::Output() {
    IndexType len = head.size();
    for (IndexType i = 0; i < len; i++) {
        std::cout << "Block " << i << '\n';
        IndexType pos = head[i];
        while (pos) {
            Node now = ReadNode(pos);
            std::cout << now.key << ' ' << now.pos << ' ' << now.data << ' ' << now.next << '\n';
            pos = now.next;
        }
        std::cout << '\n';
    }
}

/**
 * @brief Insert a pair of key and data
 * @details Insert a pair in order into the ull and maintain the size of ull
 * @param key
 * @param data
 */
void UnrolledLinkedList::insert(const std::string key, DataType data) {
    // Increase the count of current node
    cnt++;
    if (cnt == 1) { // If it is the first node
        head.push_back(cnt);
        tail.push_back(cnt);
        siz.push_back(1);
        WriteNode(cnt, Node(key, cnt, data));
    } else { // Find a correct place to insert
        IndexType len = head.size();

        for (IndexType i = 0; i < len; i++) {
            // If it is the last block, we have to insert it
            if (i == len - 1) {
                IndexType ret_pos = InsertData(i, key, cnt, data);
                WriteNode(cnt, Node(key, cnt, data, ret_pos));
                break;
            }

            // Or else, insert it in the first block such that the head of the next block is greater than it
            Node nex = ReadNode(head[i + 1]);
            if (key < nex.key || (key == nex.key && data < nex.data)) {
                IndexType ret_pos = InsertData(i, key, cnt, data);
                WriteNode(cnt, Node(key, cnt, data, ret_pos));
                break;
            }
        }
    }
    Simplify();
    // Output();
}

/**
 * @brief Find a vector of data by the given key
 * @details Find all of the data corresponding the given key, in the sort of the second keyword
 * @param key 
 * @return std::vector<UnrolledLinkedList::DataType> 
 */
std::vector<UnrolledLinkedList::DataType> UnrolledLinkedList::find(const std::string key) {
    std::vector<DataType> ret;
    ret.clear();

    // If empty, directly return the empty vector
    if (!cnt)
        return ret;

    IndexType len = head.size();
    for (IndexType i = 0; i < len; i++) {
        // Search in the i-th block (0-base)
        Node now = ReadNode(head[i]);
        // If the min data is even greater than the key
        if (now.key > key)
            return ret;

        // Determine whether the data can be found in the current block
        Node tai = ReadNode(tail[i]);
        if (tai.key >= key) {   // If possible
            while (true) {
                if (now.key == key) // Found
                    ret.push_back(now.data);
                else if (now.key > key) // Impossible then
                    return ret;
                if (!now.next) // Tail
                    break;
                now = ReadNode(now.next);
            }
        }
    }
    return ret;
}

/**
 * @brief Erase a pair of key and data
 * @details Erase a pair of given key and data, throw error when not found. Maintaining the size of the block.
 * @param key 
 * @param data 
 */
void UnrolledLinkedList::erase(const std::string key, DataType data) {
    // If empty, then the data cannot be found
    if (!cnt)
        throw Exception(UNKNOWN, "Not found.");
    
    IndexType len = head.size();
    for (IndexType i = 0; i < len; i++) {
        // Search in the i-th block (0-base)
        Node now = ReadNode(head[i]);
        if (now.key > key)
            throw Exception(UNKNOWN, "Not found.");
        Node tai = ReadNode(tail[i]);
        if (tai.key >= key) {
            Node las;
            while (true) {
                if (now.key == key && now.data == data) { // Found
                    cnt--;
                    siz[i]--;
                    if (now.pos == head[i] && now.pos == tail[i]) { // The only node in the block
                        head.erase(head.begin() + i);
                        tail.erase(tail.begin() + i);
                        siz.erase(siz.begin() + i);
                    } else if (now.pos == head[i]) {  // Head node of the block
                        head[i] = now.next;
                    } else if (now.pos == tail[i]) {  // Tail node of the block
                        tail[i] = las.pos;
                        las.next = 0;
                        WriteNode(las.pos, las);
                    } else {  // Otherwise
                        las.next = now.next;
                        WriteNode(las.pos, las);
                    }
                    now.data = -1;  // A tag of being "erased", though not used
                    WriteNode(now.pos, now);
                    Simplify();
                    return;
                } else if (now.key > key) {
                    throw Exception(UNKNOWN, "Not found.");
                }
                if (!now.next)
                    break;
                las = now;
                now = ReadNode(now.next);
            }
        }
    }
    throw Exception(UNKNOWN, "Not found.");
}

} // namespace list

} // namespace bookstore
