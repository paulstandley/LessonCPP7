#include "pch.h"
#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include "Header.h"





enum Items
{
    potions = 2,
    torches = 5,
    arrows = 10
};

int countTotalItems(const int value)
{
    return value;
}

void question1()
{
    //Pretend you’re writing a game where the player can hold 3 types of items: 
    //health potions, torches, and arrows. 
    //Create an enum to identify the different types of items, 
    //and an std::array to store the number of each item the player is carrying 
    //(The enumerators are used as indexes of the array). 
    //The player should start with 2 health potions, 5 torches, and 10 arrows.
    //Write a function called countTotalItems() 
    //that returns how many items the player has in total. 
    //Have your main() function print the output of countTotalItems() 
    //as well as the number of torches.

    std::array <int, 3>carrying{};
    carrying[0] = Items::potions;
    carrying[1] = Items::torches;
    carrying[2] = Items::arrows;
    
    const int reduceint = std::reduce(
        std::execution::par, carrying.cbegin(), carrying.cend());
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << carrying[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "The player has " << countTotalItems(reduceint) << " total items." << '\n';
}


int main()
{
    question1();
    examplecode();

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
