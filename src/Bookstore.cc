#include "Bookstore.h"

#include "User/UserSystem.h"
#include "Utils/Exception.h"
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
        throw Exception(QUIT_SYSTEM, "Quit.");
    if (msg.func == SU) {
        if (msg.info == SU_NO_PASSWD) {
            users.UserLogin(msg.args[0].c_str(), "");
        } else {
            users.UserLogin(msg.args[0].c_str(), msg.args[1].c_str());
        }
        return;
    }
    if (msg.func == LOGOUT) {
        users.UserLogout();
        return;
    }
    if (msg.func == REG) {
        users.UserRegister(msg.args[0].c_str(), msg.args[2].c_str(), msg.args[1].c_str());
        return;
    }
    if (msg.func == PASSWD) {
        users.ModifyPassword(msg.args[0].c_str(), msg.args[1].c_str(), msg.args[2].c_str());
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
    if (msg.func == SHOW) {
        if (msg.info == SHOW_ALL) {
            // TODO
        }
        if (msg.info == SHOW_ISBN) {
            books.SearchByISBN(msg.args[0].c_str());
        } else if (msg.info == SHOW_NAME) {
            books.SearchByName(msg.args[0].c_str());
        } else if (msg.info == SHOW_AUTHOR) {
            books.SearchByAuthor(msg.args[0].c_str());
        } else if (msg.info == SHOW_KEYWORD) {
            books.SearchByKeyword(msg.args[0].c_str());
        } else {
            throw Exception(UNKNOWN, "");
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
        books.ModifyBook(selected.c_str(), msg.args[0].c_str(),
                         msg.args[1].c_str(), msg.args[2].c_str(),
                         msg.args[3].c_str());
        return;
    }
    if (msg.func == IMPORT) {
        // TODO
    }
    throw Exception(UNIMPLEMENTED, "Bookstore doesn't support this operation.");
}

void Bookstore::output() {
    users.output();
    books.output();
}

} // namespace bookstore