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

int main(){
        std::cout<<"----------- main start -----------\n";

        // target() : 0x01
        target t; 

        std::cout<<"1 *******************************************\n";
        /*
                func1(target const& t) : 0x01 
        */
        func1(t);

        std::cout<<"2 *******************************************\n";
        /*
                target() : 0x02
                func1(target const& t) : 0x02      
                ~target() : 0x02
        */
        func1(target());

        std::cout<<"3 *******************************************\n";
        /*
                func2(target & t) : 0x01
        */
        func2(t);

        std::cout<<"4 *******************************************\n";
        /*
                target(target const&) : 0x02       
                func3(target t) : 0x02
                ~target() : 0x02
        */
        func3(t);

        std::cout<<"5 *******************************************\n";
        /*
                target() : 0x02
                func3(target t) : 0x02
                ~target() : 0x02
        */
        func3(target());

        std::cout<<"6 *******************************************\n";
        /*
                func4(target&& t) : 0x01
        */
        func4(std::move(t));

        std::cout<<"7 *******************************************\n";
        /*
                target() : 0x03
                operator=(target&) : 0x03
        */
        target t2;
        t2 = t;

        std::cout<<"8 *******************************************\n";
        /*
                target() : 0x04
                operator(&&) : 0x04
        */
        target t3;
        t3 = std::move(t);

        std::cout<<"9 *******************************************\n";
        /*
                target() : 0x05
                target() : 0x02
                operator(&&) : 0x05
                ~target() : 0x02
        */
        target t4;
        t4 = target();

        std::cout<<"----------- main end -------------\n";
        /*
                ~target() : 0x05
                ~target() : 0x04
                ~target() : 0x03
                ~target() : 0x01
        */
       
        return 0;
}


