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

    struct tm * t = std::gmtime(&tp);
    std::cout<<t->tm_year + 1900<<"/"<<t->tm_mon + 1<<"/"<<t->tm_mday<<" "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<"\n";

    struct tm * local = std::localtime(&tp);
    std::cout<<local->tm_year + 1900<<"/"<<local->tm_mon + 1<<"/"<<local->tm_mday<<" "<<local->tm_hour<<":"<<local->tm_min<<":"<<local->tm_sec<<"\n";

}

int main(){
    time();



    return 0;
}