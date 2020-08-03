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
#include <cstdlib> // for std::exit()
#include <limits>
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <cstdarg> // needed to use ellipsis
#include <string_view>
#include <string>
#include "Header.h"


//std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

int get_number_from_user()
{
    int return_value{};
    while (true)
    {
        std::cin >> return_value;
        //handle case where user entered a non-integer
        if (std::cin.fail())
        {
            std::cout << "Please enter an integer ";
            std::cin.clear(); // reset any error flags
            std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer
        }
        else
        {
            std::cin.clear(); // reset any error flags
            std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer
            return return_value;
        }
    }
}

int random_number_in_range(int min = 1, int max = 10)
{
    //Generate a random integer from min to max
    std::random_device rd;
    // only used once to initialise (seed) engine
    std::mt19937 rng(rd());
    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max);
    // guaranteed unbiased
    auto random_integer = uni(rng);
}


void square_numbers()
{
    //the first is the square root of the number to start at
    std::cout << "Start where? ";
    int start_num{ get_number_from_user() };
    std::cout << start_num << '\n';

    //the second is the amount of numbers to generate. 
    std::cout << "How many?  ";
    int num{ get_number_from_user() };
    std::cout << num << '\n';
    
    int rand{ random_number_in_range(2, 4) };

    for (size_t i = 0; i < start_num; i++)
    {

    }

}


void lambda_7_3()
{
    /*We’re going to write a little game with square numbers 
    (numbers which can be created by multiplying an integer with itself
    (1, 4, 9, 16, 25, …)).
    
    Ask the user to input 2 numbers, 
    the first is the square root of the number to start at, 
    the second is the amount of numbers to generate.

    Generate a random integer from 2 to 4,
    and square numbers in the range that was chosen by the user.

    Multiply each square number by the random number. 
    You can assume that the user enters valid numbers.

    The user has to calculate which numbers have been generated. The program checks if the user guessed correctly and removes the guessed number from the list. If the user guessed wrong, the game is over and the program prints the number that was closest to the user’s final guess, but only if the final guess was not off by more than 4.
    
    */

    square_numbers();

    

}


int main()
{
    lambda_7_3();

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
