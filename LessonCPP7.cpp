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
#include <iterator> // for std::size
#include "Header.h"


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
        const int *ptr{ &x };
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


int main()
{
    question5();

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
