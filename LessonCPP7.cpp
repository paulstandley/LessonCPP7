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



int binarySearch(const int* array, int target, int min, int max)
{
    // array is the array to search over.
    // target is the value we're trying to determine exists or not.
    // min is the index of the lower bounds of the array we're searching.
    // max is the index of the upper bounds of the array we're searching.
    // binarySearch() should return the index of the target element if the target is found,
    //-1 otherwise

    //Look at the center element of the array 
    //(if the array has an even number of elements, round down).

    /*
        int mid{ min - max / 2 };

    //If the center element is greater than the target element, 
    //discard the top half of the array (or recurse on the bottom half)
    int stop{ 1 };

    while (true)
    {
        if (array[mid] == target)
        {
            return target;
        }
        else if (array[mid] <= target)
        {
            std::cout << "<= " << array[mid] << '\t' << target << '\n';
            mid = max / 2;
        }
        else if (array[mid] >= target)
        {
            std::cout << array[mid] << '\t' << target << '\n';
            mid = mid;
        }
        else if (mid >= min)
        {
            return -1;
        }
        ++stop;
        if (stop < max)
            break;
    }
    */

    assert(array); // make sure array exists

    while (min <= max)
    {
        // implement this iteratively
        int midpoint{ min + ((max - min) / 2) }; // this way of calculating midpoint avoids overflow

        if (array[midpoint] > target)
        {
            // if array[midpoint] > target, then we know the number must be in the lower half of the array
            // we can use midpoint - 1 as the upper index, since we don't need to retest the midpoint next iteration
            max = midpoint - 1;
        }
        else if (array[midpoint] < target)
        {
            // if array[midpoint] < target, then we know the number must be in the upper half of the array
            // we can use midpoint + 1 as the lower index, since we don't need to retest the midpoint next iteration
            min = midpoint + 1;
        }
        else
            return midpoint;
    }
    return -1;
}

int binarySearch1(const int* array, int target, int min, int max)
{
    assert(array); // make sure array exists

// implement this recursively

    if (min > max)
        return -1;

    int midpoint{ min + ((max - min) / 2) }; // this way of calculating midpoint avoids overflow

    if (array[midpoint] > target)
    {
        return binarySearch1(array, target, min, midpoint - 1);
    }
    else if (array[midpoint] < target)
    {
        return binarySearch1(array, target, midpoint + 1, max);
    }
    else
        return midpoint;
}

void lesson_7_comprehensive_quiz()
{
    /*Quick Summary
    Function arguments can be passed by value, reference or address.
    Use pass by value for fundamental data types and enumerators.
    Use pass by reference for structs, classes, or when you need the function
    to modify an argument.
    Use pass by address for passing pointers or built-in arrays.
    Make your pass by reference and address parameters const whenever possible.

    Values can be returned by value, reference, or address.
    Most of the time, return by value is fine,
    however return by reference or address can be useful when working with 
    dynamically allocated data, structs, or classes.
    If returning by reference or address, 
    remember to make sure you’re not returning something that will go out of scope.

    Inline functions allow you to request that the compiler replace your function call
    with the function code. 
    You should not need to use the inline keyword because the compiler 
    will generally determine this for you.

    Function overloading allows us to create multiple functions with the same name,
    so long as each function is distinct in the number or types of parameters.
    The return value is not considered when determining whether an overload is distinct.

    A default argument is a default value provided for a function parameter. 
    If the caller doesn’t explicitly pass in an argument for a parameter 
    with a default value, the default value will be used.
    You can have multiple parameters with default values. 
    All parameters with default values must be to the right of non-default parameters.
    A parameter can only be defaulted in one location.
    Generally it is better to do this in the forward declaration. 
    If there are no forward declarations, this can be done on the function definition.

    Function pointers allow us to pass a function to another function. 
    This can be useful to allow the caller to customize the behavior of a function,
    such as the way a list gets sorted.

    Dynamic memory is allocated on the heap.

    The call stack keeps track of all of the active functions
    (those that have been called but have not yet terminated)
    from the start of the program to the current point of execution. 
    Local variables are allocated on the stack.
    The stack has a limited size.
    std::vector can be used to implement stack-like behavior.

    A recursive function is a function that calls itself. 
    All recursive functions need a termination condition.

    ///////////////////////////////////////////////////////////////////////

    A syntax error occurs when you write a statement that is not valid according 
    to the grammar of the C++ language.
    The compiler will catch these.
    A semantic error occurs when a statement is syntactically valid,
    but does not do what the programmer intended.

    Two common semantic errors are logic errors, and violated assumptions. 
    The assert statement can be used to detect violated assumptions, 
    but has the downside of terminating your program immediately if the
    assertion statement is false.

    Command line arguments allow users or other programs 
    to pass data into our program at startup. 
    Command line arguments are always C-style strings,
    and have to be converted to numbers if numeric values are desired.

    Ellipsis allow you to pass a variable number of arguments to a function.
    However, ellipsis arguments suspend type checking,
    and do not know how many arguments were passed. 
    It is up to the program to keep track of these details.

    Lambda functions are functions that can be nested inside other functions.
    They don’t need a name and are very useful in combination with the algorithms 
    library.
    
    /////////////////////////////////////////////////////////////////////////////

    The best algorithm for determining whether a value exists in a sorted array
    is called binary search.
    
    Binary search works as follows:

    Look at the center element of the array 
    (if the array has an even number of elements, round down).

    If the center element is greater than the target element, 
    discard the top half of the array (or recurse on the bottom half)

    If the center element is less than the target element, 
    discard the bottom half of the array (or recurse on the top half).

    If the center element equals the target element, 
    return the index of the center element.

    If you discard the entire array without finding the target element, 
    return a sentinel that represents “not found” 
    (in this case, we’ll use -1, since it’s an invalid array index).

    Because we can throw out half of the array with each iteration, 
    this algorithm is very fast. Even with an array of a million elements,
    it only takes at most 20 iterations to determine whether a value exists 
    in the array or not! However, it only works on sorted arrays.

    Modifying an array (e.g. discarding half the elements in an array) is expensive,
    so typically we do not modify the array.
    Instead, we use two integer (min and max) to hold the indices of the minimum 
    and maximum elements of the array that we’re interested in examining.

    ///////////////////////////////////////////////////////////////////////

    Let’s look at a sample of how this algorithm works, 
    given an array { 3, 6, 7, 9, 12, 15, 18, 21, 24 }, and a target value of 7. 
    At first, min = 0, max = 8, because we’re searching the whole array
    (the array is length 9, so the index of the last element is 8).

    Pass 1) We calculate the midpoint of min (0) and max (8),
    which is 4. Element #4 has value 12, which is larger than our target value. 
    Because the array is sorted, 
    we know that all elements with index equal to or greater than the midpoint
    (4) must be too large. So we leave min alone, and set max to 3.

    Pass 2) We calculate the midpoint of min (0) and max (3),
    which is 1. Element #1 has value 6, which is smaller than our target value.
    Because the array is sorted, we know that all elements 
    with index equal to or lesser than the midpoint (1) must be too small.
    So we set min to 2, and leave max alone.

    Pass 3) We calculate the midpoint of min (2) and max (3),
    which is 2. Element #2 has value 7, which is our target value. 
    So we return 2.

    */
    
     constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };
 
    // We're going to test a bunch of values to see if they produce the expected results
    constexpr int numTestValues{ 9 };
    // Here are the test values
    constexpr int testValues[numTestValues]{ 0, 3, 12, 13, 22, 26, 43, 44, 49 };
    // And here are the expected results for each value
    int expectedValues[numTestValues]{ -1, 0, 3, -1, -1, 8, -1, 13, -1 };
 
    // Loop through all of the test values
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        // See if our test value is in the array
        int index{ binarySearch(array, testValues[count], 0, 14) };
        // See if our test value is in the array
        int index1{ binarySearch1(array, testValues[count], 0, 14) };
        // If it matches our expected value, then great!
        if (index == expectedValues[count])
             std::cout << "test value " << testValues[count] << " passed!\n";
        else // otherwise, our binarySearch() function must be broken
             std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";

        if (index1 == expectedValues[count])
            std::cout << "test value " << testValues[count] << " passed!\n";
        else // otherwise, our binarySearch() function must be broken
            std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
    
    }

    /*Tip

    std::binary_search returns true if a value exists in a sorted list.

    std::equal_range returns the iterators to the first and last element 
    with a given value.

    Don’t use these functions to solve the quiz,
    but use them in the future if you need a binary search.
    
    */
}

int main()
{
    lesson_7_comprehensive_quiz();


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
