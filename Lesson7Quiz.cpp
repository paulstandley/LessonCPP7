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
    ff	No. ff‘s value depends on getValue, which might require the program to run.
    gg	Yes.
    hh	Yes. hh has static storage duration.
    iiii	Yes. iiii is a global variable.
    jjjj	Yes. jjjj is accessible in the entire file.
}
*/
    
/*
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
    return static_cast<int>(random_integer);
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
    //We’re going to write a little game with square numbers
    //(numbers which can be created by multiplying an integer with itself
    //(1, 4, 9, 16, 25, …)).

    //Ask the user to input 2 numbers,
    //the first is the square root of the number to start at,
    //the second is the amount of numbers to generate.

    //Generate a random integer from 2 to 4,
    //and square numbers in the range that was chosen by the user.

    //Multiply each square number by the random number.
    //You can assume that the user enters valid numbers.

    //The user has to calculate which numbers have been generated. The program checks if the user guessed correctly and removes the guessed number from the list. If the user guessed wrong, the game is over and the program prints the number that was closest to the user’s final guess, but only if the final guess was not off by more than 4.

    square_numbers();
}
*/

int getRandomInt(int min, int max)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    return std::uniform_int_distribution{ min, max }(mt);
}

// Generates @count numbers starting at @start*@start and multiplies
// every square number by multiplier.
list_type generateNumbers(int start, int count, int multiplier)
{
    list_type numbers(static_cast<list_type::size_type>(count));

    int i{ start };

    for (auto& number : numbers)
    {
        number = ((i * i) * multiplier);
        ++i;
    }

    return numbers;
}

// Asks the user to input start and amount, then calls @generateNumbers.
list_type generateUserNumbers(int multiplier)
{
    int start{};
    int count{};

    std::cout << "Start where? ";
    std::cin >> start;

    std::cout << "How many? ";
    std::cin >> count;

    // Input validation omitted. All functions assume valid input.

    return generateNumbers(start, count, multiplier);
}

int getUserGuess()
{
    int guess{};

    std::cout << "> ";
    std::cin >> guess;

    return guess;
}

// Searches for the value @guess in @numbers and removes it.
// Returns true if the value was found. False otherwise.
bool findAndRemove(list_type& numbers, int guess)
{
    if (auto found{ std::find(numbers.begin(), numbers.end(), guess) };
        found == numbers.end())
    {
        return false;
    }
    else
    {
        numbers.erase(found);
        return true;
    }
}

// Finds the value in @numbers that is closest to @guess.
int findClosestNumber(const list_type& numbers, int guess)
{
    return *std::min_element(numbers.begin(), numbers.end(), [=](int a, int b) {
        return (std::abs(a - guess) < std::abs(b - guess));
        });
}

void printTask(list_type::size_type count, int multiplier)
{
    std::cout << "I generated " << count
        << " square numbers. Do you know what each number is after multiplying it by "
        << multiplier << "?\n";
}

// Called when the user guesses a number correctly.
void printSuccess(list_type::size_type numbersLeft)
{
    std::cout << "Nice! ";

    if (numbersLeft == 0)
    {
        std::cout << "You found all numbers, good job!\n";
    }
    else
    {
        std::cout << numbersLeft << " number(s) left.\n";
    }
}

// Called when the user guesses a number that is not in the numbers.
void printFailure(const list_type& numbers, int guess)
{
    int closest{ findClosestNumber(numbers, guess) };

    std::cout << guess << " is wrong!";

    if (std::abs(closest - guess) <= config::maximumWrongAnswer)
    {
        std::cout << " Try " << closest << " next time.\n";
    }
    else
    {
        std::cout << '\n';
    }
}

// Returns false if the game is over. True otherwise.
bool playRound(list_type& numbers)
{
    int guess{ getUserGuess() };

    if (findAndRemove(numbers, guess))
    {
        printSuccess(numbers.size());

        return !numbers.empty();
    }
    else
    {
        printFailure(numbers, guess);
        return false;
    }
}

void runGameLoop()
{//BY NASCARDRIVER ON JANUARY 3RD, 2020
    int multiplier{ getRandomInt(config::multiplierMin, config::multiplierMax) };
    list_type numbers{ generateUserNumbers(multiplier) };
    printTask(numbers.size(), multiplier);
    while (playRound(numbers));
}


