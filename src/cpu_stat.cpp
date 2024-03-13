#include "../include/cpu_stat.hpp"

using namespace std;

namespace libex
{
    namespace Perf
    {
        void CPU_Core_Statistics::update()
        {
            if(!proc_stat.is_open())
            {
                proc_stat.open("/proc/stat");
                if(!proc_stat.is_open())
                {
                    throw(runtime_error("Error opening /proc/stat"));
                }
            }
            else
            {
                proc_stat.clear();
                proc_stat.seekg(0, ios::beg);
            }

            string line;
            string core_identifier = "cpu" + to_string(core_num);
            while(getline(proc_stat, line))
            {
                if(line.find(core_identifier) != string::npos)
                {
                    break;
                }
            }

            istringstream iss(line);
            vector<string> tokens;
            cout << "I make it this far" << endl;
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
            total = new_total;

            user_percent = (user_diff / (float)total_diff) * 100;
            system_percent = (system_diff / (float)total_diff) * 100;
            idle_percent = (idle_diff / (float)total_diff) * 100;
            cout << "This constructor succeeds" << endl;
            return;
        };

        CPU_Info::CPU_Info()
        {
            ifstream proc_cpuinfo;
            proc_cpuinfo.open("/proc/cpuinfo");
            if(!proc_cpuinfo.is_open())
            {
                throw(runtime_error("Error opening /proc/cpuinfo"));
            }

            string line;
            while(getline(proc_cpuinfo, line))
            {
                if(line.find("processor") != string::npos)
                {
                    num_cores++;
                }
            }

            for(size_t i = 0; i < num_cores; i++)
            {
                stats_cores.push_back(CPU_Core_Statistics(i));
            }

            overall_stats = CPU_Core_Statistics(num_cores);
            overall_stats.update();
            proc_cpuinfo.close();
        }

        void CPU_Info::update()
        {
            overall_stats.update();
            for(auto& core : stats_cores)
            {
                core.update();
            }
        }
    }
}