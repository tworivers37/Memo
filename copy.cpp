#include<iostream>

class target{
        public:
                target(){
                        std::cout<<"target() : "<<this<<"\n";
                }

                target(int _value){
                        std::cout<<"target(int) : "<<this<<"\n";
                        this->value = _value;
                }

                ~target(){
                        std::cout<<"~target() : "<<this<<"\n";
                }

                target(target&& t){
                        std::cout<<"target(&&) : "<<this<<"\n";
                }

                target(target const& t){
                        this->value = t.value;
                        std::cout<<"target(target const&) : "<<this<<"\n";
                }

                target& operator=(target&& t){
                        this->value=t.value;
                        std::cout<<"operator(&&) : "<<this<<"\n";
                        return *this;
                }

                target& operator=(target const& t){
                        this->value = t.value;
                        std::cout<<"operator=(target&) : "<<this<<"\n";
                        return *this;
                }

                int value;
};

void func1(target const& t){
        std::cout<<"func1(target const& t) : "<<&t<<"\n";
}

void func2(target & t){
        std::cout<<"func2(target & t) : "<<&t<<"\n";
}

void func3(target t){
        std::cout<<"func3(target t) : "<<&t<<"\n";
}

void func4(target&& t){
        std::cout<<"func4(target&& t) : "<<&t<<"\n";
}

/*

----------- main start -----------
target() : 0x01

1 *******************************************
func1(target const& t) : 0x01 

2 *******************************************
target() : 0x02
func1(target const& t) : 0x02      
~target() : 0x02

3 *******************************************
func2(target & t) : 0x01

4 *******************************************
target(target const&) : 0x02       
func3(target t) : 0x02
~target() : 0x02

5 *******************************************
target() : 0x02
func3(target t) : 0x02
~target() : 0x02

6 *******************************************
func4(target&& t) : 0x01

7 *******************************************
target() : 0x03
operator=(target&) : 0x03

8 *******************************************
target() : 0x04
operator(&&) : 0x04

9 *******************************************
target() : 0x05
target() : 0x02
operator(&&) : 0x05
~target() : 0x02

----------- main end -------------
~target() : 0x05
~target() : 0x04
~target() : 0x03
~target() : 0x01

*/

int main(){
        std::cout<<"----------- main start -----------\n";

        target t;

        std::cout<<"1 *******************************************\n";
        func1(t);

        std::cout<<"2 *******************************************\n";
        func1(target());

        std::cout<<"3 *******************************************\n";
        func2(t);

        std::cout<<"4 *******************************************\n";
        func3(t);

        std::cout<<"5 *******************************************\n";
        func3(target());

        std::cout<<"6 *******************************************\n";
        func4(std::move(t));

        std::cout<<"7 *******************************************\n";
        target t2;
        t2 = t;

        std::cout<<"8 *******************************************\n";
        target t3;
        t3 = std::move(t);

        std::cout<<"9 *******************************************\n";
        target t4;
        t4 = target();

        std::cout<<"----------- main end -------------\n";
        return 0;
}


