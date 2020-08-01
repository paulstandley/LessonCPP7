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


void lambda_captures()
{
    /*This code won’t compile. Unlike nested blocks,
    where any identifier defined in an outer block is accessible
    in the scope of the nested block, 
    lambdas can only access specific kinds of identifiers:
    global identifiers, entities that are known at compile time,
    and entities with static storage duration.
    search fulfills none of these requirements, so the lambda can’t see it.
    That’s what the capture clause is there for.

    The capture clause is used to (indirectly)
    give a lambda access to variables available in the surrounding scope 
    that it normally would not have access to. 
    All we need to do is list the entities we want to access from within the lambda
    as part of the capture clause. 
    In this case, we want to give our lambda access to the value of variable search, 
    so we add it to the capture clause:
    
    */

    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    // Ask the user what to search for.
    std::cout << "search for: ";

    std::string search{};
    std::cin >> search;

    // Capture @search                                vvvvvv
    auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
        // Search for @search rather than "nut".
        return (str.find(search) != std::string_view::npos); // Error: search not accessible in this scope
      }) };

    if (found == arr.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }
}


int main()
{
    lambdas_quiz();
    lambdas_quiz1();

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
