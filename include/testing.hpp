#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
using namespace std;

namespace libex
{
    namespace Testing 
    {
        /**
         * @brief Test and Capture the Output.
         * 
         * This is the TACO function. It is very tasty.
         * 
         * @tparam T 
         * @tparam Args 
         * @param func 
         * @param args 
         * @return string 
         */
        template <typename Function, typename... Args>
        string test_and_capture_output(Function func, Args... args)
        {
            // Capture a pointer to original cout buffer.
            streambuf* cout_buf = cout.rdbuf();
            
            // Create a new output buffer, this is what func will output to.
            ostringstream out_buf;

            // Redirect cout to out_buf.
            cout.rdbuf(out_buf.rdbuf());

            // Call the function.
            func(args...);

            /* Upon completion, restore cout to its original location, and
            return the captured output as a string; */
            cout.rdbuf(cout_buf);   
            return out_buf.str();
        }
    }
}

