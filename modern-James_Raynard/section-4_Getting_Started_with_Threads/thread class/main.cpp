#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

// The task function
void hello() {
    std::this_thread::sleep_for(2s);
    std::cout << "Hello Thread!" << std::endl;
}

// Function taking a thread object as argument
// The object must be moved into the argument.
void func(std::thread thr) {
    std::cout << "Received the thread with ID: " << thr.get_id() << std::endl;
    thr.join();  // we have the ownership of thr thread so need to join
                 // otherwise crash.
}

std::thread func2() {
    // Start the thread
    std::thread thr(hello);

    // Return a local variable
    return thr;  // don't write the return std::move(thr); it will confuse the
                 // compiler optimizer

    // Return a temporary object
    // return std::thread(hello);
}

void hello_task() {
    try {
        // Throw an exception:
        throw std::exception();
    } catch (std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    std::cout << "Hello Task \n";
}

// the following is issue if used as entry point to thread
// as the exception needs to be handled in the same thread and not in any other
// thread or parent thread main
void hello_fail() {
    throw std::exception();

    std::cout << "hello fail\n";
}

int main() {
    // std::thread is a move-only object
    std::thread thr(hello);

    // Display the child thread's ID
    std::cout << "Hello hread has ID: " << thr.get_id() << std::endl;

    // Pass a named object using std::move
    func(std::move(thr));

    // Pass a temporary object
    func(std::thread(hello));

    // Call a function which return an std::thread object
    std::thread thr1 = func2();
    std::cout << "Received thread with ID in main: " << thr1.get_id()
              << std::endl;

    // main's thr object now "owns" the system thread
    // It is reponsible for calling join.
    thr1.join();

    std::thread thread1(hello_task);
    thread1.join();

    // the following will not work:
    /*
    try {
        std::thread thread2(hello_fail);
        thread2.join();
    } catch (std::exception& e) {
        std::cout << "Exception caught in main\n";
    }
    */

    std::cout << "finished execution\n";

    return 0;
}