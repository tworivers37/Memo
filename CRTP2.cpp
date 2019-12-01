#include<iostream>
#include<vector>

class virtual_base{
    public:
        virtual void func() = 0;
};

template<typename Derived>
class Base : public virtual_base{
    public:
        void func(){
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

int main(){
    std::vector<virtual_base*> v;
    v.push_back(new DerivedClass());
    v.push_back(new DerivedClass2());
    v.push_back(new DerivedClass3());
    v.push_back(new DerivedClass());
    v.push_back(new DerivedClass2());
    v.push_back(new DerivedClass3());

    for(auto const& b : v) b->func();

    return 0;
}