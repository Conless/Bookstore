#include "UserSystem.h"
#include "Utils/Exception.h"

#include <cstring>
#include <utility>

namespace bookstore {

namespace user {

UserFileSystem::UserFileSystem() : BaseFileSystem("user"), uid_table("uid"), siz(0) {}

void UserFileSystem::insert(const UserStr &uid, const BookstoreUser &data) {
    uid_table.insert(uid, ++siz);
    BaseFileSystem::insert(siz, data);
}

void UserFileSystem::erase(const UserStr &uid) {
    int pos = uid_table.erase(uid);
    BaseFileSystem::erase(pos);
}

void UserFileSystem::edit(const UserStr &uid, const BookstoreUser &data) {
    int pos = uid_table.find(uid);
    BaseFileSystem::insert(pos, data);
}

BookstoreUser UserFileSystem::find(const UserStr &uid) {
    int pos = uid_table.find(uid);
    if (pos == -1)
        throw Exception(UNKNOWN, "No found uid");
    return BaseFileSystem::find(pos);
}

void UserFileSystem::output() {
    for (int i = 1; i <= siz; i++) {
        BookstoreUser user = BaseFileSystem::find(i);
        printf("ID=%s Name=%s Pswd=%s Iden=%d\n", user.id.str, user.name.str, user.pswd.str, user.iden);
    }
}

UserSystem::UserSystem() {
    user_table.insert(UserStr("root"), BookstoreUser("root", "root", "sjtu", 7));
    BookstoreUser guest("guest", "guest", "123", 0);
    user_table.insert(UserStr("guest"), guest);
    user_stack.push(std::make_pair(guest, 0));
}

void UserSystem::UserRegister(const char *user_id, const char *user_name, const char *user_pswd) {
    BookstoreUser tmp(user_id, user_name, user_pswd, 1);
    user_table.insert(UserStr(user_id), tmp);
}

void UserSystem::UserLogin(const char *user_id, const char *user_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (cur.iden > tmp.iden || user_pswd == tmp.pswd.str)
        user_stack.push(std::make_pair(tmp, 0));
    else
        throw Exception(UNKNOWN, "Wrong pswd!");
}
void UserSystem::UserLogout() {
    BookstoreUser cur = user_stack.top().first;
    user_stack.pop();
    user_table.edit(cur.id, cur);
}
void UserSystem::ModifyPassword(const char *user_id, const char *cur_pswd, const char *new_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (cur.iden > tmp.iden || cur_pswd == tmp.pswd) {
        tmp.pswd = UserStr(new_pswd);
        user_table.edit(tmp.id, tmp);
    } else
        throw Exception(UNKNOWN, "Wrong pswd!");
}
void UserSystem::UserAdd(const char *user_id, const char *user_name, const char *user_pswd, const int iden) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp(user_id, user_name, user_pswd, iden);
    if (cur.iden <= iden)
        throw Exception(UNKNOWN, "Identity!");
    try {
        user_table.insert(UserStr(user_id), tmp);
    } catch (const Exception &x) {
    }
}
void UserSystem::UserErase(const char *user_id) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
    if (cur.iden <= tmp.iden)
        throw Exception(UNKNOWN, "Identity!");
    user_table.erase(UserStr(user_id));
}

void UserSystem::output() {
    printf("User data:\n");
    user_table.output();
    printf("\n");
}

} // namespace user
} // namespace bookstore