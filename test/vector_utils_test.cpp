#define BOOST_TEST_MODULE Vector_Utils_Test

#include "../include/vector_utils.hpp"
#include <boost/test/unit_test.hpp>
using namespace std;

BOOST_AUTO_TEST_CASE( print_contents_test )
{
    vector<int> vec = {1, 2, 3, 4, 5};
    libex::vector_utils::print_contents(vec);
}

