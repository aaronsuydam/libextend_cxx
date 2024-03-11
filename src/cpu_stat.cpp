#include "../include/cpu_stat.hpp"

using namespace std;

namespace libex
{
    namespace Perf
    {
        void CPU_Statistics::update()
        {
            if(!proc_stat.is_open())
            {
                try {
                    proc_stat.open("/proc/stat");
                } 
                catch (const ifstream::failure& e) {
                    cerr << "Error opening /proc/stat: " << e.what() << endl;
                    return;
                }
            }

            string line;
            getline(proc_stat, line);
            istringstream iss(line);
            vector<string> tokens;
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

            size_t user_diff = stoul(tokens.at(1)) - user;
            size_t system_diff = stoul(tokens.at(3)) - system;
            size_t idle_diff = stoul(tokens.at(4)) - idle;
            
            user = stoul(tokens.at(1));
            nice = stoul(tokens.at(2));
            system = stoul(tokens.at(3));
            idle = stoul(tokens.at(4));
            iowait = stoul(tokens.at(5));
            irq = stoul(tokens.at(6));
            softirw = stoul(tokens.at(7));
            steal = stoul(tokens.at(8));
            guest = stoul(tokens.at(9));
            guest_nice = stoul(tokens.at(10));

            size_t new_total = user + nice + system + idle + iowait + irq + softirw + steal + guest + guest_nice;
            size_t total_diff = new_total - total;

            user_percent = (user_diff / (float)total_diff) * 100;
            system_percent = (system_diff / (float)total_diff) * 100;
            idle_percent = (idle_diff / (float)total_diff) * 100;
            return;
        }
    }
}