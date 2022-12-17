#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <stack>
#include <string>
#include <unordered_map>

#include "File/FileSystem.h"
#include "List/UnrolledLinkedList.h"

namespace bookstore {

namespace user {

enum Identity {
    Manager = 7,
    Staff = 3,
    Customer = 1,
    Visitor = 0
};

class BookstoreUser {
  public:
    BookstoreUser() {}
    BookstoreUser(const BookstoreUser &_user) : BookstoreUser(_user.id, _user.name, _user.password, _user.iden) {}
    BookstoreUser(const char *_user_id, const char *_user_name, const char *_user_password, const int _iden);

  public:
    char id[31], name[31], password[31];
    Identity iden;
};

class UserFileSystem : public file::BaseFileSystem<BookstoreUser> {
  public:
    UserFileSystem();
    ~UserFileSystem() = default;
    void insert(const char *uid, BookstoreUser data);
    void erase(const char *uid);
    void edit(const char *uid, BookstoreUser data);
    BookstoreUser find(const char *uid);

  private:
    list::UnrolledLinkedMap uid_table;
    int siz;
};

class UserSystem {
  public:
    UserSystem();
    ~UserSystem() = default;

    void UserRegister(const char *user_id, const char *user_password, const char *user_name);
    void UserLogin(const char *user_id, const char *user_password);
    void UserLogout();
    void ModifyPassword(const char *user_id, const char *cur_password, const char *new_password);
    void UserAdd(const char *user_id, const char *user_password, const int iden, const char *user_name);
    void UserErase(const char *user_id);

  private:
    std::stack<std::pair<BookstoreUser, std::string>> user_stack;
    UserFileSystem user_table;
};

} // namespace user

} // namespace bookstore

#endif
