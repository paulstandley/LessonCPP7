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
#include "Header.h"



int sum_to(const int value) 
{//1)
    //A function named sum_to() that takes an integer parameter and returns
    //the sum of all the numbers between 1 and the input number.
    int sum{ value };
    for (int i = 0; i < value; i++)
        sum += i;
    return sum;
}

struct Employee
{
    std::string name{};
    int id{};
};

void print_employee_name(const Employee &employee)
{//2) A function named print_employee_name() that takes an Employee struct as input.
    std::cout << "Question(2) print name " << employee.name << '\n';
}



void lesson_7_quiz()
{
    /*Write function prototypes for each of the following functions. 
    Use the most appropriate parameter and return types 
    (by value, by address, or by reference),
    including use of const where appropriate.*/

    std::cout << "Question(1) 5 sums to " << sum_to(5) << '\n';

    Employee employee;
    employee.name = "Paul Standley";
    print_employee_name(employee);

    //(3) A function named minmax() 
    //that takes two integers as input and returns back to the caller 
    //the smaller and larger number in a std::pair.
    //A std::pair works identical to a std::tuple but stores exactly two elements.
    //std::pair<int, int> minmax(const int x, const int y);
    //std::minmax is a standard function.


    
}


int main()
{
    lesson_7_quiz(); 
    

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
