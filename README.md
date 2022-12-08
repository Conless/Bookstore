# HW5-Bookstore-2022

## Information

Project name: Bookstore

Author: Conless Pan

## Classes

The main class Bookstore is 

```cpp
class Bookstore {
  public:
    Bookstore();
    ~Bookstore();

    void ReadData();
    void PrintData();
    void OperateMsg(InputMsg);

  private:
    UserSystem users;
    BookSystem books;
};
```

Class UserSystem is 

```cpp
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
```

Class BookSystem is

```cpp
class BookSystem {
  public:
    void SearchByISBN(const std::string &isbn);
    void SearchByName(const std::string &name);
    void SearchByAuthor(const std::string &author);
    void SearchByKeyword(const std::string &keyword);

    void BuyBook(const std::string &isbn, const int &quantity);
  private:
    std::string sel_isbn;
};
```

Besides, the log system and finance system are also need to be correctly stored, and that was done in Bookstore.cc.

## File structure

```
HW5-Bookstore-2022
├─ CMakeLists.txt
├─ docs
│  ├─ bonus.md
│  ├─ README.md
│  └─ requirements.md
├─ README.md
├─ scripts
│  └─ build.sh
└─ src
   ├─ Book
   │  └─ BookSystem.h
   ├─ Bookstore.cc
   ├─ Bookstore.h
   ├─ CMakeLists.txt
   ├─ Exception.cc
   ├─ Exception.h
   ├─ main.cc
   ├─ User
   │  ├─ BookstoreBaseUser.h
   │  ├─ BookstoreManager.h
   │  └─ UserSystem.h
   ├─ utils.cc
   └─ utils.h
```
