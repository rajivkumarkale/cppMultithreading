#include <iostream>
#include <thread>

// Function as entry point
void hello_world() { std::cout << "Hello World from Thread!\n"; }

// Functors as Entry Point
class Hello {
   public:
    void operator()() { std::cout << "Hello, Functor Thread!\n"; }
};

int main() {
    std::thread thread_function_pointer(hello_world);

    Hello hello;
    std::thread thread_functor(hello);

    // Lambda expression as Entry Point
    std::thread thread_lambda(
        []() { std::cout << "Hello, Lambda, Thread!\n"; });

    // wait for the thred to complete
    thread_function_pointer.join();
    thread_functor.join();
    thread_lambda.join();

    return 0;
}