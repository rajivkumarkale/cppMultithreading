#include <iostream>
#include <string>
#include <thread>

void print(std::string message) {
    std::cout << "message: " << message << std::endl;
}

void func(std::string&& message) {
    std::cout << "message rvalue: " << message << std::endl;
}

void func_ref(std::string& message) { message = "yoyo"; }

class Greeter {
   public:
    void hello() {
        std::cout << "start : hello from member function" << std::endl;
    }
};

int main() {
    std::thread thread1(print, "Hello, sending argument, please print!\n");

    std::string a = "hi";
    std::string c = "hi again";
    std::string b = "hello";
    std::thread thread2(func, std::move(a));
    std::thread thread3(func, "abc literal");
    // std::thread thread4(func_ref, c); // resulting in error.
    std::thread thread5(func_ref, std::ref(b));

    Greeter greet;
    std::thread thread6(&Greeter::hello, &greet);

    int i = 3;
    std::thread thread7([&i]() { i *= 2; });

    std::thread thread8(
        [](int i1, int i2) {
            std::cout << "The sum is: " << i1 + i2 << std::endl;
        },

        // The remaining arguments are passed to the lambda expression.
        4, 9);

    thread1.join();
    thread2.join();
    thread3.join();
    // thread4.join();
    thread5.join();
    std::cout << "a: " << a << ", b: " << b << std::endl;

    thread6.join();

    thread7.join();
    std::cout << "i: " << i << std::endl;

    thread8.join();

    return 0;
}