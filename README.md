# HW5-Bookstore-2022

## 项目信息

项目: Bookstore version 0.2.0

作者: Conless Pan

## 程序功能概述

本项目是上海交通大学 ACM 班大一上第五次大作业, 作业详细要求可见 [原仓库](https://github.com/ACMClassCourse-2022/Bookstore-2022), 在 x86-64 Linux (Ubuntu 22.04 on WSL) 下进行开发, 使用命令行交互的方式完成操作. 在常规模式下, 输入指令包括了
```
# 基础指令
quit
exit

# 帐户系统指令
su [UserID] ([Password])?
logout
register [UserID] [Password] [Username]
passwd [UserID] ([CurrentPassword])? [NewPassword]
useradd [UserID] [Password] [Privilege] [Username]
delete [UserID]

# 图书系统指令
show (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]")?
buy [ISBN] [Quantity]
select [ISBN]
modify (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+
import [Quantity] [TotalCost]

# 日志系统指令
show finance ([Count])?
log
```

## 主体逻辑说明

程序的主要功能由类 Bookstore 进行统一调度, 更细化地: 
1. 对于一条输入指令, 先由 TokenScanner 进行指令切片, 并判断输入内容的初步合法性, 若合法则传给 Bookstore 类
2. Boookstore 捕捉到切片获得信息, 首先进行鉴权, 与用户系统进行交互获得当前操作者权限. 若鉴权合法, 则将指令进行进一步分析并传给用户系统 / 图书系统进行具体操作. 
3. 进行日志写入

在类 UserSystem 内进行用户数据调度, 在类 BookSystem 内进行用户数据调度, 在类 LogSystem 内进行日志数据存储.

## 各个类的接口和成员说明

Bookstore 类的代码结构如下: 
（采用了继承方式是因为一个 Bookstore 只会有一个对应的类, 但是后面发现这种写法似乎非常愚蠢, 不过不想改了）
```cpp
class Bookstore : public user::UserSystem, public book::BookSystem, public log::LogSystem {
  public:
    Bookstore();
    ~Bookstore();

    void AcceptMsg(const input::BookstoreParser &msg);

  public:
    void output();
};
```

UserSystem 类: 

```cpp
class UserSystem {
  protected:
    UserSystem();
    ~UserSystem();

    void UserRegister(const char *user_id, const char *user_name,
                      const char *user_pswd);
    void UserLogin(const char *user_id, const char *user_pswd);
    void UserLogout();
    int ModifyPassword(const char *user_id, const char *cur_pswd,
                        const char *new_pswd);
    void UserAdd(const char *user_id, const char *user_name,
                 const char *user_pswd, const int user_iden);
    int UserErase(const char *user_id);
    void SelectBook(const int book_pos);
    int GetBook() const;
    int GetIdentity() const;
    std::string GetName() const;

  protected:
    void output();

  private:
    std::vector<std::pair<BookstoreUser, int>> user_stack;
    UserFileSystem user_table;
};
```

BookSystem 类: 

```cpp
class BookSystem {
  protected:
    BookSystem();
    ~BookSystem();

    int SelectBook(const char *isbn);

    void SearchAll();
    void SearchByISBN(const char *isbn);
    void SearchByName(const char *name);
    void SearchByAuthor(const char *author);
    void SearchByKeyword(const char *keyword);

    void BuyBook(const char *isbn, const int quantity);

    void ModifyBook(const int book_pos, const char *_isbn, const char *_name, const char *_author, const std::vector<BookStr> &_key, const double _price);
    void ImportBook(const int book_pos, const int quantity, const double cost);

    void ShowFinance(const int rev = -1);

  protected:
    void output();
    void AddBook(const char *isbn, const BookInfo &data);

  private:
    BookFileSystem book_table;
    std::vector<double> total_earn, total_cost;
};
```

## 代码文件结构

```
.
├── docs
│   ├── shared
│   │   ├── bonus.md
│   │   ├── README.md
│   │   └── requirements.md
│   ├── exception.md
│   └── procedure.md
├── generated
│   ├── gen.txt
│   └── submit.cc
├── scripts
│   ├── build.sh
│   ├── clear.sh
│   ├── generate.sh
│   └── test.sh
├── src
│   ├── Book
│   │   ├── BookSystem.cc
│   │   └── BookSystem.h
│   ├── Files
│   │   └── FileSystem.h
│   ├── List
│   │   ├── UnrolledLinkedList.cc
│   │   └── UnrolledLinkedList.h
│   ├── Log
│   │   ├── LogSystem.cc
│   │   └── LogSystem.h
│   ├── User
│   │   ├── UserSystem.cc
│   │   └── UserSystem.h
│   ├── Utils
│   │   ├── Exception.h
│   │   ├── Printer.h
│   │   ├── TokenScanner.cc
│   │   └── TokenScanner.h
│   ├── Bookstore.cc
│   ├── Bookstore.h
│   ├── CMakeLists.txt
│   └── main.cc
├── test
│   ├── book_tst
│   ├── file_tst
│   ├── stl_tst
│   ├── ull_tst
│   ├── ull_tst.old
│   └── CMakeLists.txt
├── CMakeLists.txt
└── README.md
```
