#include<iostream>

class temp{
    public:
        template<typename T>
        void print(T value){
            std::cout<<"temp print : "<<value<<"\n";
        }
};