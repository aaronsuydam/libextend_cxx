
#define BOOST_TEST_MODULE test_cpu_stats
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include "../include/cpu_stat.hpp"

#define WITHOUT_NUMPY

#include "../include/matplotlib.hpp"

using namespace libex::Perf;
using namespace std;
namespace plt = matplotlibcpp;





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

BOOST_AUTO_TEST_CASE(test_cpu_clock_monitoring_1)
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
            counter++;
        }
    }
}

BOOST_AUTO_TEST_CASE(test_cpu_clock_monitoring_2)
{
    CPU_Info cpu_info; // Assuming this is a class that monitors CPU clocks.

    plt::figure_size(1200, 780); // Set the size of the figure.

    // Plot initial CPU clock rates. Assuming `cpu_info.cpu_clock_rates` is a std::vector<double> or similar.
    plt::plot(cpu_info.cpu_clock_rates);
    plt::show(false); // Do not block execution with the initial show.
    vector<float> cpu_clock_rates;

    for(size_t i = 0; i < 200; i++)
    {
        cpu_info.update_clocks(); // Update the CPU clocks.
        cpu_clock_rates.push_back(cpu_info.cpu_clock_rates.at(0));
        // Update the plot with new CPU clock rates.
        plt::clf(); // Clear the current figure.
        plt::plot(cpu_clock_rates); // Plot the updated clock rates.
        plt::pause(0.01); // Pause to update the figure window, value can be adjusted based on update frequency requirement.

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time passing.

        size_t counter = 0;
        for(const auto& clock_rate : cpu_info.cpu_clock_rates)
        {
            BOOST_TEST_MESSAGE("CPU" << counter << " clock: " << clock_rate);
            counter++;
        }
    }
    plt::show(); // Optionally show the plot at the end if you want to hold the final plot open.
}