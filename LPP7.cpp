#include "pch.h"
#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include <iterator> // for std::size
#include <cmath>    // for std::sin() and std::cos()
#include <tuple>
#include "Header.h"


void std_reduce()
{
    std::array arr{ 1, 2, 3, 4 };
    std::cout << std::reduce(arr.begin(), arr.end()) << '\n'; // 10
    // If you can't use std::reduce, use std::accumulate. The 0 is the initial value
    // of the result: 0 + (((1 + 2) + 3) + 4)
    std::cout << std::accumulate(arr.begin(), arr.end(), 0) << '\n'; // 10
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(arr.begin(), arr.end(), mt);
    for (int i : arr)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void examplecode()
{
    const std::vector<double> v(10'000'007, 0.5);

    {
        const auto t1 = std::chrono::high_resolution_clock::now();
        const double result = std::accumulate(v.cbegin(), v.cend(), 0.0);
        const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << std::fixed << "std::accumulate result " << result
            << " took " << ms.count() << " ms\n";
    }

    {
        const auto t1 = std::chrono::high_resolution_clock::now();
        const double result = std::reduce(std::execution::par, v.cbegin(), v.cend());
        const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << "std::reduce result "
            << result << " took " << ms.count() << " ms\n";
    }
}

int countTotalItems(const int value)
{
    return value;
}

void question1()
{
    //Pretend you’re writing a game where the player can hold 3 types of items: 
    //health potions, torches, and arrows. 
    //Create an enum to identify the different types of items, 
    //and an std::array to store the number of each item the player is carrying 
    //(The enumerators are used as indexes of the array). 
    //The player should start with 2 health potions, 5 torches, and 10 arrows.
    //Write a function called countTotalItems() 
    //that returns how many items the player has in total. 
    //Have your main() function print the output of countTotalItems() 
    //as well as the number of torches.

    std::array <int, 3>carrying{};
    carrying[0] = Items::potions;
    carrying[1] = Items::torches;
    carrying[2] = Items::arrows;

    const int reduceint = std::reduce(
        std::execution::par, carrying.cbegin(), carrying.cend());

    std::cout << "The player has " << countTotalItems(reduceint) << " total items." << '\n';
    std::cout << "The player has " << Items::torches << " torches." << '\n';
}
// question 2
std::string get_name()
{
    std::string name{};
    std::cout << "Please enter first name ";
    std::cin >> name;
    return name;
}

int get_grade()
{
    int grade{};
    std::cout << "Please enter grade ";
    std::cin >> grade;
    return grade;
}

bool compareStudents(const Student& a, const Student& b)
{
    // Pass by reference to avoid slow copies.
    return (a.grade > b.grade);
}

void question2()
{
    //Write the following program : 
    //Create a struct that holds a student’s first nameand grade(on a scale of 0 - 100).
    //Ask the user how many students they want to enter.
    //Create a std::vector to hold all of the students.
    //Then prompt the user for each nameand grade.
    //Once the user has entered all the namesand grade pairs,
    //sort the list by grade(highest first).
    //Then print all the namesand grades in sorted order.
    //The output should look like this
    //Alex got a grade of 94
    //Mark got a grade of 88
    //Joe got a grade of 82
    //Terry got a grade of 73
    //Ralph got a grade of 4

    std::vector <Student> vector_array;
    std::cout << "Roll call" << '\n';
    bool stop{ false };
    char y{ 'n' };
    Student stundent;

    while (true)
    {
        stundent.first_name = get_name();
        stundent.grade = get_grade();
        vector_array.push_back(stundent);
        std::cout << "Are you ready to stop y";
        std::cin >> y;
        if (static_cast<int>(y) == 121)
        {
            std::cout << "True \n";
            break;
        }
    }

    std::sort(vector_array.begin(), vector_array.end(), compareStudents);
    for (auto inc = vector_array.begin(); inc != vector_array.end(); ++inc)
    {
        std::cout << (*inc).first_name << " got a grade of " << inc->grade << '\n';
    }
}

void question3(int one, int two)
{
    //Write your own function to swap the value of two integer variables.
    //Write a main() function to test it.
    std::cout << "One is " << one << " and two is " << two << '\n';
    std::cout << "Swap variables?" << '\n';
    //?????????????????????????????????????????????????????
    int swap{};//?  ?????????  ???        ????        ?????
    swap = one;//??  ??? ???  ???????  ???????  ???????????
    one = two;//????    ?    ????????  ???????      ???????
    two = swap;//????  ???  ?????????  ???????  ???????????
    //?????????????????????????????????????????????????????
    std::cout << "One is " << one << " and two is " << two << '\n';
}

void question4(const char* stringy2)
{
    //Write a function to print a C-style string character by character. 
    //Use a pointer to step through each character of the string 
    //and print that character. Stop when you hit the null terminator. 
    //Write a main function that tests the function with the 
    //string literal “Hello, world!”.
    char stringy1[]{ "Hello, world!" };
    const int length{ static_cast<int>(std::size(stringy1)) };
    //const int length{ sizeof(myString) / sizeof(myString[0]) }; 
    //use instead if not C++17 capable
    for (int i = 0; i < length; i++)
    {
        std::cout << stringy1[i] << ' ';
    }
    std::cout << std::endl;

    //const char length1{ static_cast<int>(*stringy2) };
    while (*stringy2 != '\0')
    {
        std::cout << *stringy2;// print the current character
        ++stringy2;// and point stringy2 at the next character
    }
    std::cout << std::endl;
}

void question5()
{
    //What’s wrong with each of these snippets, and how would you fix it?
    {// (a) returns a value thats out of range undefiend behaver so change <= to =
        int array[]{ 0, 1, 2, 3 };// count = std::size(array)
        for (std::size_t count{ 0 }; count <= std::size(array); ++count)
        {
            std::cout << array[count] << ' ';
        }
        std::cout << '\n';
    }
    {// (b) asingning a int to a pointer fix this by making ptr non-const
        int x{ 5 };
        int y{ 7 };
        const int* ptr{ &x };
        std::cout << *ptr << '\n';
        //*ptr = 6;
        std::cout << *ptr << '\n';
        ptr = &y;
        std::cout << *ptr << '\n';
    }
    /*//   (c) array dose not remember
    //     it length it decays to a pointer you
    //     need to pass it into to function as a second pramaiter
    void printArray(int array[])
    {
      for (int element : array)
      {
        std::cout << element << ' ';
      }
    }

    int main()
    {
      int array[]{ 9, 7, 5, 3, 1 };

      printArray(array);

      std::cout << '\n';

      return 0;
    }

    //   (d)
        int *allocateArray(const int length)
        {
            int temp[length]{};
            return temp;
        }
        temp is a fixed array, but length is not a compile-time constant,
        so we can’t use length to create a C-style array.
        Variable temp will also go out of scope at the end of the function,
        the return value will be pointing to something invalid.
        temp should use dynamic memory allocation or be a std::vector

        {// (e) You can’t make an int pointer point at a non-int variable.
            //ptr should be of type double*
            double d{ 5.5 };
            int* ptr{ &d };
            std::cout << ptr << '\n';
        }
    */
}

void pass_by_value(int y)
{
    std::cout << "y = " << y << '\n';
    y = 6;
    std::cout << "y = " << y << '\n';
    /*
    Pros and cons of pass by value

Advantages of passing by value:

Arguments passed by value can be variables (e.g. x), literals (e.g. 6),
expressions (e.g. x+1), structs & classes, and enumerators.
In other words, just about anything.
Arguments are never changed by the function being called, which prevents side effects.

Disadvantages of passing by value:

Copying structs and classes can incur a significant performance penalty,
especially if the function is called many times.
When to use pass by value:

When passing fundamental data type and enumerators,
and the function does not need to change the argument.

When not to use pass by value:

When passing structs or classes (including std::array, std::vector, and std::string).
In most cases, pass by value is the best way to accept parameters of fundamental
types when the function does not need to change the argument.
Pass by value is flexible and safe, and in the case of fundamental types, efficient.
    */
}

void callL7Func()
{
    //Function parameters passed by value can also be made const. 
    //This will enlist the compiler’s help in ensuring the function 
    //doesn’t try to change the parameter’s value.
    int x = 5;
    std::cout << "x = " << x << '\n';
    pass_by_value(x);
    std::cout << "x = " << x << '\n';
}

void print_elements(int(&arr)[4])
{// Note: You need to specify the array size in the function declaration
    int length{ sizeof(arr) / sizeof(arr[0]) };
    // we can now do this since the array won't decay
    for (int i{ 0 }; i < length; ++i)
    {
        std::cout << arr[i] << std::endl;
    }
}

void references_to_pointers(int*& ptr)
{// pass pointer by referance
    ptr = nullptr;
    // this changes the actual ptr argument passed in, not a copy
}

void get_sin_cos(double degrees, double& sin_out, double& cos_out)
{// This function takes one parameter (by value) as input,
    // and “returns” two parameters (by reference) as output.
    // sin() and cos() take radians, not degrees, so we need to convert
    static constexpr double pi{ 3.14159265358979323846 };// pie
    double radians = degrees * pi / 180.0;
    sin_out = std::sin(radians);
    cos_out = std::cos(radians);
    //Non-const references can only reference non-const l-values 
    //(e.g. non-const variables), so a reference parameter cannot 
    //accept an argument that is a const l-value or an r-value 
    //(e.g. literals and the results of expressions).
}

void add_one(int& ref)
{
    ref++;
}

void pass_by_ref()
{
    int value{ 5 };
    std::cout << "value = " << value << '\n';
    add_one(value);
    std::cout << "value = " << value << '\n';
    // returning multile values
    double sin(0.0);
    double cos(0.0);

    // get_sin_cos will return the sin and cos in variables sin and cos
    get_sin_cos(30.0, sin, cos);
    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';

    //It enlists the compilers help in ensuring values that shouldn’t 
    //be changed aren’t changed (the compiler will throw an error if you try,
    //like in the above example).
    //It tells the programmer that the function won’t change the value of the argument.
    //This can help with debugging.

    //You can’t pass a const argument to a non - const reference parameter.
    //Using const parameters ensures you can pass both non - constand const arguments
    //to the function.
    //Const references can accept any type of argument, 
    //including non - const l - values, const l - values, and r - values.

    //Rule
    //When passing an argument by reference, 
    //always use a const reference unless you need to change the value of the argument.

    //Non-const references cannot bind to r-values. 
    //A function with a non-const reference parameter 
    //cannot be called with literals or temporaries.
    /*
     void foo(std::string& text) {}

    int main()
    {
        std::string text{ "hello" };
        foo(text); // ok
        foo(text + " world"); // illegal, non-const references can't bind to r-values.
        return 0;
    }
    */

    int xx = { 5 };
    int* ptr = &xx;
    std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n';
    references_to_pointers(ptr);
    std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n';

    int arr[]{ 99, 20, 14, 80 };
    print_elements(arr);

    //As a reminder, you can pass a C-style array by reference. 
    //This is useful if you need the ability for the function to change the array 
    //(e.g. for a sort function) or you need access to the array’s type information
    //of a fixed array (to do sizeof() or a for-each loop). 
    //However, note that in order for this to work, 
    //you explicitly need to define the array size in the parameter:

    //This means this only works with fixed arrays of one particular length.
    //If you want this to work with fixed arrays of any length, 
    //you can make the array length a template parameter

    /*
    Pros and cons of pass by reference

    Advantages of passing by reference:

    References allow a function to change the value of the argument,
    which is sometimes useful.
    Otherwise, const references can be used to guarantee the function won’t change
    the argument.

    Because a copy of the argument is not made,
    pass by reference is fast, even when used with large structs or classes.
    References can be used to return multiple values from a function (via out parameters).
    References must be initialized, so there’s no worry about null values.

    Disadvantages of passing by reference:

    Because a non-const reference cannot be initialized with a
    const l-value or an r-value (e.g. a literal or an expression),
    arguments to non-const reference parameters must be normal variables.

    It can be hard to tell whether an argument passed by non-const
    reference is meant to be input, output, or both.
    Judicious use of const and a naming suffix for out variables can help.

    It’s impossible to tell from the function call whether the argument may change.
    An argument passed by value and passed by reference looks the same.
    We can only tell whether an argument is passed by value or reference
    by looking at the function declaration.
    This can lead to situations where the programmer does not realize
    a function will change the value of the argument.

    When to use pass by reference:

    When passing structs or classes (use const if read-only).
    When you need the function to modify an argument.
    When you need access to the type information of a fixed array.
    When not to use pass by reference:

    When passing fundamental types that don’t need to be modified (use pass by value).
    Rule: Use pass by (const) reference instead of pass by value for structs and classes
    and other expensive-to-copy types.
    */
}

void set_to_null(int* temp_ptr)
{
    // we're making temp_ptr point at something else,
    // not changing the value that temp_ptr points to.
    temp_ptr = nullptr; // use 0 instead if not C++11
}

void passing_arguments_by_address(const int* array, int length)
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

void set_to_six(int* tempPtr)
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

void foo2(int& reference)// pass by reference
{
    reference++;
}

void foo3(int* address)// pass by address
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
    int* ptr = &five;
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
    int* ptr5 = &five5;
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
    int* ptr2 = &two;
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

int return_by_value(int x)
{// double value
    //When to use return by value:
    //When returning variables that were declared inside the function
    //    When returning function arguments that were passed by value

    //    When not to use return by value :
    //When returning a built - in array or pointer(use return by address)
    //    When returning a large struct or class (use return by reference)

    int value{ x * 2 };
    return value;
}

int* return_by_address(int x)
{// return address
    int value{ x * 2 };
    return &value;
    // value is destroyed just after its address is returned to the caller.
    //The end result is that the caller ends up with the address of 
    //non-allocated memory (a dangling pointer), which will cause problems if used.
}

int* allocate_array(int size)
{// return dynamically allocated memory
    return new int[size];
    //This works because dynamically allocated memory does not go out of scope 
    //at the end of the block in which it is declared, 
    //so that memory will still exist when the address is returned back to the caller. 
    //Keeping track of manual allocations can be difficult.
}

// Returns a reference to the index element of array
int& get_element(std::array<int, 25>& array, int index)
{
    // we know that array[index] will not be destroyed when we return to the caller (since the caller passed in the array in the first place!)
    // so it's okay to return it by reference
    return array[index];
}

std::tuple<int, double> return_tuple()
{// return a tuple that contains an int and a double
    return { 5, 6.7 };
}

//void returning_values_by_value_reference_and_address()
//{
    //int value{ return_by_value(33) };
    //std::cout << "Return by value : " << value << '\n';

    //int* address{ return_by_address(44) };
    //std::cout << "Return by address : " << &address << '\n';

    // Return by address was often used to return 
    // dynamically allocated memory to the caller:
    //int* array{ allocate_array(25) };
    // do stuff with array
    //delete[] array;

    //When to use return by address:
    //When returning dynamically allocated memoryand you can’t use a type that handles allocations for you
    //When returning function arguments that were passed by address

    //When not to use return by address :
    //When returning variables that were declared inside the function or parameters that were passed by value(use return by value)
    //When returning a large struct or class that was passed by reference
    //(use return by reference)

    //Return by reference:
    //Similar to pass by address, values returned by reference must be variables
    //(you should not return a reference to a literal or an expression 
    //that resolves to a temporary value, as those will go out of scope
    //at the end of the functionand you’ll end up returning a dangling reference).

    //When a variable is returned by reference, 
    //a reference to the variable is passed back to the caller. 
    //The caller can then use this reference to continue modifying the variable,
    //which can be useful at times. Return by reference is also fast,
    //which can be useful when returning structs and classes.

    //Return by reference is typically used to return arguments 
    //passed by reference to the function back to the caller.

    //std::array<int, 25> array1;
    // Set the element of array with index 10 to the value 5
    //get_element(array1, 10) = 5;
    //std::cout << array1[10] << '\n';

    //When to use return by reference:

    //When returning a reference parameter:
    //    When returning a member of an object that was passed into the function
    //    by reference or address.
    //    When returning a large struct or class that will not be destroyed 
    //    at the end of the function(e.g.one that was passed in by reference)

    //When not to use return by reference :
    //    When returning variables that were declared inside the function
    //    or parameters that were passed by value(use return by value)
    //    When returning a built - in array or pointer value(use return by address)

    //Mixing return references and values
    //Although a function may return a value or a reference, 
    //the caller may or may not assign the result to a variable or reference accordingly.

    //int returnByValue()
    //{
    //    return 5;
    //}

    //int& returnByReference()
    //{
    //    static int x{ 5 }; // static ensures x isn't destroyed when the function ends
    //    return x;
    //}

    //int giana{ returnByReference() }; 
    // case A -- ok, treated as return by value
    //int& ref{ returnByValue() }; 
    // case B -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
    //const int& cref{ returnByValue() }; 
    // case C -- ok, the lifetime of the return value is extended to the lifetime of cref

    //In case A, we’re assigning a reference return value to a non-reference variable. 
    //Because giana isn’t a reference, the return value is copied into giana, 
    //as if returnByReference() had returned by value.

    //In case B, we’re trying to initialize reference ref with the copy 
    //of the return value returned by returnByValue(). 
    //However, because the value being returned doesn’t have an address 
    //(it’s an r-value), this will cause a compile error.

    //In case C, we’re trying to initialize const reference cref with the 
    //copy of the return value returned by returnByValue().
    //Because const references can bind to r-values, there’s no problem here. 
    //Normally, r-values expire at the end of the expression 
    //in which they are created -- however, when bound to a const reference, 
    //the lifetime of the r-value (in this case, the return value of the function)
    //is extended to match the lifetime of the reference (in this case, cref)

    //Lifetime extension doesn’t save dangling references
    //const int& returnByReference()
    //{
    //    return 5;
    //}

    //int main()
    //{
    //    const int& ref{ returnByReference() }; // runtime error
    //}

    //In the above program, returnByReference() is returning a const reference to a
    //value that will go out of scope when the function ends.
    //This is normally a no-no, as it will result in a dangling reference.

    //However, we also know that assigning a value to a const reference 
    //can extend the lifetime of that value. 
    //So which takes precedence here? Does 5 go out of scope first,
    //or does ref extend the lifetime of 5?

    //The answer is that 5 goes out of scope first, 
    //then the reference to 5 is copied back to the caller,
    //and then ref extends the lifetime of the now-dangling reference.

    //const int& ref{ return_by_value(5) };
    // ok, we're extending the lifetime of the copy passed back to main

    // Returning multiple values

    //out parameters provide one method for passing multiple bits of data back to the caller.
    //don’t recommend this method.

    //Struct_param sas{ return_struct() };
    //std::cout << sas.m_x << ' ' << sas.m_y << '\n';
    //A way (introduced in C++11) is to use std::tuple. 
    //A tuple is a sequence of elements that may be different types, 
    //where the type of each element must be explicitly specified.
    //std::tuple<int, double> return_tuple();
    //std::tuple s{ return_tuple() };
    // get our tuple
    // std::cout << std::get<0>(s) << ' ' << std::get<1>(s) << '\n';
    // use std::get<n> to get the nth element of the tuple

    //int aa;
    //double bb;
    //std::tie(aa, bb) = return_tuple();
    // put elements of tuple in variables a and b
    //std::cout << aa << ' ' << bb << '\n';
    //As of C++17, a structured binding declaration can be used to simplify 
    //splitting multiple returned values into separate variables:
    //auto [ab, ba] { return_tuple() }; // used structured binding declaration to put results of tuple in variables a and b
    //std::cout << ab << ' ' << ba << '\n';

    //Using a struct is a better option than a tuple if you’re using the 
    //struct in multiple places. However, 
    //for cases where you’re just packaging up these values to return 
    //and there would be no reuse from defining a new struct, 
    //a tuple is a bit cleaner since it doesn’t introduce a new user-defined data type.
    // we don't live up to our levels of expections we fall to the level of our traning

    //Conclusion
    //Most of the time, 
    //return by value will be sufficient for your needs.
    //It’s also the most flexibleand safest way to return information to the caller.
    //However, return by reference or address can also be useful, 
    //particularly when working with dynamically allocated classes or structs.
    //When using return by reference or address, 
    //make sure you are not returning a reference to, 
    //or the address of, a variable that will go out of scope when the function returns!
//}


