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



void helloworld()
{
    std::string hello{ "Hello, world!" };
    int index;

    do
    {
        std::cout << "Enter an index: ";
        std::cin >> index;

        //handle case where user entered a non-integer
        if (std::cin.fail())
        {
            std::cin.clear(); // reset any error flags
            std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer
            index = -1; // ensure index has an invalid value so the loop doesn't terminate
            continue; // this continue may seem extraneous, but it explicitly signals an intent to terminate this loop iteration
        }

    } while (index < 0 || index >= static_cast<int>(hello.size())); // handle case where user entered an out of range integer

    std::cout << "Letter #" << index << " is " << hello[index] << '\n';
}

void handling_errors_cerr_and_exit()
{
    //When writing programs, 
    //it is almost inevitable that you will make mistakes.
    //In this function, we will talk about the different kinds of errors that are made,
    //and how they are commonly handled.

    //Errors fall into two categories : syntax and semantic errors.

    //Syntax errors

    //A syntax error occurs when you write a statement
    //that is not valid according to the grammar of the C++ language. For example:
    //if 5 is not equal to 6 then write "not equal";

    //Although this statement is understandable by humans, 
    //it is not valid according to C++ syntax. The correct C++ statement would be:

    if (5 != 6)
        std::cout << "not equal" << '\n';

    //Syntax errors are almost always caught by the compiler and are usually easy to fix.
    //Consequently, we typically don’t worry about them too much.

    //Semantic errors
    //A semantic error occurs when a statement is syntactically valid, 
    //but does not do what the programmer intended. For example:

    for (int count{ 0 }; count <= 3; ++count)
        std::cout << count << ' ';
    std::cout << '\n';

    //The programmer may have intended this statement
    //to print 0 1 2, but it actually prints 0 1 2 3.

    //Semantic errors are not caught by the compiler,
    //and can have any number of effects:
    //they may not show up at all, 
    //cause the program to produce the wrong output, 
    //cause erratic behavior, corrupt data, or cause the program to crash.

    //Semantic errors can occur in a number of ways. 
    //One of the most common semantic errors is a logic error. 
    //A logic error occurs when the programmer incorrectly 
    //codes the logic of a statement. 
    //The above for statement example is a logic error.

    int xx{ 0 };
    if (xx >= 5)
        std::cout << "xx is greater than 5" << '\n';

    //What happens when x is exactly 5? The conditional expression evaluates to true,
    //and the program prints “x is greater than 5”.
    //Logic errors can be easy or hard to locate, 
    //depending on the nature of the problem.

    //Another common semantic error is the violated assumption. 
    //A violated assumption occurs when the programmer assumes that something
    //will be either true or false, and it isn’t. For example:


    std::string hello{ "Hello, world!" };
    std::cout << "Enter an index: ";

    int index;
    std::cin >> index;

    std::cout << "Letter #" << index << " is " << hello[index]
        << " in " << hello << '\n';

    //See the potential problem here? 
    //The programmer has assumed that the user will enter a value 
    //between 0 and the length of “Hello, world!”. 
    //If the user enters a negative number, or a large number, 
    //the array index will be out of bounds. 
    //In this case, since we are just reading a value, 
    //the program will probably print a garbage letter.
    //But in other cases, the erroneous statement might corrupt other variables
    //or cause the program to crash.

    //Defensive programming is a form of program design that involves trying to
    //identify areas where assumptions may be violated, 
    //and writing code that detects and handles any violation
    //of those assumptions so that the program reacts in a predictable
    //way when those violations do occur.

    //Detecting assumption errors

    //As it turns out, we can catch almost all assumptions that need to be checked
    //in one of three locations :

    //1 When a function has been called, the caller may have passed the 
    //function parameters that are incorrect or semantically meaningless.

    //2 When a function returns, the return value may indicate that an error has occurred.

    //3 When program receives input (either from the user, or a file), 
    //the input may not be in the correct format.

    //Consequently, the following rules should be used when programming defensively

    //1 At the top of each function, 
    //check to make sure any parameters have appropriate values.

    //2 After a function has returned, check the return value (if any), 
    //and any other error reporting mechanisms, to see if an error occurred.

    //3 Validate any user input to make sure it meets
    //the expected formatting or range criteria.

    // Let’s take a look at examples of each of these.

    //Problem: When a function is called, the caller may have passed the 
    //function parameters that are semantically meaningless.

    //void printString(const char *cstring)
    //{
    //    std::cout << cstring;
    //}

    //Can you identify the assumption that may be violated? 
    //The answer is that the caller might pass in a null pointer 
    //instead of a valid C-style string. 
    //If that happens, the program will crash. 
    //Here’s the function again with code that checks to make sure
    //the function parameter is non-null:

    //void printString(const char *cstring)
    //{
    //  Only print if cstring is non-null
    //    if (cstring)
    //        std::cout << cstring;
    //}

    //Problem: When a function returns, 
    //the return value may indicate that an error has occurred.

    //std::string hello{ "Hello, world!" };
    //std::cout << "Enter a letter: ";
    //char ch;
    //std::cin >> ch;
    //int index{ static_cast<int>(hello.find(ch)) };
    //std::cout << ch << " was found at index " << index << '\n';

    //Can you identify the assumption that may be violated? 
    //The answer is that the user may enter a character that isn’t in the string. 
    //If that happens, the find() function will return an index of -1, 
    //which will get printed.

    //std::string hello{ "Hello, world!" };
    //std::cout << "Enter a letter: ";
    //char ch;
    //std::cin >> ch;
    //int index{ static_cast<int>(hello.find(ch)) };
    //if (index != -1) // handle case where find() failed to find the character in the string
    //    std::cout << ch << " was found at index " << index << '\n';
    //else
    //    std::cout << ch << " wasn't found" << '\n';

    //Problem: When program receives input (either from the user, or a file),
    //the input may not be in the correct format. 
    //Here’s the sample program you saw previously that illustrates this flaw:

    //std::string hello{ "Hello, world!" };
    //std::cout << "Enter an index: ";
    //int index;
    //std::cin >> index;
    //std::cout << "Letter #" << index << " is " << hello[index] << '\n';

    helloworld();

    //Note that this last example has two-levels of error checking: 
    //first, we need to make sure the user’s input was properly read 
    //into variable index. 
    //Then we needed to ensure index was within range of the array.

    //Handling assumption errors

    //Now that you know where assumption errors typically occur, 
    //let’s talk about different ways to handle them when they do occur.
    //There is no best way to handle an error -- it really depends
    //on the nature of the problem and whether the problem can be fixed or not.

    //1) Quietly skip the code that depends on the assumption being valid:

    //void printString(const char* cstring)
    //{
    //    Only print if cstring is non-null
    //    if (cstring)
    //        std::cout << cstring;
    //}
    
    //In the above example, if cstring is null, we don’t print anything.
    //We have skipped the code that depends on cstring being non - null.
    //This can be a good option if the statement being skipped isn’t criticaland
    //doesn’t impact the program logic.
    //The primary challenge with doing so is that the caller or user
    //have no way to identify that something went wrong

    //// assume the array only holds positive values
    //int getArrayValue(const std::array<int, 10>& array, int index)
    //{
        // use if statement to detect violated assumption
    //    if (index < 0 || index >= static_cast<int>(array.size()))
    //        return -1; // return error code to caller
    //    return array[index];
    //}

    //In this case, the function returns -1 if the caller passes in an invalid index.
    //Returning an enumerated value would be even better.

    //This method only works if you can find a return value that can’t naturally
    //be in set of normal return values for that function.
    //For example, if the array above could hold negative numbers, 
    //then array might return -1 normally.
    //This precludes using that value to indicate an error.


}


int main()
{
    handling_errors_cerr_and_exit();
    

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
