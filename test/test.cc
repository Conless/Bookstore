#include <bits/stdc++.h>

#include "Bookstore/BlockList.h"

using namespace std;

int main() {
    bookstore::list::BlockList<std::string, int> store;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string cmd;
        cin >> cmd;
        if (cmd == "insert") {
            std::string key;
            cin >> key;
            int value;
            cin >> value;
            store.insert(key, value);
        } else if (cmd == "find") {
            string key;
            cin >> key;
            auto values = store.find(key);
            if (values.empty()) {
                puts("null");
            } else {
                for (auto v : values) {
                    printf("%d ", v);
                }
                putchar('\n');
            }
        } else if (cmd == "delete") {
            string key;
            int value;
            cin >> key >> value;
            store.remove(key, value);
        }
    }
    return 0;
}
