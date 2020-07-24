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



int factorial001(int num)
{
    if (num <= 0)
        return 1;
    else
        return factorial001(num - 1) * num;
}

void recursion_quiz()
{
    //1) A factorial of an integer N (written N!) 
    //is defined as the product (multiplication) 
    //of all the numbers between 1 and N (0! = 1). 
    //Write a recursive function called factorial
    //that returns the factorial of the input. 
    //Test it with the first 7 factorials.

    //Hint: Remember that(x * y) = (y * x), 
    //so the product of all the numbers between 1 and N
    //is the same as the product of all the numbers between N and 1.

    for (int count = 0; count < 7; ++count)
        std::cout << factorial001(count) << '\n';
    std::cout << '\n';

}


int main()
{
    recursion_quiz();
    

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
