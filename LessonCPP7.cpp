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


using list_type = std::vector<int>;

namespace config
{
    constexpr int multiplierMin{ 2 };
    constexpr int multiplierMax{ 4 };
    constexpr int maximumWrongAnswer{ 4 };
}

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


int main()
{
    runGameLoop();


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
