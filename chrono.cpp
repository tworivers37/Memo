#include<iostream>
#include<chrono>
#include<ctime>

//std::chrono::time_point : 시스템 차원의 리얼 타임 클록. 보조함수인 to_time_t, from_time_t를 사용해 시점을 캘린더 시간으로 변경.
//                          시작점은 1970년 1월 1일로 유닉스 epoch.
//std::chrono::steady_clock :   수정할 수 없다는 것을 보장. 따라서 기간 동안 또는 시점까지 기다릴 때 사용.
//                              시작점은 PC의 부트 시간.
//std::chrono::high_resolution_clock : 정확도가 가장 높은 클록. 다만 system_clock이나 steady_clock의 alias일 수도 있음.
void time(){
    std::chrono::time_point<std::chrono::system_clock> system_time_point;
    std::time_t tp = std::chrono::system_clock::to_time_t(system_time_point);
    std::string s = std::asctime(std::gmtime(&tp));
    std::cout<<"Epoch : "<<s<<"\n"; // 시작 시점

    tp = std::chrono::system_clock::to_time_t(system_time_point.min()); // 클럭이 가지는 최소 시점
    s = std::asctime(std::gmtime(&tp));
    std::cout<<"Time min : "<<s<<"\n";

    tp = std::chrono::system_clock::to_time_t(system_time_point.max()); // 클럭이 가지는 최대 시점
    s = std::asctime(std::gmtime(&tp));
    std::cout<<"Time max : "<<s<<"\n";

    system_time_point = std::chrono::system_clock::now();
    tp = std::chrono::system_clock::to_time_t(system_time_point);
    s = std::asctime(std::gmtime(&tp));
    std::cout<<"Time now : "<<s<<"\n";

/*
    Epoch : Thu Jan  1 00:00:00 1970

    Time min : Tue Sep 21 00:12:44 1677

    Time max : Fri Apr 11 23:47:16 2262

    Time now : Sun Dec  8 13:14:59 2019
*/

    struct tm * t = std::gmtime(&tp);
    std::cout<<t->tm_year + 1900<<"/"<<t->tm_mon + 1<<"/"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<"\n";

    struct tm * local = std::localtime(&tp);
    std::cout<<local->tm_year + 1900<<"/"<<local->tm_mon + 1<<"/"<<local->tm_mday<<" "<<local->tm_hour<<":"<<local->tm_min<<":"<<local->tm_sec<<"\n";

/*
    2019/12/8 13:14:59
    2019/12/8 22:14:59
*/
}

//기간은 산술연산자를 지원.

//c++14 부터 자주 사용되는 시간 리터럴을 지원.
//std::chrono::hours        ->  h   /   ex) 5h
//std::chrono::minuts       ->  min /   ex) 10min
//std::chrono::seconds      ->  s   /   ex) 15s
//std::chrono::milliseconds ->  ms  /   ex) 20ms
//std::chrono::microseconds ->  us  /   ex) 25us
//std::chrono::nanoseconds  ->  ns  /   ex) 30ns

using namespace std::literals::chrono_literals;
void time2(){
    
    constexpr auto hours = 24h;
    constexpr auto weak = 24h * 7;
    std::cout<<hours.count()<<"\n";
    std::cout<<weak.count()<<"\n";

    // std::chrono::duration<A,B>
    // A : 단위 시간
    // B : 단위 시간의 길이
    // std::ratio<1> or std::ratio<1,1> : 1초
    // std::ratio<1,1000> : 1 밀리초
    constexpr auto seconds = 3600s; // 1시간 = 3600초
    std::chrono::duration<double, std::ratio<3600>> hours2 = seconds; // 단위 시간 3600(한 시간이 3600) : 3600 / 3600 = 1시간이라는 의미
    std::cout<<hours2.count()<<"\n";
    std::chrono::duration<double, std::ratio<60>> day = seconds; // 단위 시간 60(한 시간이 60) : 3600 / 60 = 60 -> 60분이라는 의미
    std::cout<<day.count()<<"\n";
/*
    24
    168
    1
    60
*/

}

int main(){
    time();
    std::cout<<"----------------------------------------------------------------------\n";
    time2();
    std::cout<<"----------------------------------------------------------------------\n";

    return 0;
}