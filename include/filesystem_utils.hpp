#include <fstream>
#include <filesystem>
#include <optional>
#include <iostream>
using namespace std;

namespace libex {

    namespace fs
    {
        /**
         * @brief Wrapper for ifstream::open to throw an error on failure.
         * 
         * @param to_open 
         * @return ifstream 
         */
        ifstream open(filesystem::path to_open)
        {
            try
            {
                ifstream to_return(to_open.string());
                return to_return;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                throw(runtime_error("Very bad - unable to open a file, its also my only job. "));
            }
        }
    }
}
    