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
#include "Header.h"

int overloaded(int value)
{
    return value * value;
}

double overloaded(double value)
{
    return value * value - 1;
}

void print(unsigned int value)
{
    std::cout << "Unsigned int " << value << '\n';
}

void print(float value)
{
    std::cout << "Flote " << value << '\n';
}

void function_overloading()
{
    std::cout << "Overloaded int " << overloaded(8) << " double " << overloaded(0.3) << '\n';
    //1) First, C++ tries to find an exact match.
    //This is the case where the actual argument exactly matches the 
    //parameter type of one of the overloaded functions

    //2) If no exact match is found, 
    //C++ tries to find a match through promotion type conversion and casting,
    //we covered how certain types can be automatically promoted via internal 
    //type conversion to other types

    //Char, unsigned char, and short is promoted to an int.
    //Unsigned short can be promoted to int or unsigned int, depending on the size of an int
    //Float is promoted to double
    //Enum is promoted to int

    //3) If no promotion is possible, 
    //C++ tries to find a match through standard conversion. 
    //Standard conversions include:

    //Any numeric type will match any other numeric type, including unsigned(e.g. int to float)
    //Enum will match the formal type of a numeric type(e.g. enum to float)
    //Zero will match a pointer typeand numeric type(e.g. 0 to char*, or 0 to float)
    //A pointer will match a void pointer

    //4) Finally, C++ tries to find a match through user-defined conversion. 
    //Although we have not covered classes yet, classes (which are similar to structs)
    //can define conversions to other types that can be implicitly applied
    //to objects of that class. For example, 
    //we might define a class X and a user-defined conversion to int.

    // Ambiguous matches

    print(static_cast<unsigned int>('a'));
    //C++ can not find an exact match. 
    //It tries promoting ‘a’ to an int, but there is no print(int) either. 
    //Using a standard conversion, it can convert ‘a’ to both an unsigned int
    //and a floating point value. 
    //Because all standard conversions are considered equal,
    //this is an ambiguous match.

    print(0u);
    //print(0) is similar. 0 is an int, and there is no print(int).
    //It matches both calls via standard conversion.

    print(static_cast<float>(3.14159));
    //print(3.14159) might be a little surprising, 
    //as most programmers would assume it matches print(float). 
    //But remember that all literal floating point values are doubles 
    //unless they have the ‘f’ suffix. 3.14159 is a double, 
    //and there is no print(double). Consequently, 
    //it matches both calls via standard conversion.

    //Ambiguous matches are considered a compile-time error. 
    //Consequently, an ambiguous match needs to be disambiguated before your 
    //program will compile. 
    //There are a few ways to resolve ambiguous matches

    //Conclusion
    //Function overloading can lower a program’s complexity significantly 
    //while introducing very little additional risk. 
    //Although this particular lesson is longand may seem somewhat complex
    //(particularly the matching rules), 
    //in reality function overloading typically works transparentlyand 
    //without any issues.
    //The compiler will flag all ambiguous cases, 
    //and they can generally be easily resolved.
    // Rule: use function overloading to make your program simpler.
}

void optional_parameter(int x, int y)
{// 10 is the default argument, y is now an optional parameter
    std::cout << "x = " << x << '\n' << "y = " << y << '\n';
}

void multiple_default_arguments(int x, int y, int z)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

void default_arguments()
{// y will use default argument 10
    optional_parameter(1);
    optional_parameter(3, 4);
    //Default arguments are an excellent option when the function 
    //needs a value that the user may or may not want to override

    multiple_default_arguments(1, 2, 3);
    multiple_default_arguments(1, 2);
    multiple_default_arguments(1);
    multiple_default_arguments();

    //Best practice is to declare the default argument in the forward declaration 
    //and not in the function definition,
    //as the forward declaration is more likely to be seen by other files 
    //(particularly if it’s in a header file).

    //Default arguments and function overloading
    //Functions with default arguments may be overloaded.
    //void print(std::string string);
    //void print(char ch = ' ')
    //However, it is important to note that optional parameters do 
    //NOT count towards the parameters that make the function unique.
    //Consequently, the following is not allowed:
    //void printValues(int x);
    //void printValues(int x, int y = 20);

    //Default arguments provide a useful mechanism to specify parameters
    //that the user may optionally provide values for. 
    //They are frequently used in C++
}

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

void function_pointers()
{
    std::cout << foo << '\n';
    // we meant to call foo(), but instead we're printing foo itself!
    std::cout << reinterpret_cast<void*>(foo) << '\n';
    // Tell C++ to interpret function foo as a void pointer

    // fcnPtr is a pointer to a function that takes no arguments and returns an integer
    //int (*funcptr)();
    //The parenthesis around *fcnPtr are necessary for precedence reasons, as int *fcnPtr()
    //would be interpreted as a forward declaration for a function named fcnPtr that takes 
    //no parameters and returns a pointer to an integer.
    //To make a const function pointer, the const goes after the asterisk :
    //int (* const fcnPtr)();

    int (*fcnPtr1)() { foo }; // fcnPtr points to function foo
    fcnPtr1 = goo; // fcnPtr now points to function goo

    //One common mistake is to do this:
    //fcnPtr1 = goo();
    //This would actually assign the return value from a call to function goo()
    //to fcnPtr, which isn’t what we want.
    //We want fcnPtr to be assigned the address of function goo, 
    //not the return value from function goo().
    //So no parenthesis are needed

    //Note that the type (parameters and return type) 
    //of the function pointer must match the type of the function.
    // function prototypes
    //int foo();
    //double goo();
    //int hoo(int x);

    // function pointer assignments
    //int (*fcnPtr1)() { foo }; // okay
    //int (*fcnPtr2)() { goo }; // wrong -- return types don't match!
    //double (*fcnPtr4)() { goo }; // okay
    //fcnPtr1 = hoo; // wrong -- fcnPtr1 has no parameters, but hoo() does
    //int (*fcnPtr3)(int) { hoo }; // okay

    //Unlike fundamental types, 
    //C++ will implicitly convert a function into a function pointer if needed 
    //(so you don’t need to use the address-of operator (&) 
    //to get the function’s address).
    //However, it will not implicitly convert function pointers to void pointers,
    //or vice-versa.

    //Calling a function using a function pointer
    //int (*fcnPtr2)(int) { foo }; // Initialize fcnPtr with function foo
    //(*fcnPtr2)(5); // call function foo(5) through fcnPtr.
    //The second way is via implicit dereference:
    //int (*fcnPtr3)(int) { foo }; // Initialize fcnPtr with function foo
    //fcnPtr3(5); // call function foo(5) through fcnPtr.
    //As you can see, the implicit dereference method looks just like a
    //normal function call -- which is what you’d expect,
    //since normal function names are pointers to functions anyway!

    //One interesting note: 
    //Default parameters won’t work for functions called through function pointers.
    //Default parameters are resolved at compile-time 
    //(that is, if you don’t supply an argument for a defaulted parameter, 
    //the compiler substitutes one in for you when the code is compiled).
    //However, function pointers are resolved at run-time. 
    //Consequently, default parameters can not be resolved when making a 
    //function call with a function pointer.
    //You’ll explicitly have to pass in values for any defaulted parameters in this case.
}



