#include "BookSystem.h"

namespace bookstore {

namespace book {

BookFileSystem::BookFileSystem()
    : BaseFileSystem("book"), isbn_table("isbn"), name_table("name"),
      author_table("author"), key_table("key") {}

void BookFileSystem::insert(const char *isbn, const CustomBook &data) {
    siz++;
    isbn_table.insert(isbn, siz);
    name_table.insert(data.name, siz);
    author_table.insert(data.author, siz);
    for ()
}
BookSystem::BookSystem() {
    // TODO
}
BookSystem::~BookSystem() {
    // TODO
}

} // namespace book
} // namespace bookstore