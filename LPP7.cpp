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


