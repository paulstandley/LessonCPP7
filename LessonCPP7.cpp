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
    int (*fcnPtr2)(int) { foo }; // Initialize fcnPtr with function foo
    (*fcnPtr2)(5); // call function foo(5) through fcnPtr.
    //The second way is via implicit dereference:
    int (*fcnPtr3)(int) { foo }; // Initialize fcnPtr with function foo
    fcnPtr3(5); // call function foo(5) through fcnPtr.
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


int main()
{
    function_pointers();
    

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
