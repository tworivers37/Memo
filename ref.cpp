#include<iostream>
#include<functional>

//std::reference_wrapper<T> 는 T 형식의 객체 또는 함수에 대한 참조를 래핑.
//해당 T 형식의 개체를 가르키는게 가능한 래퍼.

void print(int a){
    std::cout<<a<<"\n";
}

template<typename T>
void print2(T a){
    ++a;
}

int main(){
    int a = 10;
    std::reference_wrapper<int> f(a);

    std::cout<<a<<"\n";
    std::cout<<f<<"\n";
    f.get() = 20; // f가 가리키는 값 변경
    std::cout<<a<<"\n";
    std::cout<<f<<"\n";

    std::cout<<std::endl;

    //std::ref는 주로 bind와 함께 사용이 많이 됨.

    int b = 100;
    std::function<void()> func1 = std::bind(&print, b);
    std::function<void()> func2 = std::bind(&print, std::ref(b));

    b = 200;
    func1();
    func2(); // 변경된 값 적용

    std::cout<<std::endl;

    int c = 300;
    print2(c);
    std::cout<<c<<"\n";
    print2(std::ref(c));
    std::cout<<c<<"\n"; // 값 변경

    return 0;
}