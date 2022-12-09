#include "UnrolledLinkedList.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace bookstore {

namespace list {

UnrolledLinkedList::UnrolledLinkedList(const std::string file_name) {
    file_path = file_name;
    cnt = 0;
}

UnrolledLinkedList::~UnrolledLinkedList() {}

Line UnrolledLinkedList::ReadLine(int pos) {
    Line ret;
    std::ifstream fin;
    fin.open(file_path, std::ios::in);
    fin.seekg(pos * kSizeOfLine);
    KeyType str;
    fin.read(str, kSizeOfKey);
    ret.key = str;
    fin.read(reinterpret_cast<char*>(ret.data), kSizeOfData);
    fin.read(reinterpret_cast<char *>(ret.next), kSizeOfData);
    fin.close();
    return ret;
}
void UnrolledLinkedList::insert(const std::string key, DataType data) {
    KeyType key_str;
    strcpy(key_str, key.c_str());
    std::ofstream fout;
    fout.open(file_path, std::ios::out | std::ios::ate);
    fout.seekp(cnt * kSizeOfLine);
    fout.write(key_str, kSizeOfKey);
    fout.write(reinterpret_cast<char *>(&data), kSizeOfData);
    int next = -1;
    if (!cnt) {
        fout.write(reinterpret_cast<char *>(&next), kSizeOfData);
        head.push_back(cnt);
        tail.push_back(cnt);
    } else {
        int siz = head.size();
        for (int i = 0; i < siz; i++) {
            if (i == siz - 1)
                
        }
    }
    cnt++;
    return;
}

} // namespace list

} // namespace bookstore
