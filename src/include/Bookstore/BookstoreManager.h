#ifndef MANAGER_H
#define MANAGER_H

#include "BookstoreBaseUser.h"

class BookstoreManager : public BookstoreBaseUser {
  public:
    void UserAdd() override;
    void UserDelete(const std::string &user_id) override;
};

#endif
