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


void optional_parameter(int x, int y = 10)
{// 10 is the default argument, y is now an optional parameter
    std::cout << "x = " << x << '\n' << "y = " << y << '\n';
}

void multiple_default_arguments(int x = 10, int y = 20, int z = 30)
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


int main()
{
    default_arguments();
    

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
