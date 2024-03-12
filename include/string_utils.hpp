#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
using namespace std;

namespace libex {
    namespace string_utils
    {
        
        inline vector<string> break_string_spaces(string input)
        {
            vector<string> result;
            boost::split(result, input, boost::is_space(), boost::token_compress_on);
            return result;
        }

        /**
         * @brief Compares two strings, removing any problem character. 
         * Useful for ignoring carriage returns.
         * 
         * @param a - string to remove problem char from. 
         * @param b - string to compare against.
         * @param to_remove character causing problems in string a.
         * @return true /
         * @return false 
         */
        inline bool resilient_compare_strings(string a, string b, char to_remove)
        {
            a.erase(remove_if(a.begin(), a.end(), [&](unsigned char c){
                return c == to_remove;
            }), a.end());

            return a == b;
        }

                inline string trim_trailing_whitespace(string to_trim)
        {
            size_t end_meaningful_contents = to_trim.find_last_not_of(" \t\n\r\f\v");
            if(end_meaningful_contents != string::npos)
            {
                return to_trim.substr(0, end_meaningful_contents + 1);
            }
            else
            {
                return to_trim;
            }
        }
    }
}
