#include <array>
#include <cstdio>
#include <cstring>
#include <string>

#include "ull.h"

int nextInt () {
  int x;
  scanf("%d", &x);
  return x;
}

String nextString () {
  String x;
  scanf("%s", x.buf);
  return x;
}

int main () {
  UnrolledLinkedList store {"data"};
  auto n = nextInt();
  for (auto i = 0; i < n; ++i) {
    auto cmd = std::string(nextString().buf);
    if (cmd == "insert") {
      auto key = nextString();
      auto value = nextInt();
      store.insert(key, value);
    } else if (cmd == "find") {
      auto key = nextString();
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
      auto key = nextString();
      auto value = nextInt();
      store.remove(key, value);
    }
  }
  return 0;
}
