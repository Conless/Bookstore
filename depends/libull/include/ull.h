#ifndef LIBULL_ULL_H_
#define LIBULL_ULL_H_

#include <cstring>
#include <utility>
#include <vector>

struct String {
  char buf[65];
  bool operator< (const String &rhs) const {
    return strcmp(buf, rhs.buf) < 0;
  }
  bool operator== (const String &rhs) const {
    return strcmp(buf, rhs.buf) == 0;
  }
  bool operator!= (const String &rhs) const {
    return strcmp(buf, rhs.buf) != 0;
  }
};

class UnrolledLinkedList {
 public:
  UnrolledLinkedList (const char *filename);
  ~UnrolledLinkedList ();
  void insert (const String &key, const int &value);
  void remove (const String &key, const int &value);
  std::vector<int> find (const String &key);
  std::vector<std::pair<String, int>> findAll ();
 private:
  void *impl_;
};

#endif  // LIBULL_ULL_H_
