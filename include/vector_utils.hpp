#include <vector>
#include <iostream>
#include <functional>
using namespace std;

namespace libex
{
    namespace vector
    {

        template <typename T>
        void defaultPrinter(const T& value)
        {
            cout << value << ' ' << endl;
        }

        /**
         * @brief 
         * 
         * @tparam T 
         * @tparam function<void(const T&)> 
         * @param vec 
         * @param printer defaults to `defaultPrinter` if none is provided.
         */
        template <typename T, typename Printer = function<void(const T&)>>
        void print_contents(vector<T> vec, Printer printer = defaultPrinter<T>)
        {
            for(const auto& element : vec)
            {
                printer(element);
            }
        };
    };
};