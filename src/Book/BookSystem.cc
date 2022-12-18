#include "BookSystem.h"

#include <algorithm>
#include <cstring>

#include "Utils/Exception.h"
#include "Utils/TokenScanner.h"

namespace bookstore {

namespace book {

CustomBook::CustomBook()
    : isbn(), name(), author(), keyword_cnt(0), quantity(0), price(0.0),
      total_cost(0.0) {}

CustomBook::CustomBook(const char *_isbn, const char *_name,
                       const char *_author, const char *_keyword_in_line) : isbn(_isbn), name(_name), author(_author) {
    input::BookstoreLexer ret(std::string(_keyword_in_line, '|'));
    for (int i = 0; i < ret.size(); i++)
        keyword[i] = ret[i].c_str();
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

void BookFileSystem::insert(const IsbnStr &isbn, const CustomBook &data) {
    siz++;
    isbn_table.insert(isbn, siz);
    name_table.insert(data.name, siz);
    author_table.insert(data.author, siz);
    for (int i = 0; i < data.keyword_cnt; i++)
        key_table.insert(data.keyword[i], siz);
    BaseFileSystem::insert(siz, data);
}
void BookFileSystem::erase(const IsbnStr &isbn) {
    int pos = isbn_table.erase(isbn);
    CustomBook tmp = BaseFileSystem::find(pos);
    name_table.erase(tmp.name, pos);
    author_table.erase(tmp.author, pos);
    for (int i = 0; i < tmp.keyword_cnt; i++)
        key_table.erase(tmp.keyword[i], siz);
    BaseFileSystem::erase(pos);
}

void BookFileSystem::edit(const IsbnStr &isbn, CustomBook data) {
    int pos = isbn_table.find(isbn);
    CustomBook tmp = BaseFileSystem::find(pos);
    if (!data.isbn.empty()) {
        isbn_table.erase(isbn);
        isbn_table.insert(isbn, pos);
    } else {
        data.isbn = isbn;
    }
    if (!data.name.empty()) {
        name_table.erase(tmp.name, pos);
        name_table.insert(data.name, pos);
    } else {
        data.name = tmp.name;
    }
    if (!data.author.empty()) {
        author_table.erase(tmp.author, pos);
        author_table.insert(data.author, pos);
    } else {
        data.author = tmp.author;
    }
    if (tmp.keyword_cnt) {
        for (int i = 0; i < tmp.keyword_cnt; i++)
            key_table.erase(tmp.keyword[i], pos);
        for (int i = 0; i < data.keyword_cnt; i++)
            key_table.insert(data.keyword[i], pos);
    } else {
        memcpy(data.keyword, tmp.keyword, sizeof(tmp.keyword));
        data.keyword_cnt = tmp.keyword_cnt;
    }
    BaseFileSystem::erase(pos);
    BaseFileSystem::insert(pos, data);
}

CustomBook BookFileSystem::FileSearchByISBN(const IsbnStr &isbn) {
    return BaseFileSystem::find(isbn_table.find(isbn));
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

std::vector<CustomBook> BookFileSystem::FileSearchByAuthor(const BookStr &author) {
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
    try {
        book_table.FileSearchByISBN(IsbnStr(isbn));
    } catch (const Exception &x) {
        CustomBook tmp;
        tmp.isbn = IsbnStr(isbn);
        book_table.insert(IsbnStr(isbn), tmp);
    }
    return;
}
void BookSystem::ModifyBook(const char *isbn, const char *_isbn, const char *_name, const char *_author, const char *_key) {
    book_table.edit(IsbnStr(isbn), CustomBook(_isbn, _name, _author, _key));
}

void BookSystem::SearchByISBN(const char *isbn) {
    CustomBook tmp = book_table.FileSearchByISBN(IsbnStr(isbn));
    tmp.PrintInfo();
}

void BookSystem::SearchByName(const char *name) {
    std::vector<CustomBook> tmp = book_table.FileSearchByName(BookStr(name));
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
}

void BookSystem::SearchByAuthor(const char *author) {
    std::vector<CustomBook> tmp = book_table.FileSearchByAuthor(BookStr(author));
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
}

void BookSystem::SearchByKeyword(const char *keyword) {
    std::vector<CustomBook> tmp = book_table.FileSearchByKeyword(BookStr(keyword));
    for (const auto &tmp_book : tmp)
        tmp_book.PrintInfo();
}

void BookSystem::output() { book_table.output(); }

void BookSystem::AddBook(const char *isbn, const CustomBook &data) {
    book_table.insert(IsbnStr(isbn), data);
}

} // namespace book
} // namespace bookstore