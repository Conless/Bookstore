#include <iostream>

#include "List/UnrolledLinkedList.h"

int main() {
    bookstore::list::UnrolledLinkedList l("test.dat");
    int T;
    std::cin >> T;
    while (T--) {
        std::string opt;
        std::cin >> opt;
        if (opt == "insert") {
            std::string s;
            int data;
            std::cin >> s >> data;
            l.insert(s, data);
        } else if (opt == "find") {
            std::string s;
            std::cin >> s;
            std::vector<bookstore::list::DataType> ret = l.find(s);
            if (!ret.size())
                std::cout << "null";
            else {
                for (auto i : ret)
                    std::cout << i << ' ';
            }
            std::cout << '\n';
        } else if (opt == "erase") {
            std::string s;
            int data;
            std::cin >> s >> data;
            l.erase(s, data);
        }
    }
    return 0;
}
