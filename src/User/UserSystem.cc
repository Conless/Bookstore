#include "UserSystem.h"
#include "Utils/Exception.h"

#include <cstring>
#include <fstream>
#include <utility>

namespace bookstore {

namespace user {

const BookstoreUser UserRoot = {"root", "root", "sjtu", 7};
const BookstoreUser UserGuest = {"DarkBluntness", "BrightSharpness",
                                 "BrightBluntness", 0};

UserFileSystem::UserFileSystem()
    : BaseFileSystem("user"), uid_table("uid"), siz(0) {
}

bool UserFileSystem::insert(const UserStr &uid, const BookstoreUser &data) {
    try {
        uid_table.insert(uid, siz + 1);
        siz++;
        BaseFileSystem::insert(siz, data);
        return 1;
    } catch (const NormalException &x) {
        if (x.what() == ULL_INSERTED)
            return 0;
        else {
            x.error();
            exit(-1);
        }
    }
}

bool UserFileSystem::erase(const UserStr &uid) {
    try {
        int pos = uid_table.erase(uid);
        BaseFileSystem::erase(pos);
        return 1;
    } catch (const NormalException &x) {
        if (x.what() == ULL_ERASE_NOT_FOUND)
            return 0;
        else {
            x.error();
            exit(-1);
        }
    }
}

bool UserFileSystem::edit(const UserStr &uid, const BookstoreUser &data) {
    try {
        int pos = uid_table.find(uid);
        BaseFileSystem::insert(pos, data);
        return 1;
    } catch (const NormalException &x) {
        if (x.what() == ULL_NOT_FOUND)
            return 0;
        else {
            x.error();
            exit(-1);
        }
    }
}

BookstoreUser UserFileSystem::find(const UserStr &uid) {
    try {
        int pos = uid_table.find(uid);
        return BaseFileSystem::find(pos);
    } catch (const NormalException &x) {
        if (x.what() == ULL_NOT_FOUND)
            return BookstoreUser();
        else {
            x.error();
            exit(-1);
        }
    }
}

void UserFileSystem::output() {
    for (int i = 1; i <= siz; i++) {
        BookstoreUser user = BaseFileSystem::find(i);
        std::cout << "ID=" << user.id.str << " Name=" << user.name.str << " Passwd=" << user.pswd.str << " Iden=" << user.iden << '\n';
    }
}

UserSystem::UserSystem() {
    std::ifstream fin("./data/user.log");
    if (fin.good())
        fin >> user_table.siz;
    user_table.insert(UserRoot.id, UserRoot);
    user_table.insert(UserGuest.id, UserGuest);
    user_stack.push(std::make_pair(UserGuest, 0));
}

UserSystem::~UserSystem() {
    std::ofstream fout("./data/user.log", std::ios::out | std::ios::trunc);
    fout << user_table.siz;
}

void UserSystem::UserRegister(const char *user_id, const char *user_name,
                              const char *user_pswd) {
    BookstoreUser tmp(user_id, user_name, user_pswd, 1);
    if (!user_table.insert(UserStr(user_id), tmp))
        throw InvalidException("The uid to be registered already exists");
    return;
}

void UserSystem::UserLogin(const char *user_id, const char *user_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (tmp.empty())
        throw UnknownException(UNKNOWN, "Not found such data");
    if ((cur.iden > tmp.iden && !strcmp(user_pswd, "")) ||
        user_pswd == tmp.pswd)
        user_stack.push(std::make_pair(tmp, 0));
    else
        throw InvalidException("Wrong password!");
}
void UserSystem::UserLogout() {
    BookstoreUser cur = user_stack.top().first;
    if (cur == UserGuest)
        throw InvalidException("You've logout all the accounts");
    user_stack.pop();
}
void UserSystem::ModifyPassword(const char *user_id, const char *cur_pswd,
                                const char *new_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (tmp.empty())
        throw UnknownException(
            UNKNOWN, "Not found such user when modifying the password.");
    if ((cur.iden == 7 && !strcmp(cur_pswd, "")) || cur_pswd == tmp.pswd) {
        tmp.pswd = UserStr(new_pswd);
        user_table.edit(tmp.id, tmp);
    } else
        throw InvalidException("Wrong password when modifying the password.");
}
void UserSystem::UserAdd(const char *user_id, const char *user_name,
                         const char *user_pswd, const int iden) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp(user_id, user_name, user_pswd, iden);
    if (cur.iden <= iden)
        throw InvalidException(
            "The identity should be senior when adding a user.");
    if (!user_table.insert(UserStr(user_id), tmp))
        throw InvalidException("The uid to be added already exists.");
}
void UserSystem::UserErase(const char *user_id) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (tmp.empty())
        throw InvalidException("Not found user when erasing");
    if (cur.iden <= tmp.iden)
        throw InvalidException(
            "The identity should be senior when erasing a user.");
    user_table.erase(UserStr(user_id));
}

void UserSystem::SelectBook(const int book_pos) {
    user_stack.top().second = book_pos;
}

int UserSystem::GetIdentity() const { return user_stack.top().first.iden; }

int UserSystem::GetBook() const {
    if (user_stack.top().first == UserGuest)
        return 0;
    return user_stack.top().second;
}

void UserSystem::output() {
    std::cout << "User data:\n";
    user_table.output();
    std::cout << '\n';
}

} // namespace user
} // namespace bookstore
