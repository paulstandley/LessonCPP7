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
#include "Header.h"


double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
    assert(gravity > 0.0); 
    // The object won't reach the ground unless there is positive gravity.
    if (initialHeight <= 0.0)
    {
        // The object is already on the ground. Or buried.
        return 0.0;
    }
    return std::sqrt((2.0 * initialHeight) / gravity);
}

void assert_and_static_assert()
{
    //Using a conditional statement to detect a violated assumption,
    //along with printing an error message and terminating the program,
    //is such a common response to problems that C++ provides a shortcut 
    //method for doing this. This shortcut is called an assert.

    //An assert statement is a preprocessor macro that evaluates
    //a conditional expression at runtime. 
    //If the conditional expression is true,
    //the assert statement does nothing.
    //If the conditional expression evaluates to false,
    //an error message is displayed and the program is terminated.
    //This error message contains the conditional expression that failed, 
    //along with the name of the code file and the line number of the assert.
    //This makes it very easy to tell not only what the problem was,
    //but where in the code the problem occurred.
    //This can help with debugging efforts immensely.

    std::cout << "Took " 
        << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

    //When the program calls calculateTimeUntilObjectHitsGround(100.0, -9.8),
    //the program prints a message similar to this:
    //dropsimulator: src / main.cpp : 6 : double calculateTimeUntilObjectHitsGround(double, 
    //double) : Assertion `gravity > 0.0' failed.

    //We encourage you to use assert statements liberally throughout your code.
    //Making your assert statements more descriptive

    //assert(found && "Car could not be found in database");
    //Here’s why this works: A C-style string always evaluates to boolean true.
    //So if found is false, false && true = false. If found is true, 
    //true && true = true. 
    //Thus, logical AND-ing a string doesn’t impact the evaluation of the assert.
    //However, when the assert triggers, 
    //the string will be included in the assert message:

    //NDEBUG and other considerations

    //The assert() function comes with a small performance cost that is incurred
    //each time the assert condition is checked. 
    //Furthermore, asserts should (ideally) never be encountered in production code 
    //(because your code should already be thoroughly tested). 
    //Consequently, many developers prefer that asserts are only active in debug builds.
    //C++ comes with a way to turn off asserts in production code: #define NDEBUG.

    //#define NDEBUG
    // all assert() calls will now be ignored to the end of the file

    //Some IDEs set NDEBUG by default as part of the project settings
    //for release configurations. 
    //For example, in Visual Studio, 
    //the following preprocessor definitions are set at the project level: 
    //WIN32;NDEBUG;_CONSOLE. 
    //If you’re using Visual Studio and want your asserts to trigger in release builds,
    //you’ll need to remove NDEBUG from this setting.

    //Do note that the exit() functionand assert() function(if it triggers)
    //terminate the program immediately,
    //without a chance to do any further cleanup(e.g.close a file or database).
    //Because of this, they should be used judiciously
    //(only in cases where corruption isn’t likely to occur if the program terminates
    //unexpectedly).

    //There’s another type of assert called static_assert. static_assert takes the form

    //static_assert(sizeof(long) == 8, "long must be 8 bytes");
    //static_assert(sizeof(int) == 4, "int must be 4 bytes");

    //A few notes. Because static_assert is evaluated by the compiler, 
    //the conditional part of a static_assert must be able to be evaluated
    //at compile time. Because static_assert is not evaluated at runtime, 
    //static_assert statements can also be placed anywhere in the code file 
    //(even in global space).

    //In C++11, a diagnostic message must be supplied as the second parameter.
    //Since C++17, providing a diagnostic message is optional.

    //Exceptions

    //C++ provides one more method for detectingand handling errors known as exception
    //handling.The basic idea is that when an error occurs,
    //the error is “thrown”.
    //If the current function does not “catch” the error, 
    //the caller of the function has a chance to catch the error.
    //If the caller does not catch the error,
    //the caller’s caller has a chance to catch the error.
    //The error progressively moves up the stack until it is either caughtand handled,
    //or until main() fails to handle the error.
    //If nobody handles the error, the program typically terminates
    //with an exception error.
}


int main()
{
    assert_and_static_assert();
    

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
