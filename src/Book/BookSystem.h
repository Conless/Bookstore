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
    explicit CustomBook(const char *_isbn) : CustomBook() { isbn = _isbn; }
    explicit CustomBook(const char *_isbn, const char *_name, const char *_author, const char *_keyword_in_line, const double _price);

    void PrintInfo() const;
    bool operator<(const CustomBook &x) const { return isbn < x.isbn; }
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

class BookFileSystem : public file::BaseFileSystem<CustomBook> {
  public:
    BookFileSystem();
    ~BookFileSystem() = default;
    int insert(const IsbnStr &isbn, const CustomBook &data);
    bool erase(const IsbnStr &isbn);
    bool edit(const IsbnStr &isbn, CustomBook data);
    bool edit(const int pos, CustomBook data);
    bool inc_quantity(const int pos, const int quantity, const double cost);
    double dec_quantity(const IsbnStr &isbn, const int quantity);
    CustomBook FileSearchByISBN(const IsbnStr &isbn);
    std::vector<CustomBook> FileSearchByName(const BookStr &name);
    std::vector<CustomBook> FileSearchByAuthor(const BookStr &author);
    std::vector<CustomBook> FileSearchByKeyword(const BookStr &keyword);

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
    void ModifyBook(const int book_pos, const char *_isbn, const char *_name, const char *_author, const char *_key, const double _price);

    void SearchAll();
    void SearchByISBN(const char *isbn);
    void SearchByName(const char *name);
    void SearchByAuthor(const char *author);
    void SearchByKeyword(const char *keyword);

    void BuyBook(const char *isbn, const int quantity);
    void ImportBook(const int book_pos, const int quantity, const double cost);

    void ShowFinance(const int rev = -1);

  protected:
    void output();
    void AddBook(const char *isbn, const CustomBook &data);

  private:
    BookFileSystem book_table;
    std::vector<double> total_earn, total_cost;
};

} // namespace book

} // namespace bookstore

#endif
