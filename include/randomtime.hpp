#include <random>
#include <chrono>
#include <vector>
using namespace std;
using namespace chrono;

chrono::hh_mm_ss<minutes> generateRandomTime()
{
    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution minutes_dist(0, 1439);

    int random_minutes = minutes_dist(generator);
    chrono::minutes minute= chrono::minutes((random_minutes * 5));
    chrono::hh_mm_ss<chrono::minutes> thing{minute};
    return thing;


}

int generateRandomInt(int lower_bound, int upper_bound)
{
    random_device seed;
    mt19937_64 generator(seed());
    uniform_int_distribution<int> spread(lower_bound, upper_bound);
    int to_return = spread(generator);
    return to_return;
}