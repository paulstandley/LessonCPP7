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


void pass_by_value(int y)
{
    std::cout << "y = " << y << '\n';
    y = 6;
    std::cout << "y = " << y << '\n';
    /*
    Pros and cons of pass by value

Advantages of passing by value:

Arguments passed by value can be variables (e.g. x), literals (e.g. 6), 
expressions (e.g. x+1), structs & classes, and enumerators. 
In other words, just about anything.
Arguments are never changed by the function being called, which prevents side effects.

Disadvantages of passing by value:

Copying structs and classes can incur a significant performance penalty,
especially if the function is called many times.
When to use pass by value:

When passing fundamental data type and enumerators, 
and the function does not need to change the argument.

When not to use pass by value:

When passing structs or classes (including std::array, std::vector, and std::string).
In most cases, pass by value is the best way to accept parameters of fundamental
types when the function does not need to change the argument. 
Pass by value is flexible and safe, and in the case of fundamental types, efficient.
    */
}

void callL7Func()
{
    //Function parameters passed by value can also be made const. 
    //This will enlist the compiler’s help in ensuring the function 
    //doesn’t try to change the parameter’s value.
    int x = 5;
    std::cout << "x = " << x << '\n';
    pass_by_value(x);
    std::cout << "x = " << x << '\n';
}

int main()
{
    callL7Func();

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
