# backtrace
一个可以打印c++异常堆栈的库

----

#### 支持系统

Linux

#### 安装

1.自行安装`libunwind`到系统中

2.使用cmake安装backtrace:
  
```
  $ mkdir -p build
  $ cd build
  $ cmake ..
  $ make
  $ make install
```

#### 使用

* 使用backtrace::getBacktrace()获取异常堆栈信息

```
#include <iostream>
#include <exception>
#include <backtrace.h>

struct MyException : public std::exception
{
    virtual const char* what() const noexcept {
        return "MyException";
    }
};

void foo()
{
    throw MyException();
}

int main() {
    try {
        foo();
    } catch (std::exception& e) {
        std::cout << "Exception Info:" << e.what() << std::endl;
        std::cout << "Exception Backtrace:\n" << backtrace::getBacktrace() << std::endl;
    }
}
```

#### 编译

* 编译源码文件时，需要使用-fno-inline编译选项
* 链接时需要链接backtrace和unwind

```
  $ g++ -std=c++11 -fno-inline -lbacktrace -lunwind test.cpp
```

#### 输出
```
Exception Info:MyException
Exception Backtrace:
0x0000000000401749 <std::exception::exception()+0x11>
0x00000000004016a6 <MyException::MyException()+0x18>
0x000000000040153b <foo()+0x25>
0x000000000040155b <main+0xe>
0x00007f77b12a0830 <__libc_start_main+0xf0>
0x0000000000401449 <_start+0x29>
```
