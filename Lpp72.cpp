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
#include <string_view>
#include <string>
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

// The ellipsis must be the last parameter
double findAverage2(std::string decoder, ...)
{
    double sum = 0;

    // We access the ellipsis through a va_list, so let's declare one
    va_list list;

    // We initialize the va_list using va_start.  The first parameter is
    // the list to initialize.  The second parameter is the last non-ellipsis
    // parameter.
    va_start(list, decoder);

    int count = 0;
    // Loop indefinitely
    while (true)
    {
        char codetype = decoder[count];
        switch (codetype)
        {
        default:
        case '\0':
            // Cleanup the va_list when we're done.
            va_end(list);
            return sum / count;

        case 'i':
            sum += va_arg(list, int);
            count++;
            break;

        case 'd':
            sum += va_arg(list, double);
            count++;
            break;
        }
    }
}

// The ellipsis must be the last parameter
double findAverage1(int first, ...)
{
    // We have to deal with the first number specially
    double sum = first;

    // We access the ellipsis through a va_list, so let's declare one
    va_list list;

    // We initialize the va_list using va_start.  The first parameter is
    // the list to initialize.  The second parameter is the last non-ellipsis
    // parameter.
    va_start(list, first);

    int count = 1;
    // Loop indefinitely
    while (true)
    {
        // We use va_arg to get parameters out of our ellipsis
        // The first parameter is the va_list we're using
        // The second parameter is the type of the parameter
        int arg = va_arg(list, int);

        // If this parameter is our sentinel value, stop looping
        if (arg == -1)
            break;

        sum += arg;
        count++;
    }

    // Cleanup the va_list when we're done.
    va_end(list);

    return sum / count;
}

double findAverage(int count, ...)
{// The ellipsis must be the last parameter
// count is how many additional arguments we're passing
    double sum = 0;

    // We access the ellipsis through a va_list, so let's declare one
    va_list list;

    // We initialize the va_list using va_start.  The first parameter is
    // the list to initialize.  The second parameter is the last non-ellipsis
    // parameter.
    va_start(list, count);

    // Loop through all the ellipsis arguments
    for (int arg = 0; arg < count; ++arg)
        // We use va_arg to get parameters out of our ellipsis
        // The first parameter is the va_list we're using
        // The second parameter is the type of the parameter
        sum += va_arg(list, int);

    // Cleanup the va_list when we're done.
    va_end(list);

    return sum / count;
}


void ellipsis_and_why_to_avoid_them()
{
    /*In all of the functions we’ve seen so far,
    the number of parameters a function will take must be known in advance
    (even if they have default values).
    However, there are certain cases where it can be useful to be able to pass
    a variable number of parameters to a function.

    C++ provides a special specifier known as ellipsis (aka “…”)
    that allow us to do precisely this.

    Functions that use ellipsis take the form:

    return_type function_name(argument_list, ...)

    The argument_list is one or more normal function parameters.
    Note that functions that use ellipsis must have at least one non-ellipsis parameter.
    Any arguments passed to the function must match the argument_list parameters first.

    The ellipsis (which are represented as three periods in a row)
    must always be the last parameter in the function.
    The ellipsis capture any additional arguments (if there are any).
    Though it is not quite accurate,
    it is conceptually useful to think of the ellipsis as an array
    that holds any additional parameters beyond those in the argument_list.

    */

    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

    /*As you can see, this function takes a variable number of parameters!
    Now, let’s take a look at the components that make up this example.

    First, we have to include the cstdarg header.
    This header defines va_list, va_arg, va_start, and va_end,
    which are macros that we need to use to access the parameters that are
    part of the ellipsis.

    We then declare our function that uses the ellipsis.
    Remember that the argument list must be one or more fixed parameters.
    In this case, we’re passing in a single integer that tells us how many
    numbers to average. The ellipsis always comes last.

    Note that the ellipsis parameter has no name! Instead,
    we access the values in the ellipsis through a special type known as va_list.
    It is conceptually useful to think of va_list as a pointer that points
    to the ellipsis array.
    First, we declare a va_list, which we’ve called “list” for simplicity.

    The next thing we need to do is make list point to our ellipsis parameters.
    We do this by calling va_start(). va_start() takes two parameters:
    the va_list itself, and the name of the last non-ellipsis parameter
    in the function. Once va_start() has been called, va_list points to
    the first parameter in the ellipsis.

    To get the value of the parameter that va_list currently points to,
    we use va_arg(). va_arg() also takes two parameters:
    the va_list itself, and the type of the parameter we’re trying to access.
    Note that va_arg() also moves the va_list to the next parameter in the ellipsis!

    Finally, to clean up when we are done, we call va_end(),
    with va_list as the parameter.

    Note that va_start() can be called again any time we want to reset
    the va_list to point to the first parameter in the ellipses again.

    */

    std::cout << findAverage(6, 1.0, 2, 3, 4, 5, 6) << '\n';

    /*As you have learned in previous lessons,
    a computer stores all data as a sequence of bits.
    A variable’s type tells the computer how to translate that sequence
    of bits into a meaningful value.
    However, you just learned that the ellipsis throw away the variable’s type!
    Consequently, the only way to get a meaningful value back from the ellipsis
    is to manually tell va_arg() what the expected type of the next parameter is.
    This is what the second parameter of va_arg() does.
    If the actual parameter type doesn’t match the expected parameter type,
    bad things will usually happen.

    In the above findAverage program, we told va_arg()
    that our variables are all expected to have a type of int.
    Consequently, each call to va_arg() will return the next sequence
    of bits translated as an integer.

    In this case, the problem is that the double we passed in as the first
    ellipsis argument is 8 bytes,
    whereas va_arg(list, int) will only return 4 bytes of data with each call.
    Consequently, the first call to va_arg will only read the first 4 bytes
    of the double (producing a garbage result),
    and the second call to va_arg will read the second 4 bytes of the double
    (producing another garbage result).
    Thus, our overall result is garbage.

    Because type checking is suspended,
    the compiler won’t even complain if we do something completely ridiculous,
    like this:

    */

    int value = 7;
    std::cout << findAverage(6, 1.0, 2, "Hello, world!", 'G', &value, &findAverage) << '\n';

    /*Believe it or not, this actually compiles just fine

    This result epitomizes the phrase, “Garbage in, garbage out”,
    which is a popular computer science phrase
    “used primarily to call attention to the fact that computers, unlike humans,
    will unquestioningly process the most nonsensical of input data
    and produce nonsensical output” (Wikipedia).

    So, in summary, type checking on the parameters is suspended,
    and we have to trust the caller to pass in the right type of parameters.
    If they don’t, the compiler won’t complain --
    our program will just produce garbage (or maybe crash).

    Why ellipsis are dangerous: ellipsis don’t know how many parameters were passed

    Not only do the ellipsis throw away the type of the parameters,
    it also throws away the number of parameters in the ellipsis.
    This means we have to devise our own solution for keeping track
    of the number of parameters passed into the ellipsis.
    Typically, this is done in one of three ways.

    Method 1: Pass a length parameter

    Method #1 is to have one of the fixed parameters represent the number of optional
    parameters passed.
    This is the solution we use in the findAverage() example above.

    However, even here we run into trouble. For example, consider the following call:

    */

    std::cout << findAverage(6, 1, 2, 3, 4, 5) << '\n';

    /*What happened? We told findAverage() we were going to give it 6 values,
    but we only gave it 5.
    Consequently, the first five values that va_arg()
    returns were the ones we passed in.
    The 6th value it returns was a garbage value somewhere in the stack.
    Consequently, we got a garbage answer.
    At least in this case it was fairly obvious that this is a garbage value.

    A more insidious case:
    */

    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6, 7) << '\n';

    /*This produces the answer 3.5, which may look correct at first glance,
    but omits the last number in the average,
    because we only told it we were going to provide 6 parameters
    (and then provided 7). These kind of mistakes can be very hard to catch.

    Method 2: Use a sentinel value

    Method #2 is to use a sentinel value.
    A sentinel is a special value that is used to terminate a loop when it is encountered.
    For example, with strings, the null terminator is used as a sentinel
    value to denote the end of the string.
    With ellipsis, the sentinel is typically passed in as the last parameter.
    Here’s an example of findAverage() rewritten to use a sentinel value of -1:

    */

    std::cout << findAverage1(1, 2, 3, 4, 5, -1) << '\n';
    std::cout << findAverage1(1, 2, 3, 4, 5, 6, -1) << '\n';

    /*Note that we no longer need to pass an explicit length as the first parameter.
    Instead, we pass a sentinel value as the last parameter.

    However, there are a couple of challenges here.
    First, C++ requires that we pass at least one fixed parameter.
    In the previous example, this was our count variable.

    In this example, the first value is actually part of the numbers to be averaged.
    So instead of treating the first value to be averaged as part of the ellipsis
    parameters, we explicitly declare it as a normal parameter.

    We then need special handling for it inside the function
    (in this case, we set sum to first instead of 0 to start).

    Second, this requires the user to pass in the sentinel as the last value.
    If the user forgets to pass in the sentinel value (or passes in the wrong value),
    the function will loop continuously until it runs into garbage that matches
    the sentinel (or crashes).

    Finally, note that we’ve chosen -1 as our sentinel.
    That’s fine if we only wanted to find the average of positive numbers,
    but what if we wanted to include negative numbers?
    Sentinel values only work well if there is a value that falls outside
    the valid set of values for the problem you are trying to solve.

    Method 3: Use a decoder string

    Method #3 involves passing a “decoder string”
    that tells the program how to interpret the parameters.

    */

    std::cout << findAverage2("iiiii", 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage2("iiiiii", 1, 2, 3, 4, 5, 6) << '\n';
    std::cout << findAverage2("iiddi", 1, 2, 3.5, 4.5, 5) << '\n';

    /*In this example,
    we pass a string that encodes both the number of optional variables and their types.
    The cool thing is that this lets us deal with parameters of different types.
    However, this method has downsides as well:
    the decoder string can be a bit cryptic,
    and if the number or types of the optional parameters don’t match the
    decoder string precisely, bad things can happen.

    For those of you coming from C, this is what printf does!

    Recommendations for safer use of ellipsis

    First, if possible, do not use ellipsis at all! Oftentimes,
    other reasonable solutions are available,
    even if they require slightly more work.
    For example, in our findAverage() program, we could have passed in a
    dynamically sized array of integers instead.
    This would have provided both strong type checking
    (to make sure the caller doesn’t try to do something nonsensical)
    while preserving the ability to pass a variable number of integers to be averaged.

    Second, if you do use ellipsis, do not mix expected argument types within your
    ellipsis if possible.
    Doing so vastly increases the possibility of the caller inadvertently
    passing in data of the wrong type and va_arg() producing a garbage result.

    Third, using a count parameter or decoder string as part of the argument list
    is generally safer than using a sentinel as an ellipsis parameter.
    This forces the user to pick an appropriate value for the count/decoder parameter,
    which ensures the ellipsis loop will terminate after a reasonable number of
    iterations even if it produces a garbage value.

    */
}

static bool containsNutL(std::string_view str) // static means internal linkage in this context
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. Otherwise it returns the index where the substring occurs
    // in str.
    return (str.find("nut") != std::string_view::npos);
}

void repeat(int repetitions, const std::function<void(int)>& fn)
{// We don't know what fn will be. 
    //std::function works with regular functions and lambdas.
    for (int i{ 0 }; i < repetitions; ++i)
    {
        fn(i);
    }
}

void lambdas_anonymous_functions()
{
    /*Lambdas

    A lambda expression (also called a lambda or closure)
    allows us to define an anonymous function inside another function.
    The nesting is important, as it allows us both to avoid namespace naming pollution,
    and to define the function as close to where it is used as possible
    (providing additional context).

    The syntax for lambdas is one of the weirder things in C++,
    and takes a bit of getting used to. Lambdas take the form:

    [ captureClause ] ( parameters ) -> returnType
    {
        statements;
    }

    The capture clause and parameters can both be empty if they are not needed.

    The return type is optional, and if omitted, auto will be assumed
    (thus using type inference used to determine the return type).
    While we previously noted that type inference for function return
    types should be avoided, in this context, it’s fine to use
    (because these functions are typically so trivial).

      []() {}; // defines a lambda with no captures, no parameters, and no return type

    */

    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    // Define the function right where we use it.
    auto found{ std::find_if(arr.begin(), arr.end(),
                             [](std::string_view str)
        // here's our lambda, no capture clause
                             {
                               return (str.find("nut") != std::string_view::npos);
                             }) };

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    /*Note how similar our lambda is to our containsNut function.
    They both have identical parameters and function bodies.
    The lambda has no capture clause
    (we’ll explain what a capture clause is in the next lesson)
    because it doesn’t need one.
    And we’ve omitted the trailing return type in the lambda (for conciseness),
    but since operator!= returns a bool, our lambda will return a bool too.

    Type of a lambda

    In the above example, we defined a lambda right where it was needed.
    This use of a lambda is sometimes called a function literal.

    However, writing a lambda in the same line as it’s used can sometimes
    make code harder to read.
    Much like we can initialize a variable with a literal value
    (or a function pointer) for use later,
    we can also initialize a lambda variable with a lambda definition
    and then use it later.
    A named lambda along with a good function name can make code easier to read.

    As it turns out, lambdas don’t have a type that we can explicitly use.
    When we write a lambda, the compiler generates a unique type just for the lambda
    that is not exposed to us.

    In actuality, lambdas aren’t functions
    (which is part of how they avoid the limitation of C++ not supporting nested
    functions). They’re a special kind of object called a functor.
    Functors are objects that contain an overloaded operator()
    that make them callable like a function

    Although we don’t know the type of a lambda,
    there are several ways of storing a lambda for use post-definition.
    If the lambda has an empty capture clause,
    we can use a regular function pointer.
    In the next lesson, we introduce lambda captures,
    a function pointer won’t work anymore at that point.
    However, std::function can be used for lambdas even if they are
    capturing something.

    */

    // A regular function pointer. Only works with an empty capture clause.
    double (*addNumbers1)(double, double) {
        [](double a, double b) {
            return (a + b);
        }
    };

    std::cout << addNumbers1(1, 2) << '\n';

    // Using std::function. The lambda could have a non-empty capture clause (Next lesson).
    std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
      [](double a, double b) {
        return (a + b);
      }
    };

    std::cout << addNumbers2(3, 4) << '\n';

    // Using auto. Stores the lambda with its real type.
    auto addNumbers3{
      [](double a, double b) {
        return (a + b);
      }
    };

    std::cout << addNumbers3(5, 6) << '\n';

    /*The only way of using the lambda’s actual type is by means of auto.
    auto also has the benefit of having no overhead compared to std::function.

    Unfortunately, we can’t always use auto.
    In cases where the actual lambda is unknown
    (e.g. because we’re passing a lambda to a function as a parameter and the
    caller determines what lambda will be passed in),
    we can’t use auto. In such cases, std::function should be used.

    */

    repeat(3, [](int i) {
        std::cout << i << '\n';
        });

    /*Rule

    Use auto when initializing variables with lambdas,
    and std::function if you can’t initialize the variable with the lambda.

    Generic lambdas

    For the most part, lambda parameters work by the same rules as regular function parameters.

    One notable exception is that since C++14 we’re allowed to use auto for parameters
    (note: in C++20, regular functions will be able to use auto for parameters too).
    When a lambda has one or more auto parameter,
    the compiler will infer what parameter types are needed from the calls
    to the lambda.

    Because lambdas with one or more auto parameter can potentially work with a wide variety of types, they are called generic lambdas.

    For advanced readers

    When used in the context of a lambda,
    auto is just a shorthand for a template parameter.

    */

    std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // Search for two consecutive months that start with the same letter.
    auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                        [](const auto& a, const auto& b) {
                                          return (a[0] == b[0]);
                                        }) };

    // Make sure that two months were found.
    if (sameLetter != months.end())
    {
        // std::next returns the next iterator after sameLetter
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
            << " start with the same letter\n";
    }

    /*In the above example,
    we use auto parameters to capture our strings by const reference.
    Because all string types allow access to their individual characters via operator[],
    we don’t need to care whether the user is passing in a std::string,
    C-style string, or something else.
    This allows us to write a lambda that could accept any of these,
    meaning if we change the type of months later,
    we won’t have to rewrite the lambda.

    */

    // Count how many months consist of 5 letters
    auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                         [](std::string_view str) {
                                           return (str.length() == 5);
                                         }) };

    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

    /*In this example, using auto would infer a type of const char*.
    C-style strings aren’t easy to work with (apart from using operator[]).
    In this case, we prefer to explicitly define the parameter as a std::string_view,
    which allows us to work with the underlying data much more easily
    (e.g. we can ask the string view for its length, even if the user
    passed in a C-style array).

    Generic lambdas and static variables

    One thing to be aware of is that a unique lambda will be generated for each
    different type that auto resolves to.
    The following example shows how one generic lambda turns into two distinct lambdas

    */

    // Print a value and count how many times @print has been called.
    auto printlam{
      [](auto value) {
        static int callCount{ 0 };
        std::cout << callCount++ << ": " << value << '\n';
      }
    };

    printlam("hello"); // 0: hello
    printlam("world"); // 1: world

    printlam(1); // 0: 1
    printlam(2); // 1: 2

    printlam("ding dong"); // 2: ding dong

    /*In the above example, we define a lambda and then call it with two
    different parameters (a string literal parameter,
    and an integer parameter).
    This generates two different versions of the lambda
    (one with a string literal parameter, and one with an integer parameter).

    Most of the time, this is inconsequential.
    However, note that if the generic lambda uses static duration variables,
    those variables are not shared between the generated lambdas.

    We can see this in the example above,
    where each type (string literals and integers) has its own unique count!
    Although we only wrote the lambda once,
    two lambdas were generated -- and each has its own version of callCount.
    To have a shared counter between the two generated lambdas,
    we’d have to define a variable outside of the lambda.
    For now, this means defining the variable even outside of the
    function the lambda is defined in.
    In the above example, this means adding a global variable.
    We’ll be able to avoid the global variable after talking about
    lambda captures in the next lesson.

    Return type deduction and trailing return types

    If return type deduction is used,
    a lambda’s return type is deduced from the return-statements inside the lambda.
    If return type inference is used,
    all return statements in the lambda must return the same type
    (otherwise the compiler won’t know which one to prefer).

    In the case where we’re returning different types, we have two options:

    1) Do explicit casts to make all the return types match, or

    2) explicitly specify a return type for the lambda,
    and let the compiler do implicit conversions

    */

    // note: explicitly specifying this returns a double
    auto dividelam{ [](int x, int y, bool bInteger) -> double {
      if (bInteger)
        return x / y; // will do an implicit conversion to double
      else
        return static_cast<double>(x) / y;
    } };

    std::cout << dividelam(3, 2, true) << '\n';
    std::cout << dividelam(3, 2, false) << '\n';

    /*That way, if you ever decide to change the return type,
    you (usually) only need to change the lambda’s return type,
    and not touch the lambda body.

    Standard library function objects

    For common operations (e.g. addition, negation, or comparison)
    you don’t need to write your own lambdas,
    because the standard library comes with many basic callable objects
    that can be used instead.
    These are defined in the <functional> header.

    */

    std::array arrlam{ 13, 90, 99, 5, 40, 80 };
    // Pass std::greater to std::sort
    std::sort(arrlam.begin(), arrlam.end(), std::greater{});
    // note: need curly braces to instantiate object
    for (int i : arrlam)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    /*Conclusion

    Lambdas and the algorithm library may seem unnecessarily complicated when compared
    to a solution that uses a loop. However,
    this combination can allow some very powerful operations in just a few lines
    of code, and can be more readable than writing your own loops.
    On top of that, the algorithm library features powerful
    and easy-to-use parallelism, which you won’t get with loops.
    Upgrading source code that uses library functions is easier than upgrading
    code that uses loops.

    Lambdas are great, but they don’t replace regular functions for all cases.
    Prefer regular functions for non-trivial and reusable cases.

    */

}

void lambdas_quiz()
{
    std::array<Studentlam, 8> arrstu
    {
        {
            { "Albert", 3 },
            { "Ben", 5 },
            { "Christine", 2 },
            { "Dan", 8 },
            { "Enchilada", 4 },
            { "Francis", 1 },
            { "Greg", 3 },
            { "Hagrid", 5 }
        }
    };

    auto best{
        std::max_element(arrstu.begin(), arrstu.end(), [](const auto& a, const auto& b) {
            return (a.points < b.points);
        })
    };
    std::cout << best->name << " is the best student\n";
}

void lambdas_quiz1()
{
    std::array<Seasonlam, 4> seasons
    {
        {
            { "Spring", 285.0 },
            { "Summer", 296.0 },
            { "Fall", 288.0 },
            { "Winter", 263.0 }
        }
    };

    std::sort(seasons.begin(), seasons.end(),
        // We can compare averageTemperature of the two arguments to
        // sort the array
        [](const auto& a, const auto& b)
        {
            return (a.averageTemperature < b.averageTemperature);
        });

    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }
}

