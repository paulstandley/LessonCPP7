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