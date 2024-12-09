#include <iostream>
#include <thread>

// Function as entry point
void hello_world() { std::cout << "Hello World from Thread! " << std::endl; }

// Functors as Entry Point
class Hello {
   public:
    void operator()() { std::cout << "Hello, Functor Thread!" << std::endl; }
};

int main() {
    std::thread thread_function_pointer(hello_world);

    Hello hello;
    std::thread thread_functor(hello);

    // wait for the thred to complete
    thread_function_pointer.join();
    thread_functor.join();

    return 0;
}