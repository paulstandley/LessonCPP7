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


struct Carlam
{
    std::string make{};
    std::string model{};
};

// returns a lambda
auto makeWalrus(const std::string& name)
{
    // Capture name by reference and return the lambda.
    return [&]() {
        std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
    };
}

void invoke(const std::function<void(void)>& fn)
{
    fn();
}

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

    Capture by reference

    Much like functions can change the value of arguments passed by reference,
    we can also capture variables by reference to allow our lambda
    to affect the value of the argument.

    To capture a variable by reference,
    we prepend an ampersand (&) to the variable name in the capture. 
    Unlike variables that are captured by value,
    variables that are captured by reference are non-const,
    unless the variable they’re capturing is const.

    Capture by reference should be preferred over capture by value
    whenever you would normally prefer passing an argument to a function
    by reference (e.g. for non-fundamental types).
    
    */

    int ammo3{ 10 };
    auto shoot3{
        // We don't need mutable anymore
        [&ammo3]() { // &ammo means ammo is captured by reference
          // Changes to ammo will affect main's ammo
          --ammo3;
          std::cout << "Pew! " << ammo3 << " shot(s) left.\n";
        }
    };
    shoot3();
    std::cout << ammo3 << " shot(s) left\n";

    //Now, let’s use a reference capture to count how many
    //comparisons std::sort makes when it sorts an array.

    std::array<Carlam, 3> cars{ { { "Volkswagen", "Golf" },
                           { "Toyota", "Corolla" },
                           { "Honda", "Civic" } } };

    int comparisons{ 0 };

    std::sort(cars.begin(), cars.end(),
        // Capture @comparisons by reference.
        [&comparisons](const auto& a, const auto& b) {
            // We captured comparisons by reference. We can modify it without "mutable".
            ++comparisons;

            // Sort the cars by their make.
            return (a.make < b.make);
        });

    std::cout << "Comparisons: " << comparisons << '\n';

    for (const auto& car : cars)
    {
        std::cout << car.make << ' ' << car.model << '\n';
    }

    //Capturing multiple variables

    //Multiple variables can be captured by separating them with a comma.
    //This can include a mix of variables captured by value or by reference :

    //int health{ 33 };
    //int armor{ 100 };
    //std::vector<CEnemy> enemies{};
    // Capture health and armor by value, and enemies by reference.
    //[health, armor, &enemies]() {};

    /*Default captures

    Having to explicitly list the variables you want to capture can be burdensome.
    If you modify your lambda, you may forget to add or remove captured variables.
    Fortunately, we can enlist the compiler’s help to auto-generate a list of variables 
    we need to capture.

    A default capture (also called a capture-default) captures all variables 
    that are mentioned in the lambda. 
    Variables not mentioned in the lambda are not captured
    if a default capture is used.

    To capture all used variables by value, use a capture value of =.
    To capture all used variables by reference, use a capture value of &
    
    */

    std::array areas7{ 100, 25, 121, 40, 56 };

    int width7{};
    int height7{};

    std::cout << "Enter width and height: ";
    std::cin >> width7 >> height7;

    auto found7{ std::find_if(areas7.begin(), areas7.end(),
                             [=](int knownArea) { // will default capture width and height by value
                               return (width7 * height7 == knownArea); // because they're mentioned here
                             }) };

    if (found7 == areas7.end())
    {
        std::cout << "I don't know this area :(\n";
    }
    else
    {
        std::cout << "Area found :)\n";
    }

    /*int health{ 33 };
    int armor{ 100 };
    std::vector<CEnemy> enemies{};
 
    // Capture health and armor by value, and enemies by reference.
    [health, armor, &enemies](){};
 
    // Capture enemies by reference and everything else by value.
    [=, &enemies](){};
 
    // Capture armor by value and everything else by reference.
    [&, armor](){};
 
    // Illegal, we already said we want to capture everything by reference.
    [&, &armor](){};
 
    // Illegal, we already said we want to capture everything by value.
    [=, armor](){};
 
    // Illegal, armor appears twice.
    [armor, &health, &armor](){};
 
    // Illegal, the default capture has to be the first element in the capture group.
    [armor, &](){};

    Defining new variables in the lambda-capture

    Sometimes we want to capture a variable with a slight modification
    or declare a new variable that is only visible in the scope of the lambda.
    We can do so by defining a variable in the lambda-capture without specifying
    its type.
    
    */

    std::array areas5{ 100, 25, 121, 40, 56 };

    int width5{};
    int height5{};

    std::cout << "Enter width and height: ";
    std::cin >> width5 >> height5;

    // We store areas, but the user entered width and height.
    // We need to calculate the area before we can search for it.
    auto found5{ std::find_if(areas5.begin(), areas5.end(),
        // Declare a new variable that's visible only to the lambda.
        // The type of userArea is automatically deduced to int.
        [userArea{ width5 * height5 }](int knownArea) {
          return (userArea == knownArea);
        }) };

    if (found5 == areas5.end())
    {
        std::cout << "I don't know this area :(\n";
    }
    else
    {
        std::cout << "Area found :)\n";
    }

    /*userArea will only be calculated once when the lambda is defined. 
    The calculated area is stored in the lambda object and is the same for every call.
    If a lambda is mutable and modifies a variable that was defined in the capture,
    the original value will be overridden.

    Best practice

    Only initialize variables in the capture if their value is short and their type
    is obvious. Otherwise it’s best to define the variable outside of the lambda
    and capture it.
    
    Dangling captured variables

    Variables are captured at the point where the lambda is defined.
    If a variable captured by reference dies before the lambda, 
    the lambda will be left holding a dangling reference.

    */

    // Create a new walrus whose name is Roofus.
    // sayName is the lambda returned by makeWalrus.
    auto sayName{ makeWalrus("Roofus") };
    // Call the lambda function that makeWalrus returned.
    sayName();

    /*The call to makeWalrus creates a temporary std::string from the string literal
    “Roofus”. 
    The lambda in makeWalrus captures the temporary string by reference. 
    The temporary string dies when makeWalrus returns, 
    but the lambda still references it. 
    Then when we call sayName, the dangling reference is accessed, 
    causing undefined behavior.

    Note that this also happens if name is passed to makeWalrus by value. 
    The variable name still dies at the end of makeWalrus,
    and the lambda is left holding a dangling reference.

    Warning

    Be extra careful when you capture variables by reference, especially with a 
    default reference capture. 
    The captured variables must outlive the lambda.
    If we want the captured name to be valid when the lambda is used,
    we need to capture it by value instead 
    (either explicitly or using a default-capture by value).

    Unintended copies of mutable lambdas

    Because lambdas are objects, they can be copied. 
    In some cases, this can cause problems.
    
    */

    int ii{ 0 };
    // Create a new lambda named count
    auto count{ [ii]() mutable {
      std::cout << ++ii << '\n';
    } };

    count(); // invoke count
    auto otherCount{ count }; // create a copy of count
    // invoke both count and the copy
    count();
    otherCount();

    /*Rather than printing 1, 2, 3, the code prints 2 twice. 
    When we created otherCount as a copy of count,
    we created a copy of count in its current state.
    count‘s i was 1, so otherCount‘s i is 1 as well. 
    Since otherCount is a copy of count, they each have their own i.
    
    */

    int i{ 0 };

    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {
      std::cout << ++i << '\n';
    } };

    invoke(count);
    invoke(count);
    invoke(count);

    /*This exhibits the same problem as the prior example in a more obscure form. 
    When std::function is created with a lambda,
    the std::function internally makes a copy of the lambda object.
    Thus, our call to fn() is actually being executed on the copy of our lambda, 
    not the actual lambda.

    If we need to pass a mutable lambda, and want to avoid the possibility of
    inadvertent copies being made, there are two options. 
    One option is to use a non-capturing lambda instead -- in the above case,
    we could remove the capture and track our state using a static local variable instead. 
    
    But static local variables can be difficult to keep track of and make our code 
    less readable. 
    A better option is to prevent copies of our lambda from being 
    made in the first place.
    But since we can’t affect how std::function 
    (or other standard library functions or objects) are implemented, 
    how can we do this?

    Fortunately, C++ provides a convenient type 
    (as part of the <functional> header) called std::ref that allows us to 
    pass a normal type as if it were a reference.

    By wrapping our lambda in a std::ref,
    whenever anybody tries to make a copy of our lambda, 
    they’ll make a copy of the reference instead, 
    which will copy the reference rather than the actual object.

    Here’s our updated code using std::ref:
    
    */

    int i8{ 0 };

    // Increments and prints its local copy of @i.
    auto count8{ [i8]() mutable {
      std::cout << ++i8 << '\n';
    } };

    // std::ref(count) ensures count is treated like a reference
    // thus, anything that tries to copy count will actually copy the reference
    // ensuring that only one count exists
    invoke(std::ref(count8));
    invoke(std::ref(count8));
    invoke(std::ref(count8));

    /*Note that the output doesn’t change even if invoke takes fn by value.
    std::function doesn’t create a copy of the lambda if we create it with std::ref.

    Rule

    Standard library functions may copy function objects
    (reminder: lambdas are function objects). 
    If you want to provide lambdas with mutable captured variables,
    pass them by reference using std::ref.

    Best practice

    Try to avoid lambdas with states altogether. 
    Stateless lambdas are easier to understand and don’t suffer from the above issues,
    as well as more dangerous issues that arise when you add parallel execution.
    
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
