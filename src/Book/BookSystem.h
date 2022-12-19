#ifndef BOOKSTORE_BOOKSYSTEM_H
#define BOOKSTORE_BOOKSYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Files/FileSystem.h"
#include "List/UnrolledLinkedList.h"



namespace bookstore {

namespace book {

const int kMaxISBNLen = 25;
const int kMaxBookLen = 65;

using IsbnStr = list::KeyType<kMaxISBNLen>;
using BookStr = list::KeyType<kMaxBookLen>;

using map = list::UnrolledLinkedListUnique<kMaxISBNLen>;
using multimap = list::UnrolledLinkedList<kMaxBookLen>;

class CustomBook {
  public:
    CustomBook();
    CustomBook(const char *_isbn) : CustomBook() { isbn = _isbn; }
    CustomBook(const char *_isbn, const char *_name, const char *_author, const char *_keyword_in_line);

    void PrintInfo() const;
    void BuyIt(const int &quantity);
    bool operator<(const CustomBook &x) const { return isbn < x.isbn; }

  public:
    list::KeyType<kMaxISBNLen> isbn;
    list::KeyType<kMaxBookLen> name, author;
    list::KeyType<kMaxBookLen> keyword[15];
    int keyword_cnt;
    int quantity;
    double price, total_cost;
};

class BookFileSystem : public file::BaseFileSystem<CustomBook> {
  public:
    BookFileSystem();
    ~BookFileSystem() = default;
    void insert(const IsbnStr &isbn, const CustomBook &data);
    void erase(const IsbnStr &isbn);
    void edit(const IsbnStr &isbn, CustomBook data);
    CustomBook FileSearchByISBN(const IsbnStr &isbn);
    std::vector<CustomBook> FileSearchByName(const BookStr &name);
    std::vector<CustomBook> FileSearchByAuthor(const BookStr &author);
    std::vector<CustomBook> FileSearchByKeyword(const BookStr &keyword);

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

    void SelectBook(const char *isbn);
    void ModifyBook(const char* isbn, const char *_isbn, const char *_name, const char *_author, const char *_key);
    
    void SearchByISBN(const char *isbn);
    void SearchByName(const char *name);
    void SearchByAuthor(const char *author);
    void SearchByKeyword(const char *keyword);

    void BuyBook(const std::string &isbn, const int &quantity);

  public:
    void output();
    void AddBook(const char *isbn, const CustomBook &data);

  private:
    BookFileSystem book_table;
};

} // namespace book

} // namespace bookstore

#endif
