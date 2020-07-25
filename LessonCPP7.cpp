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



void printBinary(unsigned int n)
{// h/t to reader Donlod for this solution
    if (n > 1) // we only recurse if n > 1, so this is our termination case for n == 0
        printBinary(n / 2);

    std::cout << n % 2;
}

void print_binary(int x)
{// h/t to reader Gapo for this solution
    // Termination case
    if (x == 0)
        return;

    // Recurse to the next bit
    print_binary(x / 2);

    // Print out the remainders (in reverse order)
    std::cout << x % 2;
}

int individual_digit_in_the_integer(int num)
{// if one digit return digit, else divide num by 10 then add modulo 10 
    if (num < 10)
       return num;
    else
       return individual_digit_in_the_integer(num / 10) + num % 10;
}

int factorial001(int num)
{// if the number is 1 or less return 1 else number minus one times the number
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

    //2) Write a recursive function that takes an integer as input and returns
    //the sum of each individual digit in the integer (e.g. 357 = 3 + 5 + 7 = 15).
    //Print the answer for input 93427 (which is 25).
    //Assume the input values are positive.

    std::cout << individual_digit_in_the_integer(93427) << '\n';

    //3a) This one is slightly trickier. 
    //Write a program that asks the user to enter a positive integer,
    //and then uses a recursive function to print out the binary representation 
    //for that number.

    int posint;
    std::cout << "Enter a positive integer: ";
    std::cin >> posint;
    print_binary(posint);

    //3b) Update your code from 3a to handle the case where the user may enter
    //0 or a negative number.
    //Hint: You can turn a negative integer into a positive one
    //by converting it to an unsigned integer. 
    //These have identical bit representations 
    //(the type is used to determine how to interpret the number into decimal).

    printBinary(posint);
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
