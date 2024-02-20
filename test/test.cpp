#include <iostream>
#include <chrono>
#include <randomtime.h>
using namespace std;

int main(int argc, char** argv)
{
    chrono::hh_mm_ss random_time = generateRandomTime();
    cout << "The random time generated is " << random_time << endl;
}