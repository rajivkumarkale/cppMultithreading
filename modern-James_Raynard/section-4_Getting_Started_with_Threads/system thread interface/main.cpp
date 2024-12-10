#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void hello() {
    std::this_thread::sleep_for(2s);
    std::cout << "Hello : thread id:" << std::this_thread::get_id()
              << std::endl;
}

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    std::thread thread1(hello);
    std::cout << "thread handle before: " << thread1.native_handle()
              << ", thread id: " << thread1.get_id() << std::endl;

    thread1.join();
    std::cout << "thread handle after: " << thread1.native_handle()
              << ", thread id: " << thread1.get_id() << std::endl;

    return 0;
}