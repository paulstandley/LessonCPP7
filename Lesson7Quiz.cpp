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



/*

int iiii{};
static int jjjj{};

int getValuelamb()
{
    return 0;
}

void lambdas_captures_quiz()
{
    int aa{};
    constexpr int bb{};
    static int cc{};
    static constexpr int dd{};
    const int ee{};
    const int ff{ getValuelamb() };
    static const int gg{};
    static const int hh{ getValuelamb() };

    []() {
        // Try to use the variables without explicitly capturing them.
        //aa;
        bb;
        cc;
        dd;
        ee;
        //ff;
        gg;
        hh;
        iiii;
        jjjj;
    }();

    /*
    aa	No. aa has automatic storage duration.
    bb	Yes. bb is usable in a constant expression.
    cc	Yes. cc has static storage duration.
    dd	Yes.
    ee	Yes. ee is usable in a constant expression.
    ff	No. ff‘s value depends on getValue, which might require the program to run.
    gg	Yes.
    hh	Yes. hh has static storage duration.
    iiii	Yes. iiii is a global variable.
    jjjj	Yes. jjjj is accessible in the entire file.
}
*/
    



