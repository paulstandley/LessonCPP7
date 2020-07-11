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

enum class CardSuit
{
    SUIT_SPADE,
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    MAX_SUITS
};

enum class CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card &card)
{
    // Card struct with CardRank and CardSuit enums
    switch (card.rank)
    {
    case CardRank::RANK_2:
        std::cout << '2';
    case CardRank::RANK_3:
        std::cout << '3';
    case CardRank::RANK_4:
        std::cout << '4';
    case CardRank::RANK_5:
        std::cout << '5';
    case CardRank::RANK_6:
        std::cout << '6';
    case CardRank::RANK_7:
        std::cout << '7';
    case CardRank::RANK_8:
        std::cout << '8';
    case CardRank::RANK_9:
        std::cout << '9';
    case CardRank::RANK_10:
        std::cout << '10';
    case CardRank::RANK_JACK:
        std::cout << 'J';
    case CardRank::RANK_QUEEN:
        std::cout << 'Q';
    case CardRank::RANK_KING:
        std::cout << 'K';
    case CardRank::RANK_ACE:
        std::cout << 'A';

    default:
        std::cout << '?';
        break;
    }

    switch (card.suit)
    {
    case CardSuit::SUIT_CLUB:
        std::cout << 'C';
    case CardSuit::SUIT_SPADE:
        std::cout << 'S';
    case CardSuit::SUIT_HEART:
        std::cout << 'H';
    case CardSuit::SUIT_DIAMOND:
        std::cout << 'D';

    default:
        std::cout << '?';
        break;
    }

}

void question6()
{
    // Let’s pretend we’re writing a card game.

    // (a) A deck of cards has 52 unique cards(13 card ranks of 4 suits).
    //Create enumerations for the card ranks(2, 3, 4, 5, 6, 7, 8, 9, 10, 
    //Jack, Queen, King, Ace)and suits(clubs, diamonds, hearts, spades).
    //Those enumerators will not be used to index arrays.

    //b) Each card will be represented by a struct named Card that contains a rank and a suit. 
    //Create the struct.

    //c) Create a printCard() function that takes a const Card reference as a parameter 
    //and prints the card rank and suit as a 2-letter code 
    //(e.g. the jack of spades would print as JS).
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
