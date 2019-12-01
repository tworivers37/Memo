#include<iostream>

//CRTP(Curiously Recurring Template Pattern)
//자기 자신을 베이스 클래스의 템플릿 인자로 상속 받는 것.
//이는 베이스 클래스의 구현부에서 타입이 지정된 this 포인터를 사용할 수 있기 때문.

template<typename Derived>
class Base{
    public:
        void func(){
            std::cout<<this<<" "<<__PRETTY_FUNCTION__<<"\n";
            static_cast<Derived*>(this)->execute();
        }

        void execute(){
            std::cout<<this<<" "<<__PRETTY_FUNCTION__<<"\n";
        }
};

class DerivedClass : public Base<DerivedClass>{
    public:
        void execute(){
            std::cout<<this<<" "<<__PRETTY_FUNCTION__<<"\n";
        }
};

class DerivedClass2 : public Base<DerivedClass2>{
    public:
        void execute(){
            std::cout<<this<<" "<<__PRETTY_FUNCTION__<<"\n";
        }
};

class DerivedClass3 : public Base<DerivedClass3>{};

template<typename T>
void executor(T& base){
    base->execute();
}

int main(){
    DerivedClass * d1 = new DerivedClass();
    DerivedClass2 * d2 = new DerivedClass2();    
    DerivedClass3 * d3 = new DerivedClass3();
    d1->execute(); // 0x60003a1a0
    d2->execute(); // 0x60003a1c0
    d3->execute(); // 0x60003a1e0

    std::cout<<std::endl;

    Base<DerivedClass> * b1 = new Base<DerivedClass>();
    b1->func(); // 0x60006c780
    Base<DerivedClass2> * b2 = new Base<DerivedClass2>();
    b2->func(); // 0x60006c7a0
    Base<DerivedClass3> * b3 = new Base<DerivedClass3>();
    b3->func(); // 0x60006c7c0

    std::cout<<std::endl;

    b1 = d1;
    b1->func(); // b1의 this주소 == d1의 this주소, 0x60003a1a0
    b2 = d2;
    b2->func(); // b2의 this주소 == d2의 this주소, 0x60003a1c0
    b3 = d3;
    b3->func(); // b3의 this주소 == d3의 this주소, 0x60003a1e0

    std::cout<<std::endl;

    executor(d1); // 0x60003a1a0
    executor(d2); // 0x60003a1c0
    executor(d3); // 0x60003a1e0

    std::cout<<std::endl;

    return 0;
}