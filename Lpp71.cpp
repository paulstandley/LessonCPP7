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

void print_stack(const std::vector<int>& stack)
{
    for (auto element : stack)
        std::cout << element << ' ';
    std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
}

void std_vector_capacity_and_stack_behavior()
{
    //std::vector capacity and stack behavior
    //Length vs capacity

    int* array0{ new int[10] { 1, 2, 3, 4, 5 } };
    delete[] array0;
    //We would say that this array has a length of 10, even though we’re only using 5
    //of the elements that we allocated

    //However, what if we only wanted to iterate over the elements we’ve initialized, 
    //reserving the unused ones for future expansion? 
    //In that case, we’d need to separately track how many elements were “used”
    //from how many elements were allocated. 
    //Unlike a built-in array or a std::array, 
    //which only remembers its length, 
    //std::vector contains two separate attributes: length and capacity. 
    //In the context of a std::vector, length is how many elements are being used 
    //in the array, whereas capacity is how many elements were allocated in memory.

    std::vector<int> array1{ 0, 1, 2 };
    array1.resize(5); // set length to 5
    std::cout << "The length is: " << array1.size() << '\n';
    for (auto element : array1)
        std::cout << element << ' ';

    //In the above example, we’ve used the resize() 
    //function to set the vector’s length to 5.
    //This tells variable array that we’re intending to use the first 5 elements
    //of the array, so it should consider those in active use. 
    //However, that leaves an interesting question: 
    //what is the capacity of this array?

    std::cout << "The length is: " << array1.size() << '\n';
    std::cout << "The capacity is: " << array1.capacity() << '\n';

    //More length vs. capacity

    //Why differentiate between lengthand capacity ? 
    //std::vector will reallocate its memory if needed,
    //but like Melville’s Bartleby, it would prefer not to, 
    //because resizing an array is computationally expensive.Consider the following

    std::vector<int> array2{};
    array2 = { 0, 1, 2, 3, 4 }; // okay, array length = 5
    std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';

    array2 = { 9, 8, 7 }; // okay, array length is now 3!
    std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';
    std::cout << '\n';

    //Note that although we assigned a smaller array to our vector, 
    //it did not reallocate its memory (the capacity is still 5). 
    //It simply changed its length, 
    //so it knows that only the first 3 elements are valid at this time.

    //Array subscripts and at() are based on length, not capacity

    //The range for the subscript operator ([]) and at() function is based on the the
    //vector’s length, not the capacity. 
    //Consider the array in the previous example, which has length 3 and capacity 5.
    //What happens if we try to access the array element with index 4? 
    //The answer is that it fails, since 4 is greater than the length of the array.

    //Note that a vector will not resize itself based on a call to the subscript 
    //operator or at() function

    std::vector<int> stack{};

    print_stack(stack);

    stack.push_back(5); // push_back() pushes an element on the stack
    print_stack(stack);

    stack.push_back(3);
    print_stack(stack);

    stack.push_back(2);
    print_stack(stack);

    std::cout << "top: " << stack.back() << '\n'; // back() returns the last element

    stack.pop_back(); // pop_back() pops an element off the stack
    print_stack(stack);

    stack.pop_back();
    print_stack(stack);

    stack.pop_back();
    print_stack(stack);

    //We can see that the capacity was preset to 5 and didn’t change
    //over the lifetime of the program

    //Vectors may allocate extra capacity
    //When a vector is resized, the vector may allocate more capacity than is needed.
    //This is done to provide some “breathing room” for additional elements, 
    //to minimize the number of resize operations needed.
    //Let’s take a look at this

    std::vector<int> v{ 0, 1, 2, 3, 4 };
    std::cout << '\n';
    std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
    for (auto element : v)
        std::cout << element << ' ';
    std::cout << '\n';
    v.push_back(5); // add another element
    std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
    for (auto element : v)
        std::cout << element << ' ';
    std::cout << '\n';

    //When we used push_back() to add a new element,
    //our vector only needed room for 6 elements, but allocated room for 7.
    //This was done so that if we were to push_back() another element,
    //it wouldn’t need to resize immediately.

    //If, when, and how much additional capacity is allocated
    //is left up to the compiler implementer.
}

// h/t to potterman28wxcv for a variant of this code
int fibonacci0(int count)
{
    // We'll use a static std::vector to cache calculated results
    static std::vector<int> results{ 0, 1 };

    // If we've already seen this count, then use the cache'd result
    if (count < static_cast<int>(std::size(results)))
        return results[count];
    else
    {
        // Otherwise calculate the new result and add it
        results.push_back(fibonacci0(count - 1) + fibonacci0(count - 2));
        return results[count];
    }
}

int fibonacci1(int count)
{
    if (count == 0)
        return 0; // base case (termination condition)
    if (count == 1)
        return 1; // base case (termination condition)
    return fibonacci1(count - 1) + fibonacci1(count - 2);
}

int sumTo(int sumto)
{
    // return the sum of all the integers between 1 (inclusive) and sumto (inclusive)
    // returns 0 for negative numbers
    if (sumto <= 0)
        return 0; // base case (termination condition) when user passed in an unexpected parameter (0 or negative)
    else if (sumto == 1)
        return 1; // normal base case (termination condition)
    else
        return sumTo(sumto - 1) + sumto; // recursive function call
    //Recursive programs are often hard to figure out just by looking at them. 
    //It’s often instructive to see what happens when we call a recursive function
    //with a particular value. 

    //So let’s see what happens when we call this function with parameter sumto = 5.

    //sumTo(5) called, 5 <= 1 is false, so we return sumTo(4) + 5.
    //sumTo(4) called, 4 <= 1 is false, so we return sumTo(3) + 4.
    //sumTo(3) called, 3 <= 1 is false, so we return sumTo(2) + 3.
    //sumTo(2) called, 2 <= 1 is false, so we return sumTo(1) + 2.
    //sumTo(1) called, 1 <= 1 is true, so we return 1. This is the termination condition

    //Now we unwind the call stack (popping each function off the call stack as it returns)

    //sumTo(1) returns 1.
    //sumTo(2) returns sumTo(1) + 2, which is 1 + 2 = 3.
    //sumTo(3) returns sumTo(2) + 3, which is 3 + 3 = 6.
    //sumTo(4) returns sumTo(3) + 4, which is 6 + 4 = 10.
    //sumTo(5) returns sumTo(4) + 5, which is 10 + 5 = 15.

    //Because recursive functions can be hard to understand by looking at them, 
    //good comments are particularly important.

    //Note that in the above code, we recurse with value sumto - 1 rather than --sumto.
    //We do this because operator-- has a side effect, 
    //and using a variable that has a side effect applied more than once 
    //in a given expression will result in undefined behavior. 
    //Using sumto - 1 avoids side effects, 
    //making sumto safe to use more than once in the expression.
}

void count_down(int count)
{//infinite loop
    std::cout << "push " << count << '\n';
    //count_down(count - 1); // countDown() calls itself recursively
    if (count != 0)
    {
        count_down(count - 1); // countDown() calls itself recursively
    }
    std::cout << "pop " << count << '\n';
    //Because of the termination condition, 
    //countDown(1) does not call countDown(0) -- instead, 
    //the “if statement” does not execute, so it prints “pop 1” and then terminates. 
    //At this point, countDown(1) is popped off the stack, 
    //and control returns to countDown(2). 
    //countDown(2) resumes execution at the point after countDown(1) was called, 
    //so it prints “pop 2” and then terminates. 
    //The recursive function calls get subsequently popped off the stack until
    //all instances of countDown have been removed.
}

void recursion()
{//Rule: Generally favor iteration over recursion, except when recursion really makes sense.
    //A recursive function in C++ is a function that calls itself. 
    count_down(5);
    //When countDown(5) is called, “push 5” is printed, and countDown(4) is called. 
    //countDown(4) prints “push 4” and calls countDown(3). 
    //countDown(3) prints “push 3” and calls countDown(2). 
    //The sequence of countDown(n) calling countDown(n-1) is repeated indefinitely, 
    //effectively forming the recursive equivalent of an infinite loop.

    std::cout << '\n';
    std::cout << "sumto = " << sumTo(10) << '\n';

    //Recursive algorithms

    //Recursive functions typically solve a problem by first finding the solution
    //to a subset of the problem(recursively), 
    //and then modifying that sub - solution to get to a solution.
    //In the above algorithm, sumTo(value) first solves sumTo(value - 1), 
    //and then adds the value of variable value to find the solution for sumTo(value).

    //In many recursive algorithms, some inputs produce trivial outputs.
    //For example, sumTo(1) has the trivial output 1 
    //(you can calculate this in your head), 
    //and does not benefit from further recursion.
    //Inputs for which an algorithm trivially produces an output is called a base case.
    //Base cases act as termination conditions for the algorithm.
    //Base cases can often be identified by considering the output 
    //for an input of 0, 1, "", '', or null.

    //Fibonacci numbers

    //One of the most famous mathematical recursive algorithms is the Fibonacci sequence.
    //Fibonacci sequences appear in many places in nature, 
    //such as branching of trees, the spiral of shells, the fruitlets of a pineapple,
    //an uncurling fern frond, and the arrangement of a pine cone.

    //Consequently, it's rather simple to write a (not very efficient) 
    //recursive function to calculate the nth Fibonacci number

    std::cout << '\n';
    for (int count = 0; count < 13; ++count)
        std::cout << fibonacci1(count) << " ";
    std::cout << '\n';

    //The above recursive Fibonacci algorithm isn't very efficient, 
    //in part because each call to a Fibonacci non-base case results in two more 
    //Fibonacci calls. 
    //This produces an exponential number of function calls 
    //(in fact, the above example calls fibonacci() 1205 times!).
    //There are techniques that can be used to reduce the number of calls necessary. 
    //One technique, called memoization, caches the results of expensive 
    //function calls so the result can be returned when the same input occurs again.

    for (int count = 0; count < 13; ++count)
        std::cout << fibonacci0(count) << " ";
    std::cout << '\n';

    //This memoized version makes 35 function calls, 
    //which is much better than the 1205 of the original algorithm.

    //Recursive vs iterative

    //One question that is often asked about recursive functions is, 
    //"Why use a recursive function if you can do many of the same tasks iteratively
    //(using a for loop or while loop)?". 
    //It turns out that you can always solve a recursive problem iteratively
    //-- however, for non-trivial problems, 
    //the recursive version is often much simpler to write (and read). 
    //For example, while it's possible to write the Fibonacci function iteratively, 
    //it's a little more difficult! (Try it!)

    //Iterative functions (those using a for-loop or while-loop) 
    //are almost always more efficient than their recursive counterparts. 
    //This is because every time you call a function there is some amount of 
    //overhead that takes place in pushing and popping stack frames.
    //Iterative functions avoid this overhead.

    //That’s not to say iterative functions are always a better choice.
    //Sometimes the recursive implementation of a function is so much cleaner
    //and easier to follow that incurring a little extra overhead is more
    //than worth it for the benefit in maintainability, 
    //particularly if the algorithm doesn't need to recurse too many 
    //times to find a solution.

    //In general, recursion is a good choice when most of the following are true:

    //The recursive code is much simpler to implement.
    //The recursion depth can be limited
    //(e.g.there’s no way to provide an input that will cause it to recurse down 100, 000 levels).
    //The iterative version of the algorithm requires managing a stack of data.
    //This isn’t a performance - critical section of code.
    //However, if the recursive algorithm is simpler to implement, 
    //it may make sense to start recursivelyand then optimize to an iterative algorithm later.
}

void printBinary(unsigned int n)
{// h/t to reader Donlod for this solution
    if (n > 1) // we only recurse if n > 1, so this is our termination case for n == 0
        printBinary(n / 2);

    std::cout << n % 2;
}

void print_binary(int x)
{// h/t to reader Gapo for this solution
    // Termination case
    if (x == 0)
        return;

    // Recurse to the next bit
    print_binary(x / 2);

    // Print out the remainders (in reverse order)
    std::cout << x % 2;
}

int individual_digit_in_the_integer(int num)
{// if one digit return digit, else divide num by 10 then add modulo 10 
    if (num < 10)
        return num;
    else
        return individual_digit_in_the_integer(num / 10) + num % 10;
}

int factorial001(int num)
{// if the number is 1 or less return 1 else number minus one times the number
    if (num <= 0)
        return 1;
    else
        return factorial001(num - 1) * num;
}

void recursion_quiz()
{
    //1) A factorial of an integer N (written N!) 
    //is defined as the product (multiplication) 
    //of all the numbers between 1 and N (0! = 1). 
    //Write a recursive function called factorial
    //that returns the factorial of the input. 
    //Test it with the first 7 factorials.

    //Hint: Remember that(x * y) = (y * x), 
    //so the product of all the numbers between 1 and N
    //is the same as the product of all the numbers between N and 1.

    for (int count = 0; count < 7; ++count)
        std::cout << factorial001(count) << '\n';
    std::cout << '\n';

    //2) Write a recursive function that takes an integer as input and returns
    //the sum of each individual digit in the integer (e.g. 357 = 3 + 5 + 7 = 15).
    //Print the answer for input 93427 (which is 25).
    //Assume the input values are positive.

    std::cout << individual_digit_in_the_integer(93427) << '\n';

    //3a) This one is slightly trickier. 
    //Write a program that asks the user to enter a positive integer,
    //and then uses a recursive function to print out the binary representation 
    //for that number.

    int posint;
    std::cout << "Enter a positive integer: ";
    std::cin >> posint;
    print_binary(posint);

    //3b) Update your code from 3a to handle the case where the user may enter
    //0 or a negative number.
    //Hint: You can turn a negative integer into a positive one
    //by converting it to an unsigned integer. 
    //These have identical bit representations 
    //(the type is used to determine how to interpret the number into decimal).

    printBinary(posint);
}


