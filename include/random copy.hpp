/**
 * @file random.hpp
 * @author Suydam, Aaron J. (aaron.suydam@ufl.edu)
 * @brief 
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace chrono;




/**
 * @brief 
 * The goal here is to build a set of utilities that revolve around random numbers.
 * Random times, vectors and arrays that are automatically populated with random
 * integers, floats, etc. 
 */

/**
 * @brief 
 * 
 * @tparam T 
 * @param lower_bound 
 * @param upper_bound 
 * @return T 
 */
template <typename T, enable_if_t<is_integral<T>::value, bool> = true>
T generate_random_number(T lower_bound, T upper_bound)
{
    std::random_device seed;
    std::mt19937 mersenne_generator(seed());
    uniform_int_distribution<T> spread(lower_bound, upper_bound);
    return spread(mersenne_generator);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param lower_bound 
 * @param upper_bound 
 * @return T 
 */
template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
T generate_random_number(T lower_bound, T upper_bound)
{
    std::random_device seed;
    std::mt19937 mersenne_generator(seed());
    uniform_real_distribution<T> spread(lower_bound, upper_bound);
    return spread(mersenne_generator);
}

template <typename T>
vector<T> random_vector(T lower_bound, T upper_bound, size_t num_elements)
{
    std::vector<T> to_return;
    to_return.reserve(num_elements);
    for (size_t i = 0; i < num_elements; i++)
    {
        auto rand = generate_random_number<T>(lower_bound, upper_bound);
        to_return.push_back(rand);
    }
    return to_return;
    
}






// chrono::hh_mm_ss<minutes> generateRandomTime()
// {
//     random_device seed;
//     mt19937 generator(seed());
//     uniform_int_distribution minutes_dist(0, 1439);

//     int random_minutes = minutes_dist(generator);
//     chrono::minutes minute= chrono::minutes((random_minutes * 5));
//     chrono::hh_mm_ss<chrono::minutes> thing{minute};
//     return thing;
// }


