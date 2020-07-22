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


// Default the sort to ascending sort
//void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);

// Note our user-defined comparison is the third parameter
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
{
    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };

        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
        }

        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}

bool evensFirst(int x, int y)
{
    // if x is even and y is odd, x goes first (no swap needed)
    if ((x % 2 == 0) && !(y % 2 == 0))
        return false;

    // if x is odd and y is even, y goes first (swap needed)
    if (!(x % 2 == 0) && (y % 2 == 0))
        return true;

    // otherwise sort in ascending order
    return ascending(x, y);
}

// This function prints out the values in the array
void printArray(int* array, int size)
{
    for (int index{ 0 }; index < size; ++index)
        std::cout << array[index] << ' ';
    std::cout << '\n';
}

void passing_functions_as_arguments_to_other_functions()
{
    //One of the most useful things to do with function pointers is pass a function as
    //an argument to another function. Functions used as arguments to another function
    //are sometimes called callback functions.
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);

    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);

    selectionSort(array, 9, evensFirst);
    printArray(array, 9);

    //typedef bool (*validateFcn)(int, int);

    //This defines a typedef called “validateFcn” 
    //that is a pointer to a function that takes two ints and returns a bool.

    //bool validate(int x, int y, validateFcn pfcn)
    //using validateFcn = bool(*)(int, int); // type alias
    //Using a type alias is identical to using a typedef

    //Introduced in C++11, 
    //an alternate method of definingand storing function pointers is to use
    //std::function, which is part of the standard library <functional> header.
    //To define a function pointer using this method, declare a std::function object

    std::function<int()> fcnPtr4{ foo };
    // declare function pointer that returns an int and takes no parameters
    fcnPtr4 = goo;
    // fcnPtr now points to function goo
    std::cout << fcnPtr4() << '\n'; 
    // call the function just like normal

    using validateFcnRaw = bool(*)(int, int); // type alias to raw function pointer
    using validateFcn = std::function<bool(int, int)>; // type alias to std::function

    //Type inference for function pointers
    auto fcnPtr5{ foo };
    std::cout << fcnPtr5() << '\n';
    //The downside is, of course, that all of the details about the 
    //function’s parameters types and return type are hidden, 
    //so it’s easier to make a mistake when making a call with the function,
    //or using its return value.
    
    //Conclusion
    //Function pointers are useful primarily when you want to store functions in an 
    //array(or other structure), 
    //or when you need to pass a function to another function.
    //Because the native syntax to declare function pointers is ugly and error prone,
    //we recommend using std::function.
    //In places where a function pointer type is only used once
    //(e.g.a single parameter or return value), 
    //std::function can be used directly.
    //In places where a function pointer type is used multiple times, a type alias 
    //to a std::function is a better choice(to prevent repeating yourself).
}




int main()
{
    passing_functions_as_arguments_to_other_functions();
    

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
