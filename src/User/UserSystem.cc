#include "UserSystem.h"
#include "Utils/Exception.h"

#include <cstring>
#include <utility>

namespace bookstore {

namespace user {

const BookstoreUser UserRoot = {"root", "root", "sjtu", 7};
const BookstoreUser UserGuest = {"fjdklsjfklsd", "nvdsavis", "FJSADIOUEWNF", 0};

UserFileSystem::UserFileSystem()
    : BaseFileSystem("user"), uid_table("uid"), siz(0) {}

void UserFileSystem::insert(const UserStr &uid, const BookstoreUser &data) {
    uid_table.insert(uid, siz + 1);
    siz++;
    BaseFileSystem::insert(siz, data);
    return;
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
    int pos = uid_table.find(uid); // possibly throw error
    return BaseFileSystem::find(pos);
}

void UserFileSystem::output() {
    for (int i = 1; i <= siz; i++) {
        BookstoreUser user = BaseFileSystem::find(i);
        printf("ID=%s Name=%s Pswd=%s Iden=%d\n", user.id.str, user.name.str,
               user.pswd.str, user.iden);
    }
}

UserSystem::UserSystem() {
    user_table.insert(UserRoot.id, UserRoot);
    user_table.insert(UserGuest.id, UserGuest);
    user_stack.push(std::make_pair(UserGuest, 0));
}

void UserSystem::UserRegister(const char *user_id, const char *user_name,
                              const char *user_pswd) {
    BookstoreUser tmp(user_id, user_name, user_pswd, 1);
    try {
        user_table.insert(UserStr(user_id), tmp);
    } catch (NormalException(ULL_INSERTED)) {
        throw InvalidException("The uid to be registered already exists");
    } 
}

void UserSystem::UserLogin(const char *user_id, const char *user_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp = user_table.find(UserStr(user_id));
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
    user_table.edit(cur.id, cur);
}
void UserSystem::ModifyPassword(const char *user_id, const char *cur_pswd,
                                const char *new_pswd) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp;
    try {
        user_table.find(UserStr(user_id)); // possibly throw error
    } catch (NormalException(ULL_NOT_FOUND)) {
        throw InvalidException(
            "Not found such user when modifying the password.");
    }
    if ((cur.iden > tmp.iden && !strcmp(cur_pswd, "")) ||
        cur_pswd == tmp.pswd) {
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
        throw InvalidException("The identity should be senior when adding a user.");
    try {
        user_table.insert(UserStr(user_id), tmp); // possibly throw error
    } catch (NormalException(ULL_INSERTED)) {
        throw InvalidException("The uid to be added exists.");
    }
}
void UserSystem::UserErase(const char *user_id) {
    BookstoreUser cur = user_stack.top().first;
    BookstoreUser tmp =
        user_table.find(UserStr(user_id)); // possibly throw error
    if (cur.iden <= tmp.iden)
        throw InvalidException("The identity should be senior when erasing a user.");
    user_table.erase(UserStr(user_id));
}

void UserSystem::output() {
    printf("User data:\n");
    user_table.output();
    printf("\n");
}

} // namespace user
} // namespace bookstore