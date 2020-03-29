#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>

// CRTP, shared_ptr 사용.

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

    return 0;
}