// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>  //added stdexcept

// Custom exception derived from std::exception
class CustomApplicationException : public std::exception {
    private:
        std::string message;
    public:
        CustomApplicationException(const std::string& msg) : message(msg) {}

        // Override the what() method to provide custom error message
        const char* what() const noexcept override {
            return message.c_str();
        }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;
    throw std::runtime_error("Something went wrong in even more custom logic!");
    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    catch (const std::exception& e) {
        std::cout << "Caught an exception in custom application logic: " << e.what() << std::endl;
    }

    // Throwing a custom exception derived from std::exception
    throw CustomApplicationException("Custom logic failed with a specific error!");

    std::cout << "Leaving Custom Application Logic." << std::endl; // Unreachable code after throw
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    if (den == 0) {
        throw std::invalid_argument("Division by zero is not allowed!");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error during division: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.

    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomApplicationException& e) {
        // Catch custom exception first
        std::cout << "Main caught CustomApplicationException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Catch standard exceptions
        std::cout << "Main caught std::exception: " << e.what() << std::endl;
    }
    catch (...) {
        // Catch-all handler for any uncaught exceptions
        std::cout << "Main caught an unknown exception!" << std::endl;
    }

    std::cout << "Program completed." << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu