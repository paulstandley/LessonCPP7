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
#include <tuple>
#include <functional>
#include "Header.h"


double get_user_number()
{
    while (true)
    {
        std::cout << "Enter number: ";
        int value{ 0 };
        std::cin >> value;
        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

char get_user_operator()
{
    while (true)
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char value{};
        std::cin >> value;
        switch (value)
        {
        case '+':
        case '-':
        case '/':
        case '*':
            std::cin.ignore(32767, '\n');
            return value;
        default:
            std::cin.ignore(32767, '\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

double fp_add(const double x, const double y)
{
    return x + y;
}

double fp_subtract(const double x, const double y)
{
    return x - y;
}

double fp_multiply(const double x, const double y)
{
    return x * y;
}

double fp_divide(const double x, const double y)
{
    return x / y;
}

void function_quiz()
{
    //Quiz time!
    //1) In this quiz, we’re going to write a version of our basic calculator 
    //using function pointers.

    //1a) Create a short program asking the user for two integer inputsand a 
    //mathematical operation(‘ + ’, ‘ - ‘, ‘ * ’, ‘ / ’).
    //Ensure the user enters a valid operation.

    double user_number_1{ get_user_number() };
    std::cout << "User number : " << user_number_1 << '\n';

    double user_number_2{ get_user_number() };
    std::cout << "User number : " << user_number_2 << '\n';

    char user_operator{ get_user_operator() };
    std::cout << "User operator : " << user_operator << '\n';

    //1b) Write functions named add(), subtract(), multiply(), and divide(). 
    //These should take two integer parameters and return an integer.

    std::cout << fp_add(user_number_1, user_number_2) << '\n';
    std::cout << fp_subtract(user_number_1, user_number_2) << '\n';
    std::cout << fp_multiply(user_number_1, user_number_2) << '\n';
    std::cout << fp_divide(user_number_1, user_number_2) << '\n';// check for 0

    //1c) Create a type alias named arithmeticFcn for a pointer to a
    //function that takes two integer parameters and returns an integer. 
    //Use std::function.

}


int main()
{
    function_quiz();
    

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
