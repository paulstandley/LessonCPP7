#include "pch.h"
#include <algorithm> // std::shuffle sort
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <execution>
#include "Header.h"


struct  Student
{
    std::string first_name{};
    int grade{};
};

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


int main()
{
    question2();

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
