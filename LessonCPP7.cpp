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



bool fp_stop_or_go()
{
    std::cout << "Calc n to stop anything else to continue: ";
    char value{};
    std::cin >> value;
    std::cin.ignore();
    return value == 'n' ? false : true;
}

double fp_get_user_number()
{
    while (true)
    {
        std::cout << "Enter number: ";
        double value{ 0 };
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

char fp_get_user_operator()
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
    return static_cast<double>(x + y);
}

double fp_subtract(const double x, const double y)
{
    return static_cast<double>(x - y);
}

double fp_multiply(const double x, const double y)
{
    return static_cast<double>(x * y);
}

double fp_divide(const double x, const double y)
{
    if (x != 0.0)
    {
        if (y == 0.0)// if y is 0.0 x is not so return x
            return x;
        return static_cast<double>(x / y);//do calac
    }
    else
        return x;// if 0.0 return 0.0
}

using arithmeticFcn = std::function<double(double, double)>;

arithmeticFcn get_arithmetic_funcion(char operater_function)
{
    switch (operater_function)
    {
    default: // default is fp_add
    case '+': return fp_add;
    case '-': return fp_subtract;
    case '*': return fp_multiply;
    case '/': return fp_divide;
    }
}

void calc_user_input()
{
    while (true)
    {
        if (fp_stop_or_go()) 
        {
            double user_number_1{ static_cast<double>(fp_get_user_number()) };
            char user_operator{ fp_get_user_operator() };
            double user_number_2{ static_cast<double>(fp_get_user_number()) };

            arithmeticFcn func{ get_arithmetic_funcion(user_operator) };
            double result{ static_cast<double>(func(user_number_1, user_number_2)) };

            std::cout << user_number_1 << ' ' << user_operator << ' '
                << user_number_2 << " = " << result << '\n';
        }
        else 
            break;
    }
}

void function_pointer_quiz()
{
    //Quiz time!

    //1) In this quiz, we’re going to write a version of our basic calculator 
    //using function pointers.

    //1a) Create a short program asking the user for two integer inputsand a 
    //mathematical operation(‘ + ’, ‘ - ‘, ‘ * ’, ‘ / ’).
    //Ensure the user enters a valid operation.

    //1b) Write functions named add(), subtract(), multiply(), and divide(). 
    //These should take two integer parameters and return an integer.

    //1c) Create a type alias named arithmeticFcn for a pointer to a
    //function that takes two integer parameters and returns an integer. 
    //Use std::function.

    //1d) Write a function named getArithmeticFunction() that takes an 
    //operator character and returns the appropriate function as a function pointer.

    //1e) Modify your main() function to call getArithmeticFunction(). 
    //Call the return value from that function with your inputs and print the result.

    calc_user_input();
}


int main()
{
    function_pointer_quiz();
    

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
