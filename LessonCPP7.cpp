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
#include "Header.h"


void set_to_null(int *temp_ptr)
{
    // we're making temp_ptr point at something else,
    // not changing the value that temp_ptr points to.
    temp_ptr = nullptr; // use 0 instead if not C++11
}

void passing_arguments_by_address(const int *array, int length)
{//Because printArray() doesn’t modify any of its arguments, 
    //it’s good form to make the array parameter const:
    // if user passed in a null pointer for array, bail out early!
    if (!array)
        return;
    for (int index = 0; index < length; ++index)
    {
        std::cout << array[index] << ' ';
    }
}

void set_to_six(int *tempPtr)
{
    *tempPtr = 6; // we're changing the value that tempPtr (and ptr) points to
}

// tempPtr is now a reference to a pointer, so any changes made to tempPtr will change the argument as well!
void setToNull(int*& tempPtr)
{
    tempPtr = nullptr; // use 0 instead if not C++11
}

void foo1(int value)// pass by value
{
    value++;
}

void foo2(int &reference)// pass by reference
{
    reference++;
}

void foo3(int *address)// pass by address
{
    address = address + 2;
}

void get_address()
{// arrays decay to pointers
    int array[6] = { 6, 5, 4, 3, 2, 1 };
    // so array evaluates to a pointer to the first element of the array here, no & needed
    passing_arguments_by_address(array, 6);
    // Addresses are actually passed by value
    // First we set ptr to the address of five, which means *ptr = 5
    int five = 5;
    int *ptr = &five;
    // This will print 5
    std::cout << *ptr;
    // tempPtr will receive a copy of ptr
    set_to_null(ptr);
    // ptr is still set to the address of five!    
    // This will print 5
    if (ptr)
        std::cout << *ptr << '\n';
    else
        std::cout << " ptr is null";
    // temp_ptr receives a copy of the address that ptr is holding
    // Note that even though the address itself is passed by value, 
    //you can still dereference that address to change the argument’s value. 
    //This is a common point of confusion, so let’s clarify:

/*
When passing an argument by address, 
the function parameter variable receives a copy of the address from the argument. 
At this point, the function parameter and the argument both point to the same value.

If the function parameter is then dereferenced to change the value being pointed to, 
that will impact the value the argument is pointing to, 
since both the function parameter and argument are pointing to the same value!

If the function parameter is assigned a different address, 
that will not impact the argument, 
since the function parameter is a copy,
and changing the copy won’t impact the original. 
After changing the function parameter’s address, 
the function parameter and argument will point to different values, 
so dereferencing the parameter and changing the value will no longer affect 
the value pointed to by the argument.
*/

    // First we set ptr to the address of five, which means *ptr = 5
    int five5 = 5;
    int *ptr5 = &five5;
    // This will print 5
    std::cout << *ptr5;
    // tempPtr will receive a copy of ptr
    set_to_six(ptr5);
    // tempPtr changed the value being pointed to to 6, so ptr is now pointing to the value 6
    // This will print 6
    if (ptr5)
        std::cout << *ptr5 << '\n';
    else
        std::cout << " ptr is null";

    // Passing addresses by reference
    // First we set ptr to the address of two, which means *ptr = 2
    int two = 2;
    int *ptr2 = &two;
    // This will print 2
    std::cout << *ptr2;
    // tempPtr is set as a reference to ptr
    setToNull(ptr2);
    // ptr has now been changed to nullptr!
    if (ptr2)
        std::cout << *ptr2 << '\n';
    else
        std::cout << " ptr is null\n";
    // And just above, we showed that
    //pass by address is actually just passing an address by value!
    //Therefore, we can conclude that C++ really passes everything by value!
    //The properties of pass by address(and reference)
    //come solely from the fact that we can dereference the passed address 
    //to change the argument, which we can not do with a normal value parameter!

    // Pass by address makes modifiable parameters explicit
    //int foo1(int x); // pass by value
    //int foo2(int& x); // pass by reference
    //int foo3(int* x); // pass by address
    int i{ 68 };
    foo1(i);  // can't modify i
    std::cout << "i = " << i << '\n';
    foo2(i);  // can modify i
    std::cout << "i = " << i << '\n';
    foo3(&i); // can modify i
    std::cout << "i = " << i << '\n';

/*
It’s not obvious from the call to foo2() that the function can modify variable i, is it?

For this reason, some guides recommend passing all modifiable arguments by address, 
so that it’s more obvious from an existing function call that an argument
could be modified.

However, this comes with its own set of downsides: 
the caller might think they can pass in nullptr when they aren’t supposed to, 
and you now have to rigorously check for null pointers.

We lean towards the recommendation of passing non-optional modifiable parameters 
by reference. Even better, avoid modifiable parameters altogether.

Pros and cons of pass by address

Advantages of passing by address:

Pass by address allows a function to change the value of the argument, 
which is sometimes useful.
Otherwise, const can be used to guarantee the function won’t change the argument.
(However, if you want to do this with a non-pointer, 
you should use pass by reference instead).

Because a copy of the argument is not made, 
it is fast, even when used with large structs or classes.
We can return multiple values from a function via out parameters.

Disadvantages of passing by address:

Because literals (excepting C-style string literals)
and expressions do not have addresses, 
pointer arguments must be normal variables.
All values must be checked to see whether they are null. 
Trying to dereference a null value will result in a crash. 
It is easy to forget to do this.
Because dereferencing a pointer is slower than accessing a value directly, 
accessing arguments passed by address is slower than accessing arguments
passed by value.

When to use pass by address:

When passing built-in arrays 
(if you’re okay with the fact that they’ll decay into a pointer).
When passing a pointer and nullptr is a valid argument logically.

When not to use pass by address:

When passing a pointer and nullptr is not a valid argument logically 
(use pass by reference).
When passing structs or classes (use pass by reference).
When passing fundamental types (use pass by value).
As you can see, pass by address and pass by reference have almost identical
advantages and disadvantages. 
Because pass by reference is generally safer than pass by address, 
pass by reference should be preferred in most cases.

Rule: Prefer pass by reference to pass by address whenever applicable.
*/
}


int main()
{
    get_address();

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
