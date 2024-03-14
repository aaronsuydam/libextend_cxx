
#define BOOST_TEST_MODULE test_cpu_stats
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include "../include/cpu_stat.hpp"

using namespace libex::Perf;
using namespace std;





/**
 * @brief This test case will test the CPU_Core_Statistics class.
 * 
 * One thread will be responsible for calling the `update` method
 * of the CPU_Core_Statistics class once every second. The other
 * thread will be responsible for reading the CPU statistics from
 * the CPU_Core_Statistics object and verifying that the statistics
 * are being updated correctly.
 * 
 */
BOOST_AUTO_TEST_CASE(test_cpu_time_update)
{
    CPU_Core_Time_Statistics cpu_core_stats;
    cpu_core_stats.set_is_overall(true);
    cpu_core_stats.update();

    thread t1([&cpu_core_stats](){
        for(int i = 0; i < 25; i++)
        {
            cpu_core_stats.update();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });

    this_thread::sleep_for(chrono::seconds(2));

    thread t2([&cpu_core_stats](){
        
        size_t previous_total_time = 0;
        string current_cpu_time = "";
        for(int i = 0; i < 10; i++)
        {
            if(cpu_core_stats.get_total() <= previous_total_time)
            {
                cout << "Failure on iteration " << i << endl;
                BOOST_FAIL("Total time is not being updated correctly.");
            }

            current_cpu_time = "Elapsed CPU Time: " + to_string(cpu_core_stats.get_total());
            cout << current_cpu_time << endl;
            previous_total_time = cpu_core_stats.get_total();
            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    BOOST_TEST_MESSAGE("Waiting for threads to finish...");
    t1.join();
    t2.join();
}

/* Test the retreival of CPU information */
BOOST_AUTO_TEST_CASE(test_cpu_info_retreival)
{
    CPU_Info cpu_info;
    if(cpu_info.core_info.empty())
    {
        BOOST_FAIL("CPU Information not retreived.");
    }

    if(cpu_info.core_info.at("vendor_id").empty())
    {
        BOOST_FAIL("CPU Core Information not retreived.");
    }

    BOOST_TEST_MESSAGE("CPU Information:");
    for (const auto& entry : cpu_info.core_info) {
        BOOST_TEST_MESSAGE(entry.first << ": " << entry.second);
    }
}

BOOST_AUTO_TEST_CASE(test_cpu_clock_monitoring)
{
    CPU_Info cpu_info;
    if(cpu_info.cpu_clock_rates.empty())
    {
        BOOST_FAIL("CPU Clock Rates not retreived.");
    }

    for(size_t i = 0; i < 20; i++)
    {
        cpu_info.update_clocks();
        this_thread::sleep_for(chrono::seconds(1));
        size_t counter = 0;
        for(const auto& clock_rate : cpu_info.cpu_clock_rates)
        {
            BOOST_TEST_MESSAGE("CPU" << counter << " clock: " << clock_rate);
        }
    }


}

