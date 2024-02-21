#include <chrono>
#include <iostream>
#include <functional>
using namespace std;



/**
 * @brief Determines the execution time of a function in nanocseconds.
 * 
 * @tparam ret_type The return type of the function.
 * @tparam Argument_t The argument types of the function.
 * @param to_benchmark The function to benchmark.
 * @param args The arguments to pass to the function.
 * @return The execution time of the function in nanoseconds.
 */
template <typename callable, typename... Argument_t>
chrono::nanoseconds test_exec_time(callable to_benchmark, Argument_t... args)
{
    auto start = chrono::high_resolution_clock::now();
    std::invoke(to_benchmark, args...); 
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start);
}

