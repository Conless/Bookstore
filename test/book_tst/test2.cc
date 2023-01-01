#include <bits/stdc++.h>

#include "Book/BookSystem.h"

using namespace std;
using namespace bookstore::list;
using namespace bookstore::book;

int main() {
    BookSystem master;
    int T;
    cin >> T;
    while (T--) {
        KeyType<kMaxISBNLen> isbn;
        KeyType<kMaxBookLen> name, author, key;
        KeyType<kMaxBookLen> keyword[15];
        string opt;
        cin >> opt;
        if (opt == "add") {
            cin >> isbn.str >> name.str >> author.str;
            CustomBook tmp;
            tmp.isbn = isbn;
            tmp.name = name;
            tmp.author = author;
            cin >> tmp.keyword_cnt;
            for (int i = 0; i < tmp.keyword_cnt; i++)
                cin >> tmp.keyword[i].str;
            master.AddBook(isbn.str, tmp);
        }
        if (opt == "showisbn") {
            cin >> isbn.str;
            master.SearchByISBN(isbn.str);
        }
        if (opt == "showname") {
            cin >> name.str;
            master.SearchByName(name.str);
        }
        if (opt == "showauthor") {
            cin >> author.str;
            master.SearchByAuthor(author.str);
        }
        if (opt == "showkey") {
            cin >> key.str;
            master.SearchByKeyword(key.str);
        }
        cout << '\n';
        master.output();
    }
    return 0;
}