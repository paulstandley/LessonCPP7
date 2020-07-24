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


bool fp_stop_or_go()
{
    std::cout << "Calc n to stop anything else to continue: ";
    char value{};
    std::cin >> value;
    std::cin.ignore();
    return value == 'n' ? false : true;
}

double fp_get_user_number()
{
    while (true)
    {
        std::cout << "Enter number: ";
        double value{ 0 };
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

char fp_get_user_operator()
{
    while (true)
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char value{};
        std::cin >> value;
        switch (value)
        {
        case '+':
        case '-':
        case '/':
        case '*':
            std::cin.ignore(32767, '\n');
            return value;
        default:
            std::cin.ignore(32767, '\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

double fp_add(const double x, const double y)
{
    return static_cast<double>(x + y);
}

double fp_subtract(const double x, const double y)
{
    return static_cast<double>(x - y);
}

double fp_multiply(const double x, const double y)
{
    return static_cast<double>(x * y);
}

double fp_divide(const double x, const double y)
{
    if (x != 0.0)
    {
        if (y == 0.0)// if y is 0.0 x is not so return x
            return x;
        return static_cast<double>(x / y);//do calac
    }
    else
        return x;// if 0.0 return 0.0
}

arithmeticFcn get_arithmetic_funcion(char operater_function)
{
    switch (operater_function)
    {
    default: // default is fp_add
    case '+': return fp_add;
    case '-': return fp_subtract;
    case '*': return fp_multiply;
    case '/': return fp_divide;
    }
}

void calc_user_input()
{
    while (true)
    {
        if (fp_stop_or_go())
        {
            double user_number_1{ static_cast<double>(fp_get_user_number()) };
            char user_operator{ fp_get_user_operator() };
            double user_number_2{ static_cast<double>(fp_get_user_number()) };

            arithmeticFcn func{ get_arithmetic_funcion(user_operator) };
            double result{ static_cast<double>(func(user_number_1, user_number_2)) };

            std::cout << user_number_1 << ' ' << user_operator << ' '
                << user_number_2 << " = " << result << '\n';
        }
        else
            break;
    }
}

void function_pointer_quiz()
{
    //Quiz time!

    //1) In this quiz, we’re going to write a version of our basic calculator 
    //using function pointers.

    //1a) Create a short program asking the user for two integer inputsand a 
    //mathematical operation(‘ + ’, ‘ - ‘, ‘ * ’, ‘ / ’).
    //Ensure the user enters a valid operation.

    //1b) Write functions named add(), subtract(), multiply(), and divide(). 
    //These should take two integer parameters and return an integer.

    //1c) Create a type alias named arithmeticFcn for a pointer to a
    //function that takes two integer parameters and returns an integer. 
    //Use std::function.

    //1d) Write a function named getArithmeticFunction() that takes an 
    //operator character and returns the appropriate function as a function pointer.

    //1e) Modify your main() function to call getArithmeticFunction(). 
    //Call the return value from that function with your inputs and print the result.

    calc_user_input();
}

void the_stack_and_heap()
{
    // The heap free memory

    //The memory that a program uses is typically 
    //divided into a few different areas, called segments

    //The code segment (also called a text segment), where the compiled program sits in memory. 
    //The code segment is typically read-only.

    //The bss segment(also called the uninitialized data segment), 
    //where zero - initialized global and static variables are stored.

    //The data segment(also called the initialized data segment), 
    //where initialized globaland static variables are stored.

    //The heap, where dynamically allocated variables are allocated from.
    //The call stack, where function parameters, local variables, 
    //and other function - related information are stored.

    //The heap segment (also known as the “free store”)
    //keeps track of memory used for dynamic memory allocation

    //In C++, when you use the new operator to allocate memory, 
    //this memory is allocated in the application’s heap segment.

    //int* ptr = new int; // ptr is assigned 4 bytes in the heap
    //int* array = new int[10]; // array is assigned 40 bytes in the heap

    //The address of this memory is passed back by operator new, 
    //and can then be stored in a pointer. 
    //You do not have to worry about the mechanics behind the process
    //of how free memory is located and allocated to the user. 
    //However, it is worth knowing that sequential memory requests 
    //may not result in sequential memory addresses being allocated!

    //When a dynamically allocated variable is deleted, 
    //the memory is “returned” to the heap and can then be reassigned
    //as future allocation requests are received. 
    //Remember that deleting a pointer does not delete the variable,
    //it just returns the memory at the associated address back to the 
    //operating system.

    //The heap has advantages and disadvantages:

    //Allocating memory on the heap is comparatively slow.
    //Allocated memory stays allocated until it is specifically deallocated
    //(beware memory leaks) or the application ends
    //(at which point the OS should clean it up).

    //Dynamically allocated memory must be accessed through a pointer.
    //Dereferencing a pointer is slower than accessing a variable directly.
    //Because the heap is a big pool of memory, 
    //large arrays, structures, or classes can be allocated here.

    //The call stack

    //The call stack(usually referred to as “the stack”)
    //has a much more interesting role to play.
    //The call stack keeps track of all the active functions
    //(those that have been called but have not yet terminated) 
    //from the start of the program to the current point of execution, 
    //and handles allocation of all function parametersand local variables.

    //The call stack is implemented as a stack data structure.
    //So before we can talk about how the call stack works, 
    //we need to understand what a stack data structure is.

    //The stack data structure

    //A data structure is a programming mechanism for organizing data 
    //so that it can be used efficiently. 
    //You’ve already seen several types of data structures, 
    //such as arrays and structs.
    //Both of these data structures provide mechanisms for storing data 
    //and accessing that data in an efficient way. 
    //There are many additional data structures that are commonly used in programming,
    //quite a few of which are implemented in the standard library,
    //and a stack is one of those.

    //Consider a stack of plates in a cafeteria. 
    //Because each plate is heavy and they are stacked,
    //you can really only do one of three things:

    //1) Look at the surface of the top plate
    //2) Take the top plate off the stack(exposing the one underneath, if it exists)
    //3) Put a new plate on top of the stack(hiding the one underneath, if it exists)

    //In computer programming, 
    //a stack is a container data structure that holds multiple variables 
    //(much like an array). 
    //However, whereas an array lets you access and modify elements in any
    //order you wish (called random access), a stack is more limited.
    //The operations that can be performed on a stack correspond to the
    //three things mentioned above

    //1) Look at the top item on the stack (usually done via a function called top(), 
    //but sometimes called peek())
    //2) Take the top item off of the stack(done via a function called pop())
    //3) Put a new item on top of the stack(done via a function called push())

    //A stack is a last-in, first-out (LIFO) structure. 
    //The last item pushed onto the stack will be the first item popped off. 
    //If you put a new plate on top of the stack, 
    //the first plate removed from the stack will be the plate you just pushed on last. 
    //Last on, first off. As items are pushed onto a stack, 
    //the stack grows larger -- as items are popped off, the stack grows smaller.

    //The plate analogy is a pretty good analogy as to how the call stack works, 
    //but we can make a better analogy. 
    //Consider a bunch of mailboxes, all stacked on top of each other. 
    //Each mailbox can only hold one item, and all mailboxes start out empty. 
    //Furthermore, each mailbox is nailed to the mailbox below it, 
    //so the number of mailboxes can not be changed. 
    //If we can’t change the number of mailboxes, how do we get a stack-like behavior?

    //First, we use a marker (like a post-it note) to keep track of where
    //the bottom-most empty mailbox is. In the beginning, 
    //this will be the lowest mailbox (on the bottom of the stack). 
    //When we push an item onto our mailbox stack, 
    //we put it in the mailbox that is marked (which is the first empty mailbox), 
    //and move the marker up one mailbox. 
    //When we pop an item off the stack, we move the marker down one mailbox 
    //(so it’s pointed at the top non-empty mailbox) and remove the item from that mailbox. 
    //Anything below the marker is considered “on the stack”. 
    //Anything at the marker or above the marker is not on the stack.

    //The call stack segment

    //The call stack segment holds the memory used for the call stack.
    //When the application starts, the main() function is pushed on the call stack
    //by the operating system.Then the program begins executing.

    //When a function call is encountered, the function is pushed onto the call stack.
    //When the current function ends, that function is popped off the call stack.
    //Thus, by looking at the functions pushed on the call stack, 
    //we can see all of the functions that were called to get to the current point 
    //of execution.

    //Our mailbox analogy above is fairly analogous to how the call stack works. 
    //The stack itself is a fixed-size chunk of memory addresses. 
    //The mailboxes are memory addresses, and the “items” we’re
    //pushing and popping on the stack are called stack frames. 
    //A stack frame keeps track of all of the data associated with one function call. 
    //We’ll talk more about stack frames in a bit. The “marker” is a register
    //(a small piece of memory in the CPU) known as the stack pointer 
    //(sometimes abbreviated “SP”). 
    //The stack pointer keeps track of where the top of the call stack currently is.

    //The only difference between our hypothetical mailbox stackand the call stack 
    //is that when we pop an item off the call stack,
    //we don’t have to erase the memory(the equivalent of emptying the mailbox).
    //We can just leave it to be overwritten by the next item pushed to that piece of memory.
    //Because the stack pointer will be below that memory location, 
    //we know that memory location is not on the stack.

    //Typically, it is not important to know all the details about how the call stack works.
    //However, understanding that functions are effectively pushed on the stack
    //when they are called and popped off when they return gives you the fundamentals
    //needed to understand recursion, 
    //as well as some other concepts that are useful when debugging.

    //A technical note: on some architectures, 
    //the call stack grows away from memory address 0. On others, 
    //it grows towards memory address 0. As a consequence,
    //newly pushed stack frames may have a higher or a lower memory address 
    //than the previous ones.

    //Stack overflow

    //The stack has a limited size, 
    //and consequently can only hold a limited amount of information.On Windows, 
    //the default stack size is 1MB.On some unix machines, 
    //it can be as large as 8MB.If the program tries to put too much information
    //on the stack, stack overflow will result.Stack overflow happens when all
    //the memory in the stack has been allocated -- in that case, 
    //further allocations begin overflowing into other sections of memory.

    //Stack overflow is generally the result of allocating too many variables on the stack,
    //and /or making too many nested function calls
    //(where function A calls function B calls function C calls function D etc…)
    //On modern operating systems, overflowing the stack will generally
    //cause your OS to issue an access violationand terminate the program.

    //int stack[10000000];
    //std::cout << "hi";
    //This program tries to allocate a huge (likely 40MB) array on the stack. 
    //Because the stack is not large enough to handle this array,
    //the array allocation overflows into portions of memory the program
    //is not allowed to use.

    //void foo()
    //{
    //    foo();
    //}   

    //int main()
    //{
    //    foo();
    //    return 0;
    //}

    //In the above program, 
    //a stack frame is pushed on the stack every time function foo() is called. 
    //Since foo() calls itself infinitely, 
    //eventually the stack will run out of memory and cause an overflow.

    //The stack has advantagesand disadvantages:

    //Allocating memory on the stack is comparatively fast.
    //Memory allocated on the stack stays in scope as long as it is on the stack.
    //It is destroyed when it is popped off the stack.
    //All memory allocated on the stack is known at compile time.
    //Consequently, this memory can be accessed directly through a variable.
    //Because the stack is relatively small, 
    //it is generally not a good idea to do anything that eats up lots of stack space.
    //This includes passing by value or creating local variables of large arrays
    //or other memory - intensive structures.
}




