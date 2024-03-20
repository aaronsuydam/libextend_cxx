#define BOOST_TEST_MODULE Vector_Utils_Test

#include "../include/vector_utils.hpp"
#include <boost/test/unit_test.hpp>
using namespace std;

BOOST_AUTO_TEST_CASE( print_contents_vector_int )
{
    vector<int> vec = {1, 2, 3, 4, 5};
    libex::vector_utils::print_contents(vec);
}

BOOST_AUTO_TEST_CASE( print_contents_vector_string )
{
    vector<string> vec = {"one", "two", "three", "four", "five"};
    libex::vector_utils::print_contents(vec);
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