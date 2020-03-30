#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>

// CRTP, shared_ptr 사용.
// Base가 Derived1의 함수 호출.(다형성)

class CRTPInterface{
    public:
        virtual void function() = 0;
};

template<typename Derived>
class Base : public CRTPInterface{
    public:
        void function(){ std::cout<<this<<" : Base\n"; }
        
        Derived* derived(){
            return static_cast<Derived*>(this);
        }

        void derived_function(){
            std::cout<<"derived() : "<<derived()<<"\n";
            derived()->function();
        }
};

class Derived1 : public Base<Derived1>{
    public:
        void function(){ std::cout<<this<<" : Derived1\n"; }
};


// Base2 클래스가 Derived2, Derived3 클래스를 상속 받고,
// Base2 클래스의 템플릿 타입을 Derived2 또는 Derived3로 하여
// Base2 에서 상속 받는 템플릿 타입의 함수를 호출.
class Derived2{
    public:
        void derived_function(){
            std::cout<<this<<" : derived2_function!!\n";
        }
};

class Derived3{
    public:
        void derived_function(){
            std::cout<<this<<" : derived3_function!!\n";
        }
};

template<typename Base2_Derived>
class Base2 
    : public Derived2
    , public Derived3
{
    public:
        Base2_Derived* derived(){
            return static_cast<Base2_Derived*>(this);
        }

        void function2(){
            std::cout<<this<<" : base2 function!!\n";
        }

        void derived_function_call(){
            derived()->derived_function();
        }
};


int main(){
    boost::shared_ptr<Derived1> derived1_sp = boost::make_shared<Derived1>();
    derived1_sp->function();

    boost::shared_ptr<Base<Derived1>> base1_sp = derived1_sp;
    base1_sp->function();
    base1_sp->derived_function();

    boost::shared_ptr<Base<Derived1>> base2_sp = boost::dynamic_pointer_cast<Base<Derived1>>(derived1_sp);
    if(base2_sp.get() != nullptr) std::cout<<"dynamic_pointer_cast ok !! \n";

    boost::shared_ptr<CRTPInterface> crtp = boost::dynamic_pointer_cast<CRTPInterface>(derived1_sp);
    if(crtp.get() != nullptr) std::cout<<"dynamic_pointer_cast ok2 !!\n";

    std::cout<<"----------------------------------------------------------------\n";

    boost::shared_ptr<Base2<Derived2>> base2_derived2_sp = boost::make_shared<Base2<Derived2>>();
    base2_derived2_sp->function2();
    base2_derived2_sp->derived_function_call();

    boost::shared_ptr<Base2<Derived3>> base2_derived3_sp = boost::make_shared<Base2<Derived3>>();
    base2_derived3_sp->function2();
    base2_derived3_sp->derived_function_call();

    return 0;
}