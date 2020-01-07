#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <cmath>

namespace BASIC_PRACTICE{
    template<typename T>
    void print(std::vector<T>& values){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        std::cout<<"\nstart----------------------------------------------------------------------------------------------\n";

        for(auto const& value : values) std::cout<<value<<" ";

        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        std::cout<<"\nend------------------------------------------------------------------------------------------------\n";
        // std::cout<<"Run time : "<<sec.count()<<" seconds\n";
    }
    template<typename T>
    void print(std::vector<T>&& values){
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        std::cout<<"\nstart----------------------------------------------------------------------------------------------\n";

        for(auto const& value : values) std::cout<<value<<" ";

        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        std::cout<<"\nend------------------------------------------------------------------------------------------------\n";        
    }


    template<typename T>
    void set_random_value(std::vector<T>& values){
        srand(time(nullptr));
        int size = values.size();
        for(auto & value : values) value = reinterpret_cast<T>(rand() % size + 1);
    }

    void set_random_value(std::vector<int>& values, int begin, int end){
        srand(time(nullptr));
        for(auto & value : values) value = begin + (rand() % end - begin) + 1;
    }
};