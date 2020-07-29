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
#include "Header.h"


void command_line_arguments()
{
    //Command line arguments are optional string arguments that are passed
    //by the operating system to the program when it is launched.
    //The program can then use them as input (or ignore them).
    //Much like function parameters provide a way for a function
    //to provide inputs to another function,
    //command line arguments provide a way for people or programs
    //to provide inputs to a program.

    //Passing command line arguments

    //Executable programs can be run on the command line by invoking them by name.
    //For example, to run the executable file “WordCount” that is located
    //in the root directory of the C : drive on a Windows machine, you could type :

    //C:\ > WordCount

    //In order to pass command line arguments to WordCount, 
    //we simply list the command line arguments after the executable name:

    //C:\ > WordCount Myfile.txt

    //Now when WordCount is executed, 
    //Myfile.txt will be provided as a command line argument.
    //A program can have multiple command line arguments, separated by spaces :

    //C:\ > WordCount Myfile.txt Myotherfile.txt

    //This also works for other command line operating systems,
    //such as Linux(although your prompt and directory structure will undoubtedly vary).

    //If you are running your program from an IDE, 
    //the IDE should provide a way to enter command line arguments.

    //In Microsoft Visual Studio, 
    //right click on your project in the solution explorer, then choose properties.
    //Open the “Configuration Properties” tree element,
    //and choose “Debugging”.
    //In the right pane, there is a line called “Command Arguments”.
    //You can enter your command line arguments there for testing, 
    //and they will be automatically passed to your program when you run it.

    //In Code::Blocks, choose “Project->Set program’s arguments”.

    //Using command line arguments
}


int main()
{
    
    

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
