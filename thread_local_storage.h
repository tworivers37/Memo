#pragma once
#include<iostream>
#include<boost/thread.hpp>
#include<boost/chrono.hpp>
#include<thread>
#include<mutex>

class tls_class{
    public:
        tls_class(){
            std::cout<<"tls_class()\n";
        }
        ~tls_class(){
            std::cout<<"~tls_class()\n";
        }
    
        boost::thread_specific_ptr<std::string> tls;
};
