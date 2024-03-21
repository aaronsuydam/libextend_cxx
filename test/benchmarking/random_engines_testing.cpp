

#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <iostream>
using namespace std;
using namespace chrono;


#define SIZE 1000000000


std::random_device seed;
std::mt19937 mersenne_generator(seed());
std::mt19937_64 mersenne64_generator(seed());
std::default_random_engine default_generator(seed());

void test_random_generators();
void test_mersenne_engine();
void test_mersenne64_engine();
void test_default_random_engine();

int main(int argc, char** argv)
{
    test_random_generators();
} 

void test_random_generators()
{
    string output = "Testing random number generators...\nGenerating 1,000,000 random numbers...\n";
    test_mersenne_engine();
    test_mersenne64_engine();
    test_default_random_engine();

}

void test_mersenne_engine()
{
    array<int, SIZE>* mersenne_array = new array<int, SIZE>();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        uniform_int_distribution<int> spread(0, 100);
        mersenne_array->at(i) = spread(mersenne_generator);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Mersenne Twister 32-bit: " << duration.count() << " milliseconds" << endl;
    delete[] mersenne_array;
}

void test_mersenne64_engine()
{
    array<int, SIZE>* mersenne64_array = new array<int, SIZE>();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        uniform_int_distribution<int> spread(0, 100);
        mersenne64_array->at(i) = spread(mersenne_generator);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Mersenne Twister 64-bit: " << duration.count() << " milliseconds" << endl;
    delete[] mersenne64_array;
}

void test_default_random_engine()
{
    array<int, SIZE>* default_engine_array = new array<int, SIZE>();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        uniform_int_distribution<int> spread(0, 100);
        default_engine_array->at(i) = spread(mersenne_generator);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Default Engine: " << duration.count() << " milliseconds" << endl;
    delete[] default_engine_array;
}
