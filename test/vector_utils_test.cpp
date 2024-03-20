#define BOOST_TEST_MODULE Vector_Utils_Test

#include "../include/vector_utils.hpp"
#include "../include/testing.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/process.hpp>
#include <sstream>
#include <fstream>
using namespace std;
using namespace libex::Testing;
using namespace libex::vector_utils;

struct Person
{
    string name;
    int age;
};

void print_person(const Person &p)
{
    cout << "Name: " << p.name << ", Age: " << p.age << endl;
}



BOOST_AUTO_TEST_CASE( print_contents_vector_int )
{
    vector<int> vec = {1, 2, 3, 4, 5};
    auto print_contents_int_lambda = [&vec](){ print_contents<int>(vec); };
    string result = test_and_capture_output(print_contents_int_lambda);
    BOOST_CHECK_EQUAL(result, "1 2 3 4 5\n");
}

BOOST_AUTO_TEST_CASE( print_contents_vector_string )
{
    vector<string> vec = {"one", "two", "three", "four", "five"};
    auto print_contents_string_lambda = [&vec](){ print_contents<string>(vec); };
    string result = test_and_capture_output(print_contents_string_lambda);
    BOOST_CHECK_EQUAL(result, "one two three four five\n");
}

BOOST_AUTO_TEST_CASE( print_contents_vector_object_1 )
{
    vector<Person> vec = {{"John", 25}, {"Doe", 30}, {"Jane", 20}};
    auto print_contents_person_lambda = [&vec](){ print_contents<Person>(vec, print_person); };
    string result = test_and_capture_output(print_contents_person_lambda);
    BOOST_CHECK_EQUAL(result, "Name: John, Age: 25\nName: Doe, Age: 30\nName: Jane, Age: 20\n");
}

BOOST_AUTO_TEST_CASE( stringify_vector_int )
{
    vector<int> vec = {1, 2, 3, 4, 5};
    string result = libex::vector_utils::stringify(vec);
    BOOST_CHECK_EQUAL(result, "1 2 3 4 5");
}

BOOST_AUTO_TEST_CASE( stringify_vector_string )
{
    vector<string> vec = {"one", "two", "three", "four", "five"};
    string result = libex::vector_utils::stringify(vec);
    BOOST_CHECK_EQUAL(result, "one two three four five");
}