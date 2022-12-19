#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"
#include <new>
#include <string>

namespace bookstore {

Bookstore::Bookstore() {
    // TODO
}
Bookstore::~Bookstore() {
    // TODO
}

void Bookstore::AcceptMsg(const input::BookstoreParser &msg) {
    using namespace input;
    if (msg.func == QUIT)
        throw NormalException(QUIT_SYSTEM);
    if (msg.func == SU) {
        users.UserLogin(msg.args[0].c_str(), msg.args[1].c_str());
        return;
    }
    if (msg.func == LOGOUT) {
        users.UserLogout();
        return;
    }
    if (msg.func == REG) {
        users.UserRegister(msg.args[0].c_str(), msg.args[2].c_str(),
                           msg.args[1].c_str());
        return;
    }
    if (msg.func == PASSWD) {
        users.ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(),
                             msg.args[2].c_str());
        return;
    }
    if (msg.func == USERADD) {
        users.UserAdd(msg.args[0].c_str(), msg.args[3].c_str(),
                      msg.args[1].c_str(), std::stoi(msg.args[2]));
        return;
    }
    if (msg.func == DEL) {
        // TODO
        // users.UserDelete()
    }
    if (msg.func == SHOW_ALL || msg.func == SHOW_ISBN ||
        msg.func == SHOW_NAME || msg.func == SHOW_AUTHOR ||
        msg.func == SHOW_KEYWORD) {
        if (msg.func == SHOW_ALL) {
            // TODO
        }
        if (msg.func == SHOW_ISBN) {
            books.SearchByISBN(msg.args[0].c_str());
        } else if (msg.func == SHOW_NAME) {
            books.SearchByName(msg.args[0].c_str());
        } else if (msg.func == SHOW_AUTHOR) {
            books.SearchByAuthor(msg.args[0].c_str());
        } else if (msg.func == SHOW_KEYWORD) {
            if (msg.args[0].find('|') == std::string::npos)
                throw InvalidException("More than one keywords in show");
            books.SearchByKeyword(msg.args[0].c_str());
        } else {
            throw UnknownException(UNKNOWN, "???");
        }
        return;
    }
    if (msg.func == SEL) {
        // TODO
        selected = msg.args[0];
        books.SelectBook(selected.c_str());
        return;
    }
    if (msg.func == MODIFY) {
        // TODO
        if (users.GetBook() == "")
            throw InvalidException("Modify a book before selecting it");
        books.ModifyBook(selected.c_str(), msg.args[0].c_str(),
                         msg.args[1].c_str(), msg.args[2].c_str(),
                         msg.args[3].c_str());
        return;
    }
    if (msg.func == IMPORT) {
        // TODO
    }
    throw InvalidException("Bookstore does NOT support this operation.");
}

void Bookstore::output() {
    users.output();
    books.output();
}

} // namespace bookstore