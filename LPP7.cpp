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

