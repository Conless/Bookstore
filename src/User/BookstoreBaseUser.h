#ifndef BASE_USER_H
#define BASE_USER_H

#include <string>

class BookstoreBaseUser {
  public:
    BookstoreBaseUser();
    BookstoreBaseUser(const std::string &user_id, const std::string &user_password, const std::string &user_name);

    void ModifyPassword(const std::string &current_password, const std::string &new_password);

    virtual void UserAdd();
    virtual void UserDelete(const std::string &user_id);

    // TODO

  private:
    std::string user_id, user_password, user_name;
};

#endif
