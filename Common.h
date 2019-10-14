#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

namespace BASIC_PRACTICE{
    template<typename T>
    void print(std::vector<T>&& values){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        std::cout<<"\nstart----------------------------------------------------------------------------------------------\n";

        for(auto const& value : values) std::cout<<value<<" ";

        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        std::cout<<"\nend------------------------------------------------------------------------------------------------\n";
        // std::cout<<"Run time : "<<sec.count()<<" seconds\n";
    }

    void set_random_number(std::vector<int>& values, int begin = 0, int end = 100){
        srand(time(nullptr));
        for(auto & value : values) value = begin + (rand() % end - begin) + 1;
    }
};