#ifndef BOOKSTORE_USERSYSTEM_H
#define BOOKSTORE_USERSYSTEM_H

#include <stack>
#include <string>

#include "Files/FileSystem.h"
#include "List/UnrolledLinkedList.h"

namespace bookstore {

namespace user {

const int kMaxUserLen = 35;

using UserStr = list::KeyType<kMaxUserLen>;
using map = list::UnrolledLinkedListUnique<kMaxUserLen>;

enum Identity {
    Manager = 7,
    Staff = 3,
    Customer = 1,
    Guest = 0
};

class BookstoreUser {
  public:
    BookstoreUser() : id(), name(), pswd(), iden(Guest) {}
    BookstoreUser(const BookstoreUser &_user)
        : id(_user.id), name(_user.name), pswd(_user.pswd), iden(_user.iden) {}
    BookstoreUser(const UserStr &_user_id, const UserStr &_user_name,
                  const UserStr &_user_pswd, const Identity _user_iden)
        : id(_user_id), name(_user_name), pswd(_user_pswd), iden(_user_iden) {}
    BookstoreUser(const char *_user_id, const char *_user_name,
                  const char *_user_pswd, const int _user_iden)
        : id(_user_id), name(_user_name), pswd(_user_pswd),
          iden(Identity(_user_iden)) {}
    bool empty() { return id == ""; }
    bool operator==(const BookstoreUser &x) const { return id == x.id; }

  public:
    UserStr id, name, pswd;
    Identity iden;
};

class UserFileSystem : public file::BaseFileSystem<BookstoreUser> {
  public:
    UserFileSystem();
    ~UserFileSystem() = default;
    bool insert(const UserStr &uid, const BookstoreUser &data);
    bool erase(const UserStr &uid);
    bool edit(const UserStr &uid, const BookstoreUser &data);
    BookstoreUser find(const UserStr &uid);

  public:
    void output();

  private:
    map uid_table;
    int siz;
};

class UserSystem {
  protected:
    UserSystem();
    ~UserSystem() = default;

    void UserRegister(const char *user_id, const char *user_name,
                      const char *user_pswd);
    void UserLogin(const char *user_id, const char *user_pswd);
    void UserLogout();
    void ModifyPassword(const char *user_id, const char *cur_pswd,
                        const char *new_pswd);
    void UserAdd(const char *user_id, const char *user_name,
                 const char *user_pswd, const int user_iden);
    void UserErase(const char *user_id);
    void SelectBook(const char *isbn);
    std::string GetBook() const;
    int GetIdentity() const;

  protected:
    void output();

  private:
    std::stack<std::pair<BookstoreUser, std::string>> user_stack;
    UserFileSystem user_table;
};

} // namespace user

} // namespace bookstore

#endif
