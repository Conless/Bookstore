#include "UnrolledLinkedList.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include "Utils/Exception.h"

namespace bookstore {

namespace list {

UnrolledLinkedList::UnrolledLinkedList(const std::string file_name) {
    file.open(file_name, std::ios::in | std::ios::out);
    cnt = 0;
}

UnrolledLinkedList::~UnrolledLinkedList() {}

Line UnrolledLinkedList::ReadLine(DataType pos) {
    // file.open(file_path, std::ios::in);
    Line ret;
    ret.pos = pos;
    file.seekg((pos - 1) * kSizeofLine);
    KeyType str;
    file.read(str, kSizeofKey);
    ret.key = str;
    file.read(reinterpret_cast<char *>(&ret.data), kSizeofData);
    file.read(reinterpret_cast<char *>(&ret.next), kSizeofData);
    // file.close();
    return ret;
}
void UnrolledLinkedList::WriteLine(DataType pos, Line now) {
    // file.open(file_path, std::ios::out);
    file.seekp((pos - 1) * kSizeofLine);
    KeyType key_str;
    strcpy(key_str, now.key.c_str());
    file.write(key_str, kSizeofKey);
    file.write(reinterpret_cast<char *>(&now.data), kSizeofData);
    file.write(reinterpret_cast<char *>(&now.next), kSizeofData);
    // file.close();
    // strcpy(key_str, now.key.c_str());
    // file.write(key_str, kSizeofKey);
    // file.write(reinterpret_cast<char *>(&now.data), kSizeofData);
    // file.write(reinterpret_cast<char *>(&now.next), kSizeofData);
}
DataType UnrolledLinkedList::InsertData(DataType pos, const std::string key, DataType num, DataType data) {
    siz[pos]++;
    Line now = ReadLine(head[pos]);
    if (key < now.key || (key == now.key && data < now.data)) {
        head[pos] = num;
        return now.pos;
    }
    while (true) {
        DataType nex_pos = now.next;
        if (nex_pos == 0) {
            tail[pos] = num;
            now.next = num;
            WriteLine(now.pos, now);
            return 0;
        }
        Line nex = ReadLine(nex_pos);
        if (key < nex.key || (key == nex.key && data < nex.data)) {
            now.next = num;
            WriteLine(now.pos, now);
            return nex_pos;
        }
        now = nex;
    }
}
void UnrolledLinkedList::Simplify() {
    DataType len = head.size();
    for (DataType i = 0; i < len; i++) {
        if (siz[i] >= max_list_size * 2) {
            Line now = ReadLine(head[i]), las;
            for (DataType j = 1; j < max_list_size; j++)
                now = ReadLine(now.next);
            tail.insert(tail.begin() + i + 1, tail[i]);
            tail[i] = now.pos;
            DataType tmp = now.next;
            now.next = 0;
            WriteLine(now.pos, now);
            now = ReadLine(tmp);
            head.insert(head.begin() + i + 1, now.pos);
            siz.insert(siz.begin() + i + 1, siz[i] - max_list_size);
            siz[i] -= max_list_size;
        } else if (i < len - 1) {
            if (siz[i] + siz[i + 1] <= max_list_size) {
                Line now = ReadLine(tail[i]);
                now.next = head[i + 1];
                WriteLine(now.pos, now);
                siz[i] += siz[i + 1];
                tail[i] = tail[i + 1];
                siz.erase(siz.begin() + i + 1);
                head.erase(siz.begin() + 1);
                tail.erase(tail.begin() + 1);
            }
        }
    }
}
void UnrolledLinkedList::Output() {
    DataType len = head.size();
    for (DataType i = 0; i < len; i++) {
        std::cout << "Block " << i << '\n';
        DataType pos = head[i];
        while (pos) {
            Line now = ReadLine(pos);
            std::cout << now.key << ' ' << now.pos << ' ' << now.data << ' ' << now.next << '\n';
            pos = now.next;
        }
        std::cout << '\n';
    }
}
void UnrolledLinkedList::insert(const std::string key, DataType data) {
    cnt++;
    if (cnt == 1) {
        head.push_back(cnt);
        tail.push_back(cnt);
        siz.push_back(1);
        WriteLine(cnt, Line(key, cnt, data));
    } else {
        DataType len = head.size();
        Line now = ReadLine(head[0]);
        for (DataType i = 0; i < len; i++) {
            if (i == len - 1) {
                DataType ret_pos = InsertData(i, key, cnt, data);
                WriteLine(cnt, Line(key, cnt, data, ret_pos));
                break;
            }
            DataType nex_pos = head[i + 1];
            Line nex = ReadLine(nex_pos);
            if (key < nex.key || (key == nex.key && data < nex.data)) {
                DataType ret_pos = InsertData(i, key, cnt, data);
                WriteLine(cnt, Line(key, cnt, data, ret_pos));
                break;
            }
            now = nex;
        }
        Simplify();
    }
    // Output();
}
std::vector<DataType> UnrolledLinkedList::find(const std::string key) {
    std::vector<DataType> ret;
    if (!cnt)
        return ret;
    DataType len = head.size();
    for (DataType i = 0; i < len; i++) {
        Line now = ReadLine(head[i]);
        if (now.key > key)
            return ret;
        Line tai = ReadLine(tail[i]);
        if (tai.key >= key) {
            while (true) {
                if (now.key == key)
                    ret.push_back(now.data);
                else if (now.key > key)
                    return ret;
                if (!now.next)
                    break;
                now = ReadLine(now.next);
            }
        }
    }
    return ret;
}
void UnrolledLinkedList::erase(const std::string key, DataType data) {
    if (!cnt)
        throw Exception(UNKNOWN, "Not found such data.");
    DataType len = head.size();
    for (DataType i = 0; i < len; i++) {
        Line now = ReadLine(head[i]);
        if (now.key > key)
            break;
        cnt--;
        Line tai = ReadLine(tail[i]);
        bool flag = 0;
        if (tai.key >= key) {
            Line las;
            while (true) {
                if (now.key == key && now.data == data) {
                    siz[i]--;
                    if (now.pos == head[i] && now.pos == tail[i]) {
                        head.erase(head.begin() + i);
                        tail.erase(tail.begin() + i);
                        siz.erase(siz.begin() + i);
                    } else if (now.pos == head[i]) {
                        head[i] = now.next;
                    } else if (now.pos == tail[i]) {
                        tail[i] = las.pos;
                        las.next = 0;
                        WriteLine(las.pos, las);
                    } else {
                        las.next = now.next;
                        WriteLine(las.pos, las);
                    }
                    now.data = -1;
                    WriteLine(now.pos, now);
                } else if (now.key > key) {
                    flag = 1;
                    break;
                }
                if (!now.next)
                    break;
                las = now;
                now = ReadLine(now.next);
            }
        }
        if (flag)
            break;
    }
    Simplify();
    // Output();
}

} // namespace list

} // namespace bookstore
