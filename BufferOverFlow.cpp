// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <limits> //added to check character limits
#include <string> //added to allow string

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_number
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.
    //  You must notify the user if they entered too much data.

    const std::string account_number = "CharlieBrown42";
    char user_input[20];
    std::cout << "Enter a value: ";
    std::cin.getline(user_input, sizeof(user_input));

    // Check if the input might have been truncated (meaning the buffer was filled)
    if (std::cin.fail()) {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
        std::cout << "Warning: You entered too much data. Input has been truncated to prevent buffer overflow." << std::endl;
    }
    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
