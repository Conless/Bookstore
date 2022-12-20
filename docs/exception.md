# 异常类架构

## 异常类的接口

基类提供了异常类的基本元素: 异常类型与异常信息.

```
class BaseException {
  public:
    BaseException(ExceptionType _opt, const std::string &_msg)
        : opt(_opt), msg(_msg) {}
    std::string what() const { return msg; }

  private:
    ExceptionType opt;
    std::string msg;
};
```

常规异常是在程序的中间步骤中用于传递常规异常的类

## 异常类的抛出情况

下面给出了在程序运行的每个步骤中, 有可能抛出的异常

### 参数的输入

### 指令的读入和传参

```
Operate a message
├─ BookstoreLexer (Cutting the message)
├─ BookstoreParser
│  ├─ quit
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ su
│  │  ├─ SU_NO_PASSWD 
│  │  ├─ SU_PASSWD
│  │  └─ Parameters Error: InputException
│  ├─ logout
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException 
│  ├─ register
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ passwd
│  │  ├─ with current
│  │  ├─ no current
│  │  └─ Parameters Error: InputException
│  ├─ useradd
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ delete
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ show
│  │  ├─ Show all
│  │  ├─ Show isbn
│  │  ├─ Show name
│  │  ├─ Show author
│  │  ├─ Show keyword
│  │  └─ Parameters Error: InputException
│  ├─ buy
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ select
│  │  ├─ Normal
│  │  └─ Parameters Error: InputException
│  ├─ modify
│  │  ├─ Normal
│  │  ├─ No parameter: InvalidException
│  │  ├─ Repeated parameter: InvalidException
│  │  └─ Parameters Error: InputException
│  └─ import
│     ├─ Normal
│     └─ Parameters Error: InputException
└─ Bookstore.AcceptMsg
   ├─ QUIT
   │  └─ Normal: NormalException(QUIT)
   ├─ CheckAuthority
   ├─ SU, LOGOUT, REG, PASSWD, USERADD, DEL, SHOW
   │  └─ Pass it to UserSystem or BookSystem
   ├─ SELECT
   │  └─ Pass it to both UserSystem and BookSystem
   ├─ MODIFY
   │  ├─ Judge if select a book - InvalidException
   │  ├─ Judge if have more than a keyword - InvalidException
   │  └─ Pass it to BookSystem
   ├─ BUY
   │  ├─ Judge if select a book - InvalidException
   │  ├─ Judge if quantity is not an integer - InvalidException
   │  └─ Pass it to BookSystem
   ├─ IMPORT
   │  ├─ Judge if select a book - InvalidException
   │  ├─ Judge quantity, total cost - InvalidException
   │  └─ Pass it to BookSystem
   ├─ FINANCE
   │  ├─ Normal
   │  └─ Parameters Error: InputException
   ├─ LOG
```

### 用户系统指令





