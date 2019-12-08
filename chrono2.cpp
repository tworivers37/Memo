#include<iostream>
#include<boost/chrono.hpp>
#include<boost/chrono/io/ios_base_state.hpp>
#include<boost/chrono/chrono_io.hpp>
#include<boost/chrono/time_point.hpp>
#include<boost/chrono/system_clocks.hpp>
#include<sstream>



int main(){
    boost::chrono::system_clock::time_point now = boost::chrono::system_clock::now();
    std::cout<<now<<"\n";
    std::cout<<boost::chrono::system_clock::now()<<"\n";
    std::cout<<boost::chrono::steady_clock::now()<<"\n";
    std::cout<<boost::chrono::high_resolution_clock::now()<<"\n";
    std::cout<<boost::chrono::process_cpu_clock::now()<<"\n";
    std::cout<<boost::chrono::process_real_cpu_clock::now()<<"\n";
    std::cout<<boost::chrono::process_system_cpu_clock::now()<<"\n";
/*
    - std::cout - 
    1575797429519522300 nanoseconds since Jan 1, 1970
    1575797429520556300 nanoseconds since Jan 1, 1970
    16799860709300 nanoseconds since boot
    16799861194200 nanoseconds since boot
    {156014946000000;15000000;0} nanoseconds since process start-up
    156014958000000 nanoseconds since process start-up
    0 nanoseconds since process start-up
*/
    std::cout<<"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n";

    std::cout<<now<<"\n";
    std::cout<<now - boost::chrono::nanoseconds{1}<<"\n";
    std::cout<<now - boost::chrono::hours{1}<<"\n";
/*
    1575797599219008600 nanoseconds since Jan 1, 1970
    1575797599219008599 nanoseconds since Jan 1, 1970
    1575793999219008600 nanoseconds since Jan 1, 1970
*/
    std::cout<<"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222\n";

    std::cout<<boost::chrono::time_point_cast<boost::chrono::minutes>(now)<<"\n";
    std::cout<<boost::chrono::time_point_cast<boost::chrono::hours>(now)<<"\n";
/*
    26263295 minutes since Jan 1, 1970
    437721 hours since Jan 1, 1970
*/
    std::cout<<"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333\n";

    std::cout<<boost::chrono::minutes{10} + boost::chrono::seconds{60}<<"\n";
    std::cout<<boost::chrono::duration_cast<boost::chrono::minutes>(boost::chrono::minutes{10} + boost::chrono::seconds{60})<<"\n";
/*
    660 seconds
    11 minutes
*/
    std::cout<<"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444\n";
    
    std::time_t time = boost::chrono::system_clock::to_time_t(now);

    std::tm * t = std::localtime(&time);
    std::cout<<t->tm_year + 1900<<"/"<<t->tm_mon + 1<<"/"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<"\n";

    std::tm * gmt = std::gmtime(&time);
    std::cout<<gmt->tm_year + 1900<<"/"<<gmt->tm_mon + 1<<"/"<<gmt->tm_mday<<" "<<gmt->tm_hour<<":"<<gmt->tm_min<<":"<<gmt->tm_sec<<"\n";
/*
    2019/12/8 22:14:33
    2019/12/8 13:14:33
*/

    return 0;
}