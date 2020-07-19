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

void set_to_null(int* temp_ptr);
void passing_arguments_by_address(const int* array, int length);
void set_to_six(int* tempPtr);
void setToNull(int*& tempPtr);
void foo1(int value);
void foo2(int& reference);
void foo3(int* address);
void get_address();

int return_by_value(int x);
int* return_by_address(int x);
int* allocate_array(int size);
int& get_element(std::array<int, 25>& array, int index);

//struct Struct_param
//{
//    int m_x;
//    double m_y;
//};

//Struct_param return_struct()
//{
//    Struct_param s;
//    s.m_x = 5;
//    s.m_y = 6.7;
//    return s;
//}
//void returning_values_by_value_reference_and_address();

int sum_to(const int value);

struct Employee
{
    std::string name{};
    int id{};
};

void print_employee_name(const Employee& employee);
int get_index_of_largest_value(const std::vector<int>& array);
const std::string& getElement(const std::vector<std::string>& array, const int index);
void lesson_7_quiz();

int overloaded(int value);
double overloaded(double value);
void print(unsigned int value);
void print(float value);
void function_overloading();




#endif // !LESSON_7

