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

class BookInfo {
  public:
    BookInfo();
    explicit BookInfo(const char *_isbn) : BookInfo() { isbn = _isbn; }
    explicit BookInfo(const char *_isbn, const char *_name, const char *_author, const std::vector<BookStr> &_keyword, const double _price);

    void PrintInfo() const;
    bool operator<(const BookInfo &x) const { return isbn < x.isbn; }
    bool empty() { return isbn == ""; }

  public:
    list::KeyType<kMaxISBNLen> isbn;
    list::KeyType<kMaxBookLen> name, author;
    list::KeyType<kMaxBookLen> keyword[15];
    int keyword_cnt;
    int quantity;
    int pos;
    double price;
};

class BookFileSystem : public file::BaseFileSystem<BookInfo> {
  public:
    BookFileSystem();
    ~BookFileSystem() = default;

    std::pair<int, bool> insert(const IsbnStr &isbn, const BookInfo &data);
    std::pair<int, bool> erase(const IsbnStr &isbn);
    std::pair<int, bool> edit(const int pos, BookInfo data);

    std::pair<double, bool> import(const int pos, const int quantity, const double cost);
    std::pair<double, bool> buy(const IsbnStr &isbn, const int quantity);
    
    BookInfo FileSearchByISBN(const IsbnStr &isbn);
    std::vector<BookInfo> FileSearchByName(const BookStr &name);
    std::vector<BookInfo> FileSearchByAuthor(const BookStr &author);
    std::vector<BookInfo> FileSearchByKeyword(const BookStr &keyword);

  public:
    void output();
    int siz;

  private:
    map isbn_table;
    multimap name_table;
    multimap author_table;
    multimap key_table;
};

class BookSystem {
  protected:
    BookSystem();
    ~BookSystem();

    int SelectBook(const char *isbn);

    void SearchAll();
    void SearchByISBN(const char *isbn);
    void SearchByName(const char *name);
    void SearchByAuthor(const char *author);
    void SearchByKeyword(const char *keyword);

    void BuyBook(const char *isbn, const int quantity);

    void ModifyBook(const int book_pos, const char *_isbn, const char *_name, const char *_author, const std::vector<BookStr> &_key, const double _price);
    void ImportBook(const int book_pos, const int quantity, const double cost);

    void ShowFinance(const int rev = -1);

  protected:
    void output();
    void AddBook(const char *isbn, const BookInfo &data);

  private:
    BookFileSystem book_table;
    std::vector<double> total_earn, total_cost;
};

} // namespace book

} // namespace bookstore

#endif
