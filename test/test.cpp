#include <iostream>
#include <exception>
#include <backtrace.h>

struct MyException : public std::exception
{
    MyException() {
        std::cout << "Construct MyException" << std::endl;
    }

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

