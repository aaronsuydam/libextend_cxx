#include "../include/cpu_stat.hpp"

using namespace std;

namespace libex
{
    namespace Perf
    {
        void CPU_Core_Time_Statistics::update()
        {
            /* Make sure that the file is actually open. */
            if(!proc_stat.is_open())
            {
                proc_stat.open("/proc/stat");
                if(!proc_stat.is_open())
                {
                    throw(runtime_error("Error opening /proc/stat"));
                }
            }
            else // Updating, so re-read the contents of the file. 
            {
                proc_stat.clear();
                proc_stat.seekg(0, ios::beg);
            }

            string line;
            if(is_overall) // If this is the overall CPU statistics, then we don't need to search for the core.
            {
                getline(proc_stat, line);
            }
            else
            {
                string core_identifier = "cpu" + to_string(core_num);
                while(getline(proc_stat, line))
                {
                    if(line.find(core_identifier) != string::npos)
                    {
                        cout << "Found core " << core_identifier << endl;
                        break;
                    }
                }
            }

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
            total = new_total;

            user_percent = (user_diff / (float)total_diff) * 100;
            system_percent = (system_diff / (float)total_diff) * 100;
            idle_percent = (idle_diff / (float)total_diff) * 100;
            return;
        };

        /**
         * @brief Construct a new CPU_Info object.
         * 
         * This constructor will initalize the CPU_Info object with
         * the number of cores, logical threads supported, and other
         * CPUID information. 
         * 
         */
        CPU_Info::CPU_Info()
        {
            Proc_CPUInfo_Reader proc_cpuinfo;
            num_cores = proc_cpuinfo.num_cores;
            
            for(size_t i = 0; i < num_cores; i++)
            {
                cores_stats.push_back(CPU_Core_Time_Statistics());
                cores_stats.at(i).set_core_num(i);
            }

            cpu_timing_stats.set_is_overall(true);
            cpu_timing_stats.update();

            auto core_0_info = proc_cpuinfo.core_info.at(0);
            for (const auto& entry : core_0_info) {
                this->core_info[entry.first] = entry.second;
            }
            
        }

        void CPU_Info::update()
        {
            cpu_timing_stats.update();
            for(auto& core : cores_stats)
            {
                core.update();
            }

            this->update_clocks();
        }

        void CPU_Info::update_clocks()
        {
            size_t counter = 0;
            for_each(cpu_clock_rates.begin(), cpu_clock_rates.end(), [&](float& rate){
                std::filesystem::path clock_file_path = "/sys/devices/system/cpu/cpu" + to_string(counter) + "/cpufreq/scaling_cur_freq";
                ifstream cpu_n_clock_file(clock_file_path);
                if(!cpu_n_clock_file.is_open())
                {
                    throw(runtime_error("Error opening " + clock_file_path.string()));
                }
                string line;
                getline(cpu_n_clock_file, line);
                rate = stof(line);
            });
        }


        Proc_CPUInfo_Reader::Proc_CPUInfo_Reader()
        {
            retrieve();
        }

        void Proc_CPUInfo_Reader::retrieve()
        {
            std::ifstream cpuinfoFile("/proc/cpuinfo");
            if (!cpuinfoFile.is_open()) 
            { 
                throw std::runtime_error("Error opening /proc/cpuinfo");
            }
            
            std::string line;
            map<string, string> core_0_info;
            /* Fill with core 0 information */
            while (std::getline(cpuinfoFile, line)) {
                std::istringstream iss(line);
                std::string key, value;
                
                // Get the raw key
                std::getline(iss, key, ':');
                if (key.empty()) {
                    break;
                }
                
                // Normalize the key: remove spaces and convert to lowercase for consistency
                key = string_utils::trim_trailing_whitespace(key);
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);

                // Trim leading whitespace from the value
                std::getline(iss >> std::ws, value);

                // Store the normalized key and value in the map
                core_0_info.emplace(key, value);
            }

            core_info.push_back(core_0_info);

            // Once you have the number of cores, finish filling the core_info map
            for (size_t i = 1; i < stoul(core_info.at(0)["cpu cores"]); i++)
            {
                map<string, string> core_i_info_map;
                while (std::getline(cpuinfoFile, line)) {
                    std::istringstream iss(line);
                    std::string key, value;
                    
                    // Get the raw key
                    std::getline(iss, key, ':');
                    if (key.empty()) {
                        break;
                    }
                    
                    // Normalize the key: remove spaces and convert to lowercase for consistency
                    key = string_utils::trim_trailing_whitespace(key);
                    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

                    // Trim leading whitespace from the value
                    std::getline(iss >> std::ws, value);

                    // Store the normalized key and value in the map
                    core_i_info_map.emplace(key, value);
                }
                core_info.push_back(core_i_info_map);
            }

            this->num_cores = stoul(core_info.at(0)["cpu cores"]);
            cpuinfoFile.close();
            
        }
        
    }
}