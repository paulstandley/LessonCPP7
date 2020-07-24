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


void print_stack(const std::vector<int>& stack)
{
    for (auto element : stack)
        std::cout << element << ' ';
    std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
}

void std_vector_capacity_and_stack_behavior()
{
    //std::vector capacity and stack behavior
    //Length vs capacity

    int* array0{ new int[10] { 1, 2, 3, 4, 5 } };
    delete[] array0;
    //We would say that this array has a length of 10, even though we’re only using 5
    //of the elements that we allocated

    //However, what if we only wanted to iterate over the elements we’ve initialized, 
    //reserving the unused ones for future expansion? 
    //In that case, we’d need to separately track how many elements were “used”
    //from how many elements were allocated. 
    //Unlike a built-in array or a std::array, 
    //which only remembers its length, 
    //std::vector contains two separate attributes: length and capacity. 
    //In the context of a std::vector, length is how many elements are being used 
    //in the array, whereas capacity is how many elements were allocated in memory.

    std::vector<int> array1{ 0, 1, 2 };
    array1.resize(5); // set length to 5
    std::cout << "The length is: " << array1.size() << '\n';
    for (auto element : array1)
        std::cout << element << ' ';

    //In the above example, we’ve used the resize() 
    //function to set the vector’s length to 5.
    //This tells variable array that we’re intending to use the first 5 elements
    //of the array, so it should consider those in active use. 
    //However, that leaves an interesting question: 
    //what is the capacity of this array?

    std::cout << "The length is: " << array1.size() << '\n';
    std::cout << "The capacity is: " << array1.capacity() << '\n';

    //More length vs. capacity

    //Why differentiate between lengthand capacity ? 
    //std::vector will reallocate its memory if needed,
    //but like Melville’s Bartleby, it would prefer not to, 
    //because resizing an array is computationally expensive.Consider the following

    std::vector<int> array2{};
    array2 = { 0, 1, 2, 3, 4 }; // okay, array length = 5
    std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';

    array2 = { 9, 8, 7 }; // okay, array length is now 3!
    std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';
    std::cout << '\n';

    //Note that although we assigned a smaller array to our vector, 
    //it did not reallocate its memory (the capacity is still 5). 
    //It simply changed its length, 
    //so it knows that only the first 3 elements are valid at this time.

    //Array subscripts and at() are based on length, not capacity

    //The range for the subscript operator ([]) and at() function is based on the the
    //vector’s length, not the capacity. 
    //Consider the array in the previous example, which has length 3 and capacity 5.
    //What happens if we try to access the array element with index 4? 
    //The answer is that it fails, since 4 is greater than the length of the array.

    //Note that a vector will not resize itself based on a call to the subscript 
    //operator or at() function

    std::vector<int> stack{};

    print_stack(stack);

    stack.push_back(5); // push_back() pushes an element on the stack
    print_stack(stack);

    stack.push_back(3);
    print_stack(stack);

    stack.push_back(2);
    print_stack(stack);

    std::cout << "top: " << stack.back() << '\n'; // back() returns the last element

    stack.pop_back(); // pop_back() pops an element off the stack
    print_stack(stack);

    stack.pop_back();
    print_stack(stack);

    stack.pop_back();
    print_stack(stack);

    //We can see that the capacity was preset to 5 and didn’t change
    //over the lifetime of the program

    //Vectors may allocate extra capacity
    //When a vector is resized, the vector may allocate more capacity than is needed.
    //This is done to provide some “breathing room” for additional elements, 
    //to minimize the number of resize operations needed.
    //Let’s take a look at this

    std::vector<int> v{ 0, 1, 2, 3, 4 };
    std::cout << '\n';
    std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
    for (auto element : v)
        std::cout << element << ' ';
    std::cout << '\n';
    v.push_back(5); // add another element
    std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
    for (auto element : v)
        std::cout << element << ' ';
    std::cout << '\n';

    //When we used push_back() to add a new element,
    //our vector only needed room for 6 elements, but allocated room for 7.
    //This was done so that if we were to push_back() another element,
    //it wouldn’t need to resize immediately.

    //If, when, and how much additional capacity is allocated
    //is left up to the compiler implementer.
}


int main()
{
    std_vector_capacity_and_stack_behavior();
    

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
