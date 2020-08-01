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

    /*So how do captures actually work?

    While it might look like our lambda in the example above is directly accessing the
    value of main‘s search variable, this is not the case.
    Lambdas might look like nested blocks, but they work slightly differently
    (and the distinction is important).

    When a lambda definition is executed,
    for each variable that the lambda captures, 
    a clone of that variable is made (with an identical name) inside the lambda. 
    These cloned variables are initialized from the outer scope variables
    of the same name at this point.

    Thus, in the above example, when the lambda object is created, 
    the lambda gets its own cloned variable named search.
    This cloned search has the same value as main‘s search, 
    so it behaves like we’re accessing main‘s search, but we’re not.

    While these cloned variable have the same name, 
    they don’t necessarily have the same type as the original variable.
    
    Key insight

    The captured variables of a lambda are clones of the outer scope variables,
    not the actual variables.

    For advanced readers

    Although lambdas look like functions, 
    they’re actually objects that can be called like functions
    (these are called functors -- we’ll discuss how to create your own functors 
    from scratch in a future lesson).
    
    When the compiler encounters a lambda definition,
    it creates a custom object definition for the lambda.
    Each captured variable becomes a data member of the object.

    At runtime, when the lambda definition is encountered, 
    the lambda object is instantiated, 
    and the members of the lambda are initialized at that point.
    
    Captures default to const value

    By default, variables are captured by const value. 
    This means when the lambda is created, 
    the lambda captures a constant copy of the outer scope variable, 
    which means that the lambda is not allowed to modify them.
    In the following example, we capture the variable ammo and try to decrement it.

    */

    int ammo1{ 10 };

    // Define a lambda and store it in a variable called "shoot".
    auto shoot1{
      [ammo1]() {
            int val{ammo1};
            // Illegal, ammo was captured as a const copy.
            --val;
            //--ammo1;
            std::cout << "Pew! " << val << " shot(s) left.\n";
          }
    };

    // Call the lambda
    shoot1();

    std::cout << ammo1 << " shot(s) left\n";

    int ammo2{ 10 };

    auto shoot2{
        // Added mutable after the parameter list.
        [ammo2]() mutable {
            // We're allowed to modify ammo now
            --ammo2;

            std::cout << "Pew! " << ammo2 << " shot(s) left.\n";
          }
    };

    shoot2();
    shoot2();
    std::cout << ammo2 << " shot(s) left\n";

    /*While this now compiles, there’s still a logic error. 
    What happened? When the lambda was called, the lambda captured a copy of ammo. 
    When the lambda decremented ammo from 10 to 9 to 8, 
    it decremented its own copy, not the original value.

    Note that the value of ammo is preserved across calls to the lambda!
    
    */

}


int main()
{
    lambda_captures();


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
