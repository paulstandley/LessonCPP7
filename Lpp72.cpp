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
#include <cstdarg> // needed to use ellipsis
#include "Header.h"


void printStringerr(const char* cstring)
{
    // Only print if cstring is non-null
    if (cstring)
        std::cout << cstring;
    else
        std::cerr << "function printString() received a null parameter";
}

int getArrayValueerr(const std::array<int, 10>& array, int index)
{
    // use if statement to detect violated assumption
    if (index < 0 || index >= static_cast<int>(array.size()))
        std::exit(2); // terminate program and return error number 2 to OS

    return array[index];
}

void helloworlderr()
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

void helloword1err()
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer
            index = -1; // ensure index has an invalid value so the loop doesn't terminate
            continue; // this continue may seem extraneous, but it explicitly signals an intent to terminate this loop iteration...
        }

        // ...just in case we added more stuff here later

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any remaining characters in the input buffer

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

    helloworlderr();

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

    //3) If we want to terminate the program immediately, the exit function that lives in 
    //<cstdlib> can be used to return an error code to the operating system:

    //#include <cstdlib> // for std::exit()
    //#include <array>

    //int getArrayValue(const std::array<int, 10>& array, int index)
    //{
        // use if statement to detect violated assumption
    //    if (index < 0 || index >= static_cast<int>(array.size()))
    //        std::exit(2); // terminate program and return error number 2 to OS

    //    return array[index];
    //}

    //If the caller passes in an invalid index, this program will terminate immediately 
    //(with no error message) and pass error code 2 to the operating system.

    //4) If the user has entered invalid input, ask the user to enter the input again.

    helloword1err();

    //5) cerr is another mechanism that is meant specifically for printing error messages.
    //cerr is an output stream (just like cout) that is defined in <iostream>. 
    //Typically, cerr writes the error messages on the screen (just like cout),
    //but it can also be individually redirected to a file.

    printStringerr("Hay");

    //In the above example, we not only skip the bad line, 
    //we also log an error so the user can later determine why the 
    //program didn’t execute as expected.

    //6) If working in some kind of graphical environment 
    //(eg. MFC, SDL, QT, etc…),
    //it is common to pop up a message box with an error code and then
    //terminate the program. 
    //The specific details of how to do this depend on the environment.
}

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
    assert(gravity > 0.0);
    // The object won't reach the ground unless there is positive gravity.
    if (initialHeight <= 0.0)
    {
        // The object is already on the ground. Or buried.
        return 0.0;
    }
    return std::sqrt((2.0 * initialHeight) / gravity);
}

void assert_and_static_assert()
{
    //Using a conditional statement to detect a violated assumption,
    //along with printing an error message and terminating the program,
    //is such a common response to problems that C++ provides a shortcut 
    //method for doing this. This shortcut is called an assert.

    //An assert statement is a preprocessor macro that evaluates
    //a conditional expression at runtime. 
    //If the conditional expression is true,
    //the assert statement does nothing.
    //If the conditional expression evaluates to false,
    //an error message is displayed and the program is terminated.
    //This error message contains the conditional expression that failed, 
    //along with the name of the code file and the line number of the assert.
    //This makes it very easy to tell not only what the problem was,
    //but where in the code the problem occurred.
    //This can help with debugging efforts immensely.

    std::cout << "Took "
        << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

    //When the program calls calculateTimeUntilObjectHitsGround(100.0, -9.8),
    //the program prints a message similar to this:
    //dropsimulator: src / main.cpp : 6 : double calculateTimeUntilObjectHitsGround(double, 
    //double) : Assertion `gravity > 0.0' failed.

    //We encourage you to use assert statements liberally throughout your code.
    //Making your assert statements more descriptive

    //assert(found && "Car could not be found in database");
    //Here’s why this works: A C-style string always evaluates to boolean true.
    //So if found is false, false && true = false. If found is true, 
    //true && true = true. 
    //Thus, logical AND-ing a string doesn’t impact the evaluation of the assert.
    //However, when the assert triggers, 
    //the string will be included in the assert message:

    //NDEBUG and other considerations

    //The assert() function comes with a small performance cost that is incurred
    //each time the assert condition is checked. 
    //Furthermore, asserts should (ideally) never be encountered in production code 
    //(because your code should already be thoroughly tested). 
    //Consequently, many developers prefer that asserts are only active in debug builds.
    //C++ comes with a way to turn off asserts in production code: #define NDEBUG.

    //#define NDEBUG
    // all assert() calls will now be ignored to the end of the file

    //Some IDEs set NDEBUG by default as part of the project settings
    //for release configurations. 
    //For example, in Visual Studio, 
    //the following preprocessor definitions are set at the project level: 
    //WIN32;NDEBUG;_CONSOLE. 
    //If you’re using Visual Studio and want your asserts to trigger in release builds,
    //you’ll need to remove NDEBUG from this setting.

    //Do note that the exit() functionand assert() function(if it triggers)
    //terminate the program immediately,
    //without a chance to do any further cleanup(e.g.close a file or database).
    //Because of this, they should be used judiciously
    //(only in cases where corruption isn’t likely to occur if the program terminates
    //unexpectedly).

    //There’s another type of assert called static_assert. static_assert takes the form

    //static_assert(sizeof(long) == 8, "long must be 8 bytes");
    //static_assert(sizeof(int) == 4, "int must be 4 bytes");

    //A few notes. Because static_assert is evaluated by the compiler, 
    //the conditional part of a static_assert must be able to be evaluated
    //at compile time. Because static_assert is not evaluated at runtime, 
    //static_assert statements can also be placed anywhere in the code file 
    //(even in global space).

    //In C++11, a diagnostic message must be supplied as the second parameter.
    //Since C++17, providing a diagnostic message is optional.

    //Exceptions

    //C++ provides one more method for detectingand handling errors known as exception
    //handling.The basic idea is that when an error occurs,
    //the error is “thrown”.
    //If the current function does not “catch” the error, 
    //the caller of the function has a chance to catch the error.
    //If the caller does not catch the error,
    //the caller’s caller has a chance to catch the error.
    //The error progressively moves up the stack until it is either caughtand handled,
    //or until main() fails to handle the error.
    //If nobody handles the error, the program typically terminates
    //with an exception error.
}

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


