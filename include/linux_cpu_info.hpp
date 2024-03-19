#include "./cpu_stat_factory.hpp"
#include <vector>
#include <map>
using namespace std;


namespace libex 
{
    namespace Perf
    {
        class Linux_CPU_Info : public ICPU_Info
        {
            public:

            // Overall Timing Statistics object
            CPU_Core_Time_Statistics cpu_timing_stats;
            
            // Per-core Timing Statistics objects
            vector<CPU_Core_Time_Statistics> cores_stats;

            vector<float> cpu_clock_rates;

            // Number of cores
            size_t num_cores;

            map<string, string> core_info;
            
            Linux_CPU_Info();
            void update();
            void update_clocks();

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