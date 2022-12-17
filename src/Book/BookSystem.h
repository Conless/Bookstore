#ifndef BOOKSTORE_BOOKSYSTEM_H
#define BOOKSTORE_BOOKSYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>

#include "File/FileSystem.h"
#include "List/UnrolledLinkedList.h"



namespace bookstore {

namespace book {

const int kMaxISBNLen = 25;
const int kMaxBookLen = 65;

using map = list::UnrolledLinkedListUnique<kMaxISBNLen>;
using multimap = list::UnrolledLinkedList<kMaxBookLen>;

class CustomBook {
  public:
    void PrintInfo();
    void BuyIt(const int &quantity);
    bool operator<(const CustomBook &num);

  public:
    list::KeyType<kMaxISBNLen> isbn;
    list::KeyType<kMaxBookLen> name, author;
    std::vector<list::KeyType<kMaxBookLen>> keyword;
    int quantity;
    double price, total_cost;
};

class BookFileSystem : public file::BaseFileSystem<CustomBook> {
  public:
    BookFileSystem();
    ~BookFileSystem() = default;
    void insert(const char *isbn, const CustomBook &data);
    void erase(const char *isbn);
    void edit(const char *uid, const CustomBook &data);
    std::vector<CustomBook> find_by_isbn(const char *isbn);
    std::vector<CustomBook> find_by_name(const char *isbn);
    std::vector<CustomBook> find_by_author(const char *isbn);
    std::vector<CustomBook> find_by_keyword(const char *isbn);

  public:
    void output();

  private:
    int siz = 0;
    map isbn_table;
    multimap name_table;
    multimap author_table;
    multimap key_table;
};

class BookSystem {
  public:
    BookSystem();
    ~BookSystem();
    
    void SearchByISBN(const std::string &isbn);
    void SearchByName(const std::string &name);
    void SearchByAuthor(const std::string &author);
    void SearchByKeyword(const std::string &keyword);

    void BuyBook(const std::string &isbn, const int &quantity);
};

} // namespace book

} // namespace bookstore

#endif
