
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
BOOST_AUTO_TEST_CASE(test_cpu_stats)
{
    CPU_Core_Statistics cpu_core_stats(0);

    thread t1([&cpu_core_stats](){
        for(int i = 0; i < 12; i++)
        {
            cpu_core_stats.update();
            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    thread t2([&cpu_core_stats](){
        
        size_t previous_total_time = 0;
        string current_cpu_time = "";
        this_thread::sleep_for(chrono::seconds(2));
        for(int i = 0; i < 5; i++)
        {
            if(cpu_core_stats.get_total() <= previous_total_time)
            {
                cout << "Failure on iteration " << i << endl;
                BOOST_FAIL("Total time is not being updated correctly.");
            }

            current_cpu_time = "Elapsed CPU Time: " + to_string(cpu_core_stats.get_total());
            cout << current_cpu_time << endl;
            previous_total_time = cpu_core_stats.get_total();
            this_thread::sleep_for(chrono::milliseconds(1113));
        }
    });

    BOOST_TEST_MESSAGE("Waiting for threads to finish...");
    t1.join();
    t2.join();
}
