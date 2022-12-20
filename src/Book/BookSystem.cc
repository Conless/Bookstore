#include "BookSystem.h"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "Utils/Exception.h"
#include "Utils/TokenScanner.h"

namespace bookstore {

namespace book {

CustomBook::CustomBook()
    : isbn(), name(), author(), keyword_cnt(0), quantity(0), price(0.0),
      total_cost(0.0) {}

CustomBook::CustomBook(const char *_isbn, const char *_name,
                       const char *_author, const char *_keyword_in_line,
                       const double _price)
    : isbn(_isbn), name(_name), author(_author), price(_price) {
    input::BookstoreLexer ret(std::string(_keyword_in_line), '|');
    for (int i = 0; i < ret.size(); i++)
        keyword[i] = ret[i].c_str();
    keyword_cnt = ret.size();
}

void CustomBook::PrintInfo() const {
    printf("%s\t%s\t%s\t", isbn.str, name.str, author.str);
    for (int i = 0; i < keyword_cnt; i++) {
        if (i)
            printf("|");
        printf("%s", keyword[i].str);
    }
    printf("\t%.2lf\t%d\n", price, quantity);
}

BookFileSystem::BookFileSystem()
    : BaseFileSystem("book"), isbn_table("isbn"), name_table("name"),
      author_table("author"), key_table("key") {}

bool BookFileSystem::insert(const IsbnStr &isbn, const CustomBook &data) {
    try {
        isbn_table.insert(isbn, siz + 1);
        siz++;
        name_table.insert(data.name, siz);
        author_table.insert(data.author, siz);
        for (int i = 0; i < data.keyword_cnt; i++)
            key_table.insert(data.keyword[i], siz);
        BaseFileSystem::insert(siz, data);
        return 1;
    } catch (NormalException(ULL_INSERTED)) {
        return 0;
    }
}

bool BookFileSystem::erase(const IsbnStr &isbn) {
    try {
        int pos = isbn_table.erase(isbn);
        CustomBook tmp = BaseFileSystem::find(pos);
        name_table.erase(tmp.name, pos);
        author_table.erase(tmp.author, pos);
        for (int i = 0; i < tmp.keyword_cnt; i++)
            key_table.erase(tmp.keyword[i], siz);
        BaseFileSystem::erase(pos);
        return 1;
    } catch (NormalException(ULL_ERASE_NOT_FOUND)) {
        return 0;
    }
}

bool BookFileSystem::edit(const IsbnStr &isbn, CustomBook data) {
    int pos = isbn_table.find(isbn);
    CustomBook tmp = BaseFileSystem::find(pos);
    if (!data.isbn.empty()) {
        if (data.isbn == tmp.isbn)
            return 0;
        isbn_table.erase(tmp.isbn);
        isbn_table.insert(data.isbn, pos);
        tmp.isbn = data.isbn;
    }
    if (!data.name.empty()) {
        name_table.erase(tmp.name, pos);
        name_table.insert(data.name, pos);
        tmp.name = data.name;
    }
    if (!data.author.empty()) {
        author_table.erase(tmp.author, pos);
        author_table.insert(data.author, pos);
        tmp.author = data.author;
    }
    if (data.keyword_cnt) {
        for (int i = 0; i < tmp.keyword_cnt; i++)
            key_table.erase(tmp.keyword[i], pos);
        for (int i = 0; i < data.keyword_cnt; i++)
            key_table.insert(data.keyword[i], pos);
        memcpy(tmp.keyword, data.keyword, sizeof(data.keyword));
        tmp.keyword_cnt = data.keyword_cnt;
    }
    if (data.price)
        tmp.price = data.price;
    BaseFileSystem::erase(pos);
    BaseFileSystem::insert(pos, tmp);
    return 1;
}

bool BookFileSystem::dec_quantity(const IsbnStr &isbn, const int quantity) {
    int pos = isbn_table.find(isbn);
    CustomBook tmp = BaseFileSystem::find(pos);
    if (tmp.quantity < quantity)
        return 0;
    tmp.quantity -= quantity;
    BaseFileSystem::erase(pos);
    BaseFileSystem::insert(pos, tmp);
    return 1;
}

void BookFileSystem::inc_quantity(const IsbnStr &isbn, const int quantity, const double cost) {
    int pos = isbn_table.find(isbn);
    CustomBook tmp = BaseFileSystem::find(pos);
    tmp.quantity += quantity;
    tmp.total_cost += cost;
    BaseFileSystem::erase(pos);
    BaseFileSystem::insert(pos, tmp);
}

CustomBook BookFileSystem::FileSearchByISBN(const IsbnStr &isbn) {
    try {
        int pos = isbn_table.find(isbn);
        return BaseFileSystem::find(pos);
    } catch (NormalException(ULL_NOT_FOUND)) {
        return CustomBook();
    }
}

std::vector<CustomBook> BookFileSystem::FileSearchByName(const BookStr &name) {
    std::vector<int> pos = name_table.find(name);
    std::vector<CustomBook> ret;
    ret.clear();
    for (auto p : pos)
        ret.push_back(BaseFileSystem::find(p));
    std::sort(ret.begin(), ret.end());
    return ret;
}

std::vector<CustomBook>
BookFileSystem::FileSearchByAuthor(const BookStr &author) {
    std::vector<int> pos = author_table.find(author);
    std::vector<CustomBook> ret;
    ret.clear();
    for (auto p : pos)
        ret.push_back(BaseFileSystem::find(p));
    std::sort(ret.begin(), ret.end());
    return ret;
}

std::vector<CustomBook>
BookFileSystem::FileSearchByKeyword(const BookStr &keyword) {
    std::vector<int> pos = key_table.find(keyword);
    std::vector<CustomBook> ret;
    ret.clear();
    for (auto p : pos)
        ret.push_back(BaseFileSystem::find(p));
    std::sort(ret.begin(), ret.end());
    return ret;
}

void BookFileSystem::output() {
    for (int i = 1; i <= siz; i++) {
        CustomBook tmp = BaseFileSystem::find(i);
        printf("ISBN=%s Name=%s Author=%s Keywords=", tmp.isbn.str,
               tmp.name.str, tmp.author.str);
        for (int i = 0; i < tmp.keyword_cnt; i++) {
            if (i)
                printf("|");
            printf("%s", tmp.keyword[i].str);
        }
        printf("\n");
    }
}

BookSystem::BookSystem() {}
BookSystem::~BookSystem() {
    // TODO
}

void BookSystem::SelectBook(const char *isbn) {
    CustomBook tmp = book_table.FileSearchByISBN(IsbnStr(isbn));
    if (tmp.empty()) {
        tmp.isbn = isbn;
        book_table.insert(IsbnStr(isbn), tmp);
    }
    return;
}
void BookSystem::ModifyBook(const char *isbn, const char *_isbn,
                            const char *_name, const char *_author,
                            const char *_key, const double _price) {
    if (!strcmp(isbn, ""))
        throw InvalidException("Modify a book before selecting it");
    book_table.edit(IsbnStr(isbn),
                    CustomBook(_isbn, _name, _author, _key, _price));
}

void BookSystem::SearchByISBN(const char *isbn) {
    CustomBook tmp = book_table.FileSearchByISBN(IsbnStr(isbn));
    if (tmp.empty()) {
        std::cout << '\n';
        return;
    }
    tmp.PrintInfo();
}

void BookSystem::SearchByName(const char *name) {
    std::vector<CustomBook> tmp = book_table.FileSearchByName(BookStr(name));
    if (tmp.empty()) {
        std::cout << '\n';
        return;
    }
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
    return;
}

void BookSystem::SearchByAuthor(const char *author) {
    std::vector<CustomBook> tmp =
        book_table.FileSearchByAuthor(BookStr(author));
    if (tmp.empty()) {
        std::cout << '\n';
        return;
    }
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
    return;
}

void BookSystem::SearchByKeyword(const char *keyword) {
    std::vector<CustomBook> tmp =
        book_table.FileSearchByKeyword(BookStr(keyword));
    if (tmp.empty()) {
        std::cout << '\n';
        return;
    }
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
    return;
}

void BookSystem::SearchAll() {
    std::set<CustomBook> tmp = book_table.search();
    if (tmp.empty()) {
        std::cout << '\n';
        return;
    }
    for (CustomBook tmp_book : tmp)
        tmp_book.PrintInfo();
    return;
}

void BookSystem::output() { book_table.output(); }

void BookSystem::AddBook(const char *isbn, const CustomBook &data) {
    if (!book_table.insert(IsbnStr(isbn), data))
        throw InvalidException("Insert a book that already exists");
    return;
}

void BookSystem::BuyBook(const char *isbn, const int quantity) {
    if (!book_table.dec_quantity(IsbnStr(isbn), quantity))
        throw InvalidException("No enough book!");
}

void BookSystem::ImportBook(const char *isbn, const int quantity, const double cost) {
    book_table.inc_quantity(IsbnStr(isbn), quantity, cost);
}

} // namespace book

} // namespace bookstore
