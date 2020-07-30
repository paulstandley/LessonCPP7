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

    //Now that you know how to provide command line arguments to a program, 
    //the next step is to access them from within our C++ program. 
    //To do that, we use a different form of main() than we’ve seen before. 
    //This new form of main() takes two arguments (named argc and argv by convention)
    //as follows:

    //int main(int argc, char* argv[])
    
    //You will sometimes also see it written as :

    //int main(int argc, char** argv)
       
    //Even though these are treated identically,
    //we prefer the first representation because it’s intuitively easier to understand.

    //argc is an integer parameter containing a count of the number of arguments
    //passed to the program(think: argc = argument count).
    //argc will always be at least 1, because the first argument is always the name
    //of the program itself.
    //Each command line argument the user provides will cause argc to increase by 1.

    //argv is where the actual argument values are stored
    //(think: argv = argument values, though the proper name is “argument vectors”).
    //Although the declaration of argv looks intimidating, 
    //argv is really just an array of C-style strings.
    //The length of this array is argc.

    // Program: MyArgs
    //#include <iostream>

    //int main(int argc, char* argv[])
    //{
    //    std::cout << "There are " << argc << " arguments:\n";

        // Loop through each argument and print its number and value
    //    for (int count{ 0 }; count < argc; ++count)
    //        std::cout << count << " " << argv[count] << '\n';

    //    return 0;
    //}

    //Now, when we invoke this program (MyArgs) with the command line arguments 
    //“Myfile.txt” and “100”, the output will be as follows:

    //There are 3 arguments:
    //0 C : \MyArgs
    //1 Myfile.txt
    //2 100

    //Argument 0 is the path and name of the current program being run.
    //Argument 1 and 2 in this case are the two command line parameters we passed in.

    //Dealing with numeric arguments

    //Command line arguments are always passed as strings,
    //even if the value provided is numeric in nature.
    //To use a command line argument as a number, 
    //you must convert it from a string to a number.
    //Unfortunately, C++ makes this a little more difficult than it should be.

    //#include <iostream>
    //#include <string>
    //#include <sstream> // for std::stringstream
    //#include <cstdlib> // for std::exit()

    //int main(int argc, char* argv[])
    //{
    //if (argc <= 1)
    //{
        // On some operating systems, argv[0] can end up as an empty string instead of the program's name.
        // We'll conditionalize our response on whether argv[0] is empty or not.
    //    if (argv[0])
    //        std::cout << "Usage: " << argv[0] << " <number>" << '\n';
    //    else
    //        std::cout << "Usage: <program name> <number>" << '\n';

    //    std::exit(1);
    //}

    //std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]

    //int myint{};
    //if (!(convert >> myint)) // do the conversion
    //    myint = 0; // if conversion fails, set myint to a default value

    //std::cout << "Got integer: " << myint << '\n';

    //return 0;
    //}


    //std::stringstream works much like std::cin.
    //In this case, we’re initializing it with the value of argv[1],
    //so that we can use operator>> to extract the value to an integer variable 
    //(the same as we would with std::cin).

    //The OS parses command line arguments first

    //When you type something at the command line(or run your program from the IDE), 
    //it is the operating system’s responsibility to translateand route that request
    //as appropriate.This not only involves running the executable, 
    //it also involves parsing any arguments to determine how they should
    //be handledand passed to the application.

    //Generally, operating systems have special rules about how special
    //characters like double quotesand backslashes are handled
    
    //Conclusion

    //Command line arguments provide a great way for users or other programs
    //to pass input data into a program at startup.
    //Consider making any input data that a program requires at startup to operate
    //a command line parameter.
    //If the command line isn’t passed in, you can always detect thatand 
    //ask the user for input.That way, your program can operate either way.
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
