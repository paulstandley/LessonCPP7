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
#include "Header.h"


static bool containsNutL(std::string_view str) // static means internal linkage in this context
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. Otherwise it returns the index where the substring occurs
    // in str.
    return (str.find("nut") != std::string_view::npos);
}

void repeat(int repetitions, const std::function<void(int)>& fn)
{// We don't know what fn will be. 
    //std::function works with regular functions and lambdas.
    for (int i{ 0 }; i < repetitions; ++i)
    {
        fn(i);
    }
}

void lambdas_anonymous_functions()
{
    /*Lambdas

    A lambda expression (also called a lambda or closure)
    allows us to define an anonymous function inside another function.
    The nesting is important, as it allows us both to avoid namespace naming pollution,
    and to define the function as close to where it is used as possible 
    (providing additional context).

    The syntax for lambdas is one of the weirder things in C++, 
    and takes a bit of getting used to. Lambdas take the form:

    [ captureClause ] ( parameters ) -> returnType
    {
        statements;
    }
    
    The capture clause and parameters can both be empty if they are not needed.

    The return type is optional, and if omitted, auto will be assumed
    (thus using type inference used to determine the return type).
    While we previously noted that type inference for function return 
    types should be avoided, in this context, it’s fine to use
    (because these functions are typically so trivial).

      []() {}; // defines a lambda with no captures, no parameters, and no return type
    
    */

    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    // Define the function right where we use it.
    auto found{ std::find_if(arr.begin(), arr.end(),
                             [](std::string_view str)
        // here's our lambda, no capture clause
                             {
                               return (str.find("nut") != std::string_view::npos);
                             }) };

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    /*Note how similar our lambda is to our containsNut function. 
    They both have identical parameters and function bodies. 
    The lambda has no capture clause 
    (we’ll explain what a capture clause is in the next lesson)
    because it doesn’t need one. 
    And we’ve omitted the trailing return type in the lambda (for conciseness), 
    but since operator!= returns a bool, our lambda will return a bool too.
    
    Type of a lambda

    In the above example, we defined a lambda right where it was needed. 
    This use of a lambda is sometimes called a function literal.

    However, writing a lambda in the same line as it’s used can sometimes
    make code harder to read.
    Much like we can initialize a variable with a literal value
    (or a function pointer) for use later,
    we can also initialize a lambda variable with a lambda definition 
    and then use it later. 
    A named lambda along with a good function name can make code easier to read.
    
    As it turns out, lambdas don’t have a type that we can explicitly use. 
    When we write a lambda, the compiler generates a unique type just for the lambda
    that is not exposed to us.

    In actuality, lambdas aren’t functions 
    (which is part of how they avoid the limitation of C++ not supporting nested
    functions). They’re a special kind of object called a functor.
    Functors are objects that contain an overloaded operator()
    that make them callable like a function

    Although we don’t know the type of a lambda,
    there are several ways of storing a lambda for use post-definition.
    If the lambda has an empty capture clause,
    we can use a regular function pointer.
    In the next lesson, we introduce lambda captures,
    a function pointer won’t work anymore at that point.
    However, std::function can be used for lambdas even if they are 
    capturing something.

    */

    // A regular function pointer. Only works with an empty capture clause.
    double (*addNumbers1)(double, double) {
        [](double a, double b) {
            return (a + b);
        }
    };

    std::cout << addNumbers1(1, 2) << '\n';

    // Using std::function. The lambda could have a non-empty capture clause (Next lesson).
    std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
      [](double a, double b) {
        return (a + b);
      }
    };

    std::cout << addNumbers2(3, 4) << '\n';

    // Using auto. Stores the lambda with its real type.
    auto addNumbers3{
      [](double a, double b) {
        return (a + b);
      }
    };

    std::cout << addNumbers3(5, 6) << '\n';

    /*The only way of using the lambda’s actual type is by means of auto.
    auto also has the benefit of having no overhead compared to std::function.

    Unfortunately, we can’t always use auto.
    In cases where the actual lambda is unknown 
    (e.g. because we’re passing a lambda to a function as a parameter and the 
    caller determines what lambda will be passed in),
    we can’t use auto. In such cases, std::function should be used.
    
    */

    repeat(3, [](int i) {
        std::cout << i << '\n';
        });

    /*Rule

    Use auto when initializing variables with lambdas, 
    and std::function if you can’t initialize the variable with the lambda.

    Generic lambdas

    For the most part, lambda parameters work by the same rules as regular function parameters.

    One notable exception is that since C++14 we’re allowed to use auto for parameters 
    (note: in C++20, regular functions will be able to use auto for parameters too).
    When a lambda has one or more auto parameter, 
    the compiler will infer what parameter types are needed from the calls 
    to the lambda.

    Because lambdas with one or more auto parameter can potentially work with a wide variety of types, they are called generic lambdas.

    For advanced readers

    When used in the context of a lambda,
    auto is just a shorthand for a template parameter.
    
    */

    std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // Search for two consecutive months that start with the same letter.
    auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                        [](const auto& a, const auto& b) {
                                          return (a[0] == b[0]);
                                        }) };

    // Make sure that two months were found.
    if (sameLetter != months.end())
    {
        // std::next returns the next iterator after sameLetter
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
            << " start with the same letter\n";
    }

    /*In the above example, 
    we use auto parameters to capture our strings by const reference.
    Because all string types allow access to their individual characters via operator[],
    we don’t need to care whether the user is passing in a std::string, 
    C-style string, or something else.
    This allows us to write a lambda that could accept any of these, 
    meaning if we change the type of months later,
    we won’t have to rewrite the lambda.
    
    */

    // Count how many months consist of 5 letters
    auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                         [](std::string_view str) {
                                           return (str.length() == 5);
                                         }) };

    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

    /*In this example, using auto would infer a type of const char*.
    C-style strings aren’t easy to work with (apart from using operator[]).
    In this case, we prefer to explicitly define the parameter as a std::string_view, 
    which allows us to work with the underlying data much more easily
    (e.g. we can ask the string view for its length, even if the user 
    passed in a C-style array).
    
    Generic lambdas and static variables

    One thing to be aware of is that a unique lambda will be generated for each
    different type that auto resolves to.
    The following example shows how one generic lambda turns into two distinct lambdas

    */

    // Print a value and count how many times @print has been called.
    auto printlam{
      [](auto value) {
        static int callCount{ 0 };
        std::cout << callCount++ << ": " << value << '\n';
      }
    };

    printlam("hello"); // 0: hello
    printlam("world"); // 1: world

    printlam(1); // 0: 1
    printlam(2); // 1: 2

    printlam("ding dong"); // 2: ding dong

    /*In the above example, we define a lambda and then call it with two 
    different parameters (a string literal parameter,
    and an integer parameter). 
    This generates two different versions of the lambda
    (one with a string literal parameter, and one with an integer parameter).

    Most of the time, this is inconsequential.
    However, note that if the generic lambda uses static duration variables, 
    those variables are not shared between the generated lambdas.

    We can see this in the example above,
    where each type (string literals and integers) has its own unique count!
    Although we only wrote the lambda once, 
    two lambdas were generated -- and each has its own version of callCount. 
    To have a shared counter between the two generated lambdas, 
    we’d have to define a variable outside of the lambda. 
    For now, this means defining the variable even outside of the 
    function the lambda is defined in. 
    In the above example, this means adding a global variable.
    We’ll be able to avoid the global variable after talking about 
    lambda captures in the next lesson.

    Return type deduction and trailing return types

    If return type deduction is used,
    a lambda’s return type is deduced from the return-statements inside the lambda. 
    If return type inference is used,
    all return statements in the lambda must return the same type
    (otherwise the compiler won’t know which one to prefer).

    In the case where we’re returning different types, we have two options:

    1) Do explicit casts to make all the return types match, or

    2) explicitly specify a return type for the lambda, 
    and let the compiler do implicit conversions
    
    */

    // note: explicitly specifying this returns a double
    auto dividelam{ [](int x, int y, bool bInteger) -> double {
      if (bInteger)
        return x / y; // will do an implicit conversion to double
      else
        return static_cast<double>(x) / y;
    } };

    std::cout << dividelam(3, 2, true) << '\n';
    std::cout << dividelam(3, 2, false) << '\n';

    /*That way, if you ever decide to change the return type,
    you (usually) only need to change the lambda’s return type,
    and not touch the lambda body.

    Standard library function objects

    For common operations (e.g. addition, negation, or comparison)
    you don’t need to write your own lambdas,
    because the standard library comes with many basic callable objects
    that can be used instead.
    These are defined in the <functional> header.
    
    */

    std::array arrlam{ 13, 90, 99, 5, 40, 80 };
    // Pass std::greater to std::sort
    std::sort(arrlam.begin(), arrlam.end(), std::greater{});
    // note: need curly braces to instantiate object
    for (int i : arrlam)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    /*Conclusion

    Lambdas and the algorithm library may seem unnecessarily complicated when compared
    to a solution that uses a loop. However, 
    this combination can allow some very powerful operations in just a few lines
    of code, and can be more readable than writing your own loops.
    On top of that, the algorithm library features powerful 
    and easy-to-use parallelism, which you won’t get with loops. 
    Upgrading source code that uses library functions is easier than upgrading 
    code that uses loops.

    Lambdas are great, but they don’t replace regular functions for all cases.
    Prefer regular functions for non-trivial and reusable cases.
    
    */

}


int main()
{
    lambdas_anonymous_functions();
    

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
