#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>
#include "../include/string_utils.hpp"
using namespace std;

namespace libex
{
    namespace Perf
    {
        class CPU_Core_Time_Statistics
        {
            private:

                /* Primitives */
                size_t user;
                size_t nice;
                size_t system;
                size_t idle;
                size_t iowait;
                size_t irq;
                size_t softirw;
                size_t steal;
                size_t guest;
                size_t guest_nice;
                size_t total;

                size_t core_num;
                bool is_overall = false;
                
                float user_percent;
                float system_percent;
                float idle_percent;

                ifstream proc_stat;
                

            public:
                CPU_Core_Time_Statistics()
                {
                    user = 0;
                    nice = 0;
                    system = 0;
                    idle = 0;
                    iowait = 0;
                    irq = 0;
                    softirw = 0;
                    steal = 0;
                    guest = 0;
                    guest_nice = 0;
                    total = 0;
                    user_percent = 0;
                    system_percent = 0;
                    idle_percent = 0;
                };

                void update();
                void set_core_num(size_t core_num) { this->core_num = core_num; }
                void set_is_overall(bool is_overall) { this->is_overall = is_overall; }

                /* Getters for primitives. */
                size_t get_user() const { return user; }
                size_t get_nice() const { return nice; }
                size_t get_system() const { return system; }
                size_t get_idle() const { return idle; }
                size_t get_iowait() const { return iowait; }
                size_t get_irq() const { return irq; }
                size_t get_softirw() const { return softirw; }
                size_t get_steal() const { return steal; }
                size_t get_guest() const { return guest; }
                size_t get_guest_nice() const { return guest_nice; }
                size_t get_total() const { return total; }

                /* Getters */
                float get_user_percent() const { return user_percent; }
                float get_system_percent() const { return system_percent; }
                float get_idle_percent() const { return idle_percent; }

        };

        class CPU_Info
        {
            private:

            // Overall Timing Statistics object
            CPU_Core_Time_Statistics cpu_timing_stats;
            // Per-core Timing Statistics objects
            vector<CPU_Core_Time_Statistics> cores_stats;

            // Number of cores
            size_t num_cores;
            
            public:

            map<string, string> core_info;
            
            CPU_Info();
            void update();

        };


        /**
         * @brief Parser for /proc/cpuinfo.
         * 
         * On instantiation, reads the contents of /proc/cpuinfo,
         * making the data accessible via the `core_info` member.
         */
        struct Proc_CPUInfo_Reader
        {
            
            vector<map<string, string>> core_info;
            size_t num_cores;
            //bool is_heterogeneous;

            Proc_CPUInfo_Reader();
            void retrieve();

        };


    }
}

