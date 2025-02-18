#include <fstream>
#include <filesystem>
#include <optional>
#include <iostream>
#include <errno.h>
#include <cstring>
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
                #if DEBUG 
                string path_string = to_open.string();
                std::cout << "Current directory is: " << std::filesystem::current_path() << endl;
                ifstream to_return;
                to_return.open(path_string);
                #else
                ifstream to_return(to_open.string());
                #endif

                auto success = to_return.good();
                if(!success)
                {
                    std::cout << "File open failed, error is: " << strerror(errno) << endl;
                    throw std::runtime_error("");
                }
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
    