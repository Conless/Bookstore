#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <string>
#include <unordered_map>
#include <stack>

#include "BookstoreBaseUser.h"

#include "List/UnrolledLinkedList.h"

namespace bookstore {

enum Identity {
    Manager,
    Staff,
    Customer,
    Visitor
};

namespace user {

class UserSystem {
  public:
    UserSystem();
    ~UserSystem();

    int QueryUnum(const std::string &user_id);
    void UserRegister(const std::string &user_id, const std::string &user_password, const std::string &user_name);
    void UserLogin(const std::string &user_id, const std::string &user_password);
    void ModifyPassword(const std::string &current_password, const std::string &new_password);
    void UserLogout();

  private:
    std::stack<BookstoreBaseUser *> current_user;
    UnrolledLinkedList uid_table;
};

} // namespace user

} // namespace bookstore

#endif
