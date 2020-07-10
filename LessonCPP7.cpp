#include "pch.h"
#include <algorithm> // std::shuffle sort
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include <iterator> // for std::size
#include "Header.h"


void question4(const char* stringy2)
{
    //Write a function to print a C-style string character by character. 
    //Use a pointer to step through each character of the string 
    //and print that character. Stop when you hit the null terminator. 
    //Write a main function that tests the function with the 
    //string literal “Hello, world!”.
    char stringy1[]{ "Hello, world!" };
    const int length{ static_cast<int>(std::size(stringy1)) };
    //const int length{ sizeof(myString) / sizeof(myString[0]) }; 
    //use instead if not C++17 capable
    for (int i = 0; i < length; i++)
    {
        std::cout << stringy1[i] << ' ';
    }
    std::cout << std::endl;
    
    //const char length1{ static_cast<int>(*stringy2) };
    while (*stringy2 != '\0')
    {
        std::cout << *stringy2;// print the current character
        ++stringy2;// and point stringy2 at the next character
    }
    std::cout << std::endl;
}

int main()
{
    question4("Hello world!");

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
