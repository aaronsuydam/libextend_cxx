/**
 * @file random_test.cpp
 * @author Suydam, Aaron J. (aaron.suydam@ufl.edu)
 * @brief 
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../include/random.hpp"

#define BOOST_TEST_MODULE RandomUtilsTests

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(RandomUtilsTests);

BOOST_AUTO_TEST_CASE(single_random_number)
{
    auto rand = generate_random_number<int>(1, 1000);
    BOOST_CHECK( rand >= 1 );
    BOOST_CHECK( rand <= 1000 );
}

BOOST_AUTO_TEST_CASE(fill_vector)
{
    vector<float> rand_vect = random_vector<float>(0, 1000, 50);
    BOOST_CHECK( rand_vect.size() == 50);
}