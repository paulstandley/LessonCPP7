#include "pch.h"
#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include "Header.h"

void std_reduce()
{
    std::array arr{ 1, 2, 3, 4 };
    std::cout << std::reduce(arr.begin(), arr.end()) << '\n'; // 10
    // If you can't use std::reduce, use std::accumulate. The 0 is the initial value
    // of the result: 0 + (((1 + 2) + 3) + 4)
    std::cout << std::accumulate(arr.begin(), arr.end(), 0) << '\n'; // 10
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(arr.begin(), arr.end(), mt);
    for (int i : arr)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std_reduce();

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
