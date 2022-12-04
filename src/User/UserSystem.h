#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>

#include "BookstoreBaseUser.h"

enum Identity { Manager, Staff, Customer, Visitor };

class UserSystem {
  public:
    UserSystem();
    ~UserSystem();

    void UserRegister(const std::string &user_id, const std::string &user_password, const std::string &user_name);
    void UserLogin(const std::string &user_id, const std::string &user_password);
    void ModifyPassword(const std::string &current_password, const std::string &new_password);
    void UserLogout();

  private:
    std::unordered_map<std::string, BookstoreBaseUser *> user_table;
    BookstoreBaseUser *current_user;
};

#endif
