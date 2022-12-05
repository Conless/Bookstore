#ifndef BOOK_SYSTEM_H
#define BOOK_SYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>

class CustomBook {
  public:
    void PrintInfo();
    void BuyIt(const int &quantity);
    bool operator<(const CustomBook &num);

  private:
    std::string isbn, name;
    std::unordered_map<std::string, bool> keyword;
    int quantity;
    double price, total_cost;
};

namespace bookstore {

namespace book {

class BookSystem {
  public:
    BookSystem();
    ~BookSystem();
    
    void SearchByISBN(const std::string &isbn);
    void SearchByName(const std::string &name);
    void SearchByAuthor(const std::string &author);
    void SearchByKeyword(const std::string &keyword);

    void BuyBook(const std::string &isbn, const int &quantity);

  private:
    std::string sel_isbn;
};

} // namespace book

} // namespace bookstore

#endif
