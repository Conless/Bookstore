# HW5-Bookstore-2022

## 项目信息

项目: Bookstore version 1.0.0

作者: Conless Pan

## 程序功能概述

本项目在 x86-64 Linux (Ubuntu 22.04 on WSL) 下进行开发, 使用命令行交互的方式完成操作. 在常规模式下, 输入指令包括了
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
1. 对于除了退出指令以外的所有指令, Bookstore 类首先访问账户系统, 获取当前用户的身份信息进行鉴权
2. 对于账户系统指令, Bookstore 类在获取相关信息后, 将其传送给账户系统, 在账户系统内部直接进行操作
3. 对于图书系统指令, Bookstore 类在获取相关信息后, 分以下几种情况讨论
   - 若指令为 select, 先访问图书系统检查图书存在性, 随后直接进入用户系统
   - 若指令为其它, 先访问用户系统鉴权返回一个 bool 类型, 随后直接进入图书系统
4. 进行日志写入

在类 UserSystem 内进行用户数据调度, 更细化地:
1. 对于登录操作, 在块状链表中找到当前 uid 对应的编号, 在静态库中查找该编号对应的用户密码与用户类型, 并且将其指针 push 进入栈中.
2. 对于其他操作, 直接进行鉴权执行即可.
3. 对于 select 操作, 直接写入当前 isbn.

在类 LogSystem 内进行日志数据存储.


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
    std::unordered_map<std::string, BookstoreUser *> user_table;
    BookstoreUser *current_user;
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
   │  ├─ BookstoreUser.h
   │  ├─ BookstoreManager.h
   │  └─ UserSystem.h
   ├─ utils.cc
   └─ utils.h
```
