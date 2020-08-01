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

void optional_parameter(int x, int y = 10);
void multiple_default_arguments(int x = 10, int y = 20, int z = 30);
void default_arguments();

int foo();
int goo();
void function_pointers();

void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int));
bool ascending(int x, int y);
bool descending(int x, int y);
bool evensFirst(int x, int y);
void printArray(int* array, int size);
void passing_functions_as_arguments_to_other_functions();

bool fp_stop_or_go();
double fp_get_user_number();
char fp_get_user_operator();
double fp_add(const double x, const double y);
double fp_subtract(const double x, const double y);
double fp_multiply(const double x, const double y);
double fp_divide(const double x, const double y);
#include <functional>
using arithmeticFcn = std::function<double(double, double)>;
arithmeticFcn get_arithmetic_funcion(char operater_function);
void calc_user_input();
void function_pointer_quiz();

void the_stack_and_heap();

void print_stack(const std::vector<int>& stack);
void std_vector_capacity_and_stack_behavior();

// h/t to potterman28wxcv for a variant of this code
int fibonacci0(int count);

int fibonacci1(int count);
int sumTo(int sumto);
void count_down(int count);
void recursion();

void printBinary(unsigned int n);
void print_binary(int x);
int individual_digit_in_the_integer(int num);
int factorial001(int num);
void recursion_quiz();

void printStringerr(const char* cstring);
int getArrayValueerr(const std::array<int, 10>& array, int index);
void helloworlderr();
void helloword1err();
void handling_errors_cerr_and_exit();

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity);
void assert_and_static_assert();

void command_line_arguments();

double findAverage2(std::string decoder, ...);
double findAverage1(int first, ...);
double findAverage(int count, ...);
void ellipsis_and_why_to_avoid_them();

static bool containsNutL(std::string_view str);
void repeat(int repetitions, const std::function<void(int)>& fn);
void lambdas_anonymous_functions();

struct Studentlam
{
    std::string name{};
    int points{};
};

struct Seasonlam
{
    std::string_view name{};
    double averageTemperature{};
};

void lambdas_quiz();
void lambdas_quiz1();


#endif // !LESSON_7

