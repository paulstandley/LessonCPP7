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



/*

int iiii{};
static int jjjj{};

int getValuelamb()
{
    return 0;
}

void lambdas_captures_quiz()
{
    int aa{};
    constexpr int bb{};
    static int cc{};
    static constexpr int dd{};
    const int ee{};
    const int ff{ getValuelamb() };
    static const int gg{};
    static const int hh{ getValuelamb() };

    []() {
        // Try to use the variables without explicitly capturing them.
        //aa;
        bb;
        cc;
        dd;
        ee;
        //ff;
        gg;
        hh;
        iiii;
        jjjj;
    }();

    /*
    aa	No. aa has automatic storage duration.
    bb	Yes. bb is usable in a constant expression.
    cc	Yes. cc has static storage duration.
    dd	Yes.
    ee	Yes. ee is usable in a constant expression.
    ff	No. ff�s value depends on getValue, which might require the program to run.
    gg	Yes.
    hh	Yes. hh has static storage duration.
    iiii	Yes. iiii is a global variable.
    jjjj	Yes. jjjj is accessible in the entire file.
}
*/
    
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
    // random-number engine used (Mersenne-Twister)
    std::uniform_int_distribution<int> uni(min, max);
    // guaranteed unbiased
    auto random_integer = uni(rng);
    return random_integer;
}

bool start_square_numbers()
{
    std::cout << "Do you want to play a game y or n ";
    char yayornay{};
    std::cin >> yayornay;
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    if (static_cast<int>(yayornay) == 89 || static_cast<int>(yayornay) == 121)
        return true;
    else
        return false;
}

void square_numbers()
{
    while (true)
    {
        if (start_square_numbers())
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
                std::cout << i << " ";
            }
            std::cout << '\n';
        }
        else
        {
            break;
        }
    }
}

void lambda_7_3()
{
    /*We�re going to write a little game with square numbers
    (numbers which can be created by multiplying an integer with itself
    (1, 4, 9, 16, 25, �)).

    Ask the user to input 2 numbers,
    the first is the square root of the number to start at,
    the second is the amount of numbers to generate.

    Generate a random integer from 2 to 4,
    and square numbers in the range that was chosen by the user.

    Multiply each square number by the random number.
    You can assume that the user enters valid numbers.

    The user has to calculate which numbers have been generated. The program checks if the user guessed correctly and removes the guessed number from the list. If the user guessed wrong, the game is over and the program prints the number that was closest to the user�s final guess, but only if the final guess was not off by more than 4.

    */

    square_numbers();

}


