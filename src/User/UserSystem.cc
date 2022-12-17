#include "UserSystem.h"
#include "Utils/Exception.h"

#include <cstring>
#include <utility>

namespace bookstore {

namespace user {

BookstoreUser::BookstoreUser(const char *_user_id, const char *_user_name, const char *_user_password, const int _iden) {
    strcpy(id, _user_id);
    strcpy(name, _user_name);
    strcpy(password, _user_password);
    iden = Identity(_iden);
}

UserFileSystem::UserFileSystem() : BaseFileSystem("user"), uid_table("uid"), siz(0) {}

void UserFileSystem::insert(const char *uid, BookstoreUser data) {
    uid_table.insert(uid, ++siz);
    BaseFileSystem::insert(siz, data);
}

void UserFileSystem::erase(const char *uid) {
    int pos = uid_table.erase(uid);
    BaseFileSystem::erase(pos);
}

void UserFileSystem::edit(const char *uid, BookstoreUser data) {
    int pos = uid_table.find(uid);
    BaseFileSystem::insert(pos, data);
}

BookstoreUser UserFileSystem::find(const char *uid) {
    int pos = uid_table.find(uid);
    return BaseFileSystem::find(pos);
}

UserSystem::UserSystem() {
    // TODO
    BookstoreUser visitor("", "", "", 0);
    user_table.insert("", visitor);
    user_stack.push(std::make_pair(visitor, ""));
}

void UserSystem::UserRegister(const char *user_id, const char *user_password, const char *user_name) {
    BookstoreUser tmp(user_id, user_password, user_name, 1);
    user_table.insert(user_id, tmp);
}

void UserSystem::UserLogin(const char *user_id, const char *user_password) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(user_id);
    if (cur.iden > tmp.iden || !strcmp(user_password, tmp.password))
        user_stack.push(std::make_pair(tmp, ""));
    else
        throw Exception(UNKNOWN, "Wrong password!");
}
void UserSystem::UserLogout() {
    BookstoreUser cur = user_stack.top().first;
    user_stack.pop();
    user_table.edit(cur.id, cur);
}
void UserSystem::ModifyPassword(const char *user_id, const char *cur_password, const char *new_password) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(user_id);
    if (cur.iden > tmp.iden || !strcmp(cur_password, tmp.password)) {
        strcpy(tmp.password, new_password);
        user_table.edit(tmp.id, tmp);
    } else
        throw Exception(UNKNOWN, "Wrong password!");
}
void UserSystem::UserAdd(const char *user_id, const char *user_password, const int iden, const char *user_name) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp(user_id, user_name, user_password, iden);
    if (cur.iden <= iden)
        throw Exception(UNKNOWN, "Identity!");
    try {
        user_table.insert(user_id, tmp);
    } catch (const Exception &x) {
    }
}
void UserSystem::UserErase(const char *user_id) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(user_id);
    if (cur.iden <= tmp.iden)
        throw Exception(UNKNOWN, "Identity!");
    user_table.erase(user_id);
}

} // namespace user
} // namespace bookstore