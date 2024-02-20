/**
 * @file random_test.cpp
 * @author Suydam, Aaron J. (aaron.suydam@ufl.edu)
 * @brief 
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../include/random.hpp"

int main(int argc, char** argv)
{
    int random_number = generate_random_number<int>(0, 10);
    cout << "I generated a random number!" << endl;
    cout << random_number << endl;

    auto random_vect = random_vector(0, 10, 100);
    cout << "I generated a random vector!!" << endl;
    for (size_t i = 0; i < random_vect.size(); i++)
    {
        cout << random_vect.at(i) << " ";
    }
    
}