#ifndef LESSON_7

void std_reduce();
enum Items
{
    potions = 2,
    torches = 5,
    arrows = 10
};
void question1();
int countTotalItems(const int value);

void examplecode();

struct  Student
{
    std::string first_name{};
    int grade{};
};
std::string get_name();
int get_grade();
bool compareStudents(const Student& a, const Student& b);
void question2();

void question3(int one, int two);
void question4(const char* stringy2);

void question5();

//////// Card game question 6  //////////

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

void printCard(const Card& card);

// aliases
using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
    deck_type deck{};
    index_type card{ 0 };

    auto suits{ static_cast<int>(CardSuit::MAX_SUITS) };
    auto ranks{ static_cast<int>(CardRank::MAX_RANKS) };

    for (int suit{ 0 }; suit < suits - 1; ++suit)
    {
        for (int rank{ 0 }; rank < ranks - 1; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }
    }
    return deck;
}

void printDeck(const deck_type& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << '\n';
}

void shuffleDeck(deck_type& deck)
{
    // mt is static so it only gets seeded once.
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card);
void question6();


#endif // !LESSON_7

