#include "template_2.h"

// 템플릿 멤버 함수 특수화
// 선언은 할 수도 없고 할 필요도 없음.
// 그냥 정의하면됨.

template<>
void temp::print<char const*>(char const* s){ // string에 대해선 char const* 형식으로 deduction됨.
    std::cout<<"char const* : "<<s<<"\n";
}

template<>
void temp::print<bool>(bool b){
    std::cout<<"bool : "<<std::boolalpha<<b<<"\n";
}

int main(){
    temp t;
    
    t.print("test1");
    t.print(true);
    
    std::cout<<"\n";

    t.print(std::string("test2"));
    t.print(123);
    t.print(1.23);


    return 0;
}