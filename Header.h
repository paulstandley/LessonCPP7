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

void pass_by_value(int y);
void callL7Func();

void print_elements(int (&arr)[4]);
void references_to_pointers(int*& ptr);
void get_sin_cos(double degrees, double& sin_out, double& cos_out);
void add_one(int& ref);
void pass_by_ref();


#endif // !LESSON_7

