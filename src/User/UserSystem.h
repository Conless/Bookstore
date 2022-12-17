#ifndef BOOKSTORE_USERSYSTEM_H
#define BOOKSTORE_USERSYSTEM_H

#include <stack>
#include <string>

#include "File/FileSystem.h"
#include "List/UnrolledLinkedList.h"

namespace bookstore {

namespace user {

const int kMaxUserLen = 35;

using map = list::UnrolledLinkedListUnique<kMaxUserLen>;

enum Identity {
    Manager = 7,
    Staff = 3,
    Customer = 1,
    Guest = 0
};

class BookstoreUser {
  public:
    BookstoreUser() {}
    BookstoreUser(const BookstoreUser &_user) : BookstoreUser(_user.id, _user.name, _user.pswd, _user.iden) {}
    BookstoreUser(const char *_user_id, const char *_user_name, const char *_user_pswd, const int _iden);

  public:
    char id[kMaxUserLen], name[kMaxUserLen], pswd[kMaxUserLen];
    Identity iden;
};

class UserFileSystem : public file::BaseFileSystem<BookstoreUser> {
  public:
    UserFileSystem();
    ~UserFileSystem() = default;
    void insert(const char *uid, const BookstoreUser &data);
    void erase(const char *uid);
    void edit(const char *uid, const BookstoreUser &data);
    BookstoreUser find(const char *uid);

  public:
    void output();

  private:
    map uid_table;
    int siz;
};

class UserSystem {
  public:
    UserSystem();
    ~UserSystem() = default;

    void UserRegister(const char *user_id, const char *user_name, const char *user_pswd);
    void UserLogin(const char *user_id, const char *user_pswd);
    void UserLogout();
    void ModifyPassword(const char *user_id, const char *cur_pswd, const char *new_pswd);
    void UserAdd(const char *user_id, const char *user_name, const char *user_pswd, const int user_iden);
    void UserErase(const char *user_id);

  public:
    void output();

  private:
    std::stack<std::pair<BookstoreUser, std::string>> user_stack;
    UserFileSystem user_table;
};

} // namespace user

} // namespace bookstore

#endif
