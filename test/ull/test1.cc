#include "List/UnrolledLinkedList.cc"
#include "List/UnrolledLinkedList.h"

#include <bits/stdc++.h>

using namespace std;

namespace bookstore {

namespace list {

class ULLTst : public UnrolledLinkedList {
  public:
    ULLTst(const char *file_name) : UnrolledLinkedList(file_name) {}
    void test1() {
        ListBlock a, b;
        file.seekp(0);
        a.data = new DataType[1];
        strcpy(a.data[0].key.str, "a");
        puts(a.data[0].key.str);
        deallocate(a);
        allocate(b);
        puts(b.data[0].key.str);
    }

    void test2() {
        // char str[kMaxKeyLen];
        // int data;
        // ListBlock a;
        // int T;
        // std::cin >> T;
        // a.read(file);
        // while (T--) {
        //     int opt;
        //     std::cin >> opt;
        //     if (opt == 0) {
        //         std::cin >> str >> data;
        //         DataType tmp(str, data);
        //         a.insert(tmp);
        //     } else if (opt == 1) {
        //         std::cin >> str >> data;
        //         DataType tmp(str, data);
        //         a.erase(tmp);
        //     } else {
        //         a.output();
        //     }
        // }
    }

    void test3() {
        char str[kMaxKeyLen];
        int data;
        int T;
        cin >> T;
        while (T--) {
            string opt;
            std::cin >> opt;
            try {
                if (opt == "insert") {
                    std::cin >> str >> data;
                    insert(str, data);
                } else if (opt == "delete") {
                    std::cin >> str >> data;
                    erase(str, data);
                } else if (opt == "find") {
                    std::cin >> str;
                    std::vector<int> ret = find(str);
                    if (!ret.size())
                        std::cout << "null\n";
                    else {
                        for (const auto &num : ret)
                            std::cout << num << ' ';
                        std::cout << '\n';
                    }
                }
                // output(blocks[1]);
                // std::cout << '\n';
            } catch (const Exception &x) {
            }
        }
    }
};

} // namespace list

} // namespace bookstore

int main() {
    bookstore::list::ULLTst a("test");
    a.test3();
    return 0;
}