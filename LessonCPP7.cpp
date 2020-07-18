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

int get_index_of_largest_value(const std::vector<int>& array)
{//std::max_element is a standard function.
    int length{ static_cast<int>(size(array)) };
    int big_num{ 0 };

    for (int value_index : array)
    {
        if (value_index > big_num)
        {
            big_num = value_index;
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (big_num == array[i])
        {
            return i;
        }
    }
}

const std::string& getElement(const std::vector<std::string>& array, const int index)
{//(5)
    //A function named getElement() that takes an array of std::string 
    //(as a std::vector) and an index and returns the array element at that index 
    //(not a copy). Assume the index is valid, and the return value is const.
    return array[index];
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

    std::vector array1{29, 54, 66, 21, 69, 32};
    std::cout << "Question 4 largest index in  vector : " << get_index_of_largest_value(array1) << '\n';
    
    const std::vector<std::string>& array2{ "Paul" };
    std::string element2{ getElement(array2, 0) };
    std::cout << "Question 5 string element " << element2 << '\n';
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
