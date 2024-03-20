#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
using namespace std;

namespace libex
{
    namespace vector_utils
    {

        template <typename T>
        void defaultPrinter(const T& value)
        {
            cout << value << ' ';
        }

        template <typename T>
        void defaultStringify(const T& value, stringstream& ss)
        {
            ss << value << ' ';
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
        void print_contents(const vector<T>& vec, Printer printer)
        {
            for(const auto& element : vec)
            {
                printer(element);
            }
        };

        template <typename T>
        void print_contents(const vector<T>& vec)
        {
            for(const auto& element : vec)
            {
                defaultPrinter(element);
            }
            cout << endl;
        };

        template <typename T, typename Stringify = function<void(const T&, stringstream&)>>
        std::string stringify(vector<T> vec, Stringify converter = defaultStringify<T>)
        {
            std::stringstream ss;
            for(const auto& element : vec)
            {
                converter(element, ss);
            }
            string result = ss.str();
            size_t trailing_space_candidate = result.at(result.size() - 1);
            if(std::isspace(trailing_space_candidate))
            {
                result = result.substr(0, result.size() - 1);
            }
            return result;
        }
    };
};
