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
#include "Header.h"


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

void returning_values_by_value_reference_and_address()
{
    int value{ return_by_value(33) };
    std::cout << "Return by value : " << value << '\n';

    int* address{ return_by_address(44) };
    std::cout << "Return by address : " << &address << '\n';

    // Return by address was often used to return 
    // dynamically allocated memory to the caller:
    int* array{ allocate_array(25) };
    // do stuff with array
    delete[] array;

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

    std::array<int, 25> array1;
    // Set the element of array with index 10 to the value 5
    get_element(array1, 10) = 5;
    std::cout << array1[10] << '\n';

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

    const int& ref{ return_by_value(5) }; 
    // ok, we're extending the lifetime of the copy passed back to main
}

int main()
{
    returning_values_by_value_reference_and_address();

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
