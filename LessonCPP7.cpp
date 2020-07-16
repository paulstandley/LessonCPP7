#include "pch.h"
#include <algorithm> // std::shuffle sort
#include <array>
#include <ctime> //  std::time
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include <iterator> // for std::size
#include "Header.h"


int return_by_value(int x)
{// double value
    //When to use return by value:
    //When returning variables that were declared inside the function
    //    When returning function arguments that were passed by value

    //    When not to use return by value :
    //When returning a built - in array or pointer(use return by address)
    //    When returning a large struct or class (use return by reference)

    int value{ x * 2 };
    return value;
}

int* return_by_address(int x)
{// return address
    int value{ x * 2 };
    return &value;
    // value is destroyed just after its address is returned to the caller.
    //The end result is that the caller ends up with the address of 
    //non-allocated memory (a dangling pointer), which will cause problems if used.
}

int* allocate_array(int size)
{// return dynamically allocated memory
    return new int[size];
    //This works because dynamically allocated memory does not go out of scope 
    //at the end of the block in which it is declared, 
    //so that memory will still exist when the address is returned back to the caller. 
    //Keeping track of manual allocations can be difficult.
}

void returning_values_by_value_reference_and_address()
{
    int value{ return_by_value(33) };
    std::cout << "Return by value : " << value << '\n';

    int* address{ return_by_address(44) };
    std::cout << "Return by address : " << &address << '\n';

    // Return by address was often used to return 
    // dynamically allocated memory to the caller:
    int* array{ allocate_array(25) };
    // do stuff with array
    delete[] array;

    //When to use return by address:
    //When returning dynamically allocated memoryand you can’t use a type that handles allocations for you
    //When returning function arguments that were passed by address

    //When not to use return by address :
    //When returning variables that were declared inside the function or parameters that were passed by value(use return by value)
    //When returning a large struct or class that was passed by reference
    //(use return by reference)
}

int main()
{
    returning_values_by_value_reference_and_address();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
