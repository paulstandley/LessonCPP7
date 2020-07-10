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

#endif // !LESSON_7

