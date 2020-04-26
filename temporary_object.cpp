#include<iostream>

/*
    Temporary object란 이름이 없으며, 스택 메모리에 잡히는 object. 임시객체라고 부른다. 
    
    1)  임시객체의 lifetime
        -   임시객체는 세미콜론을 만나면 파괴됨.
            ex)
                {
                    target t; // 이름있는 object는 scope의 끝에서 파괴됨.
                    target(); // 해당 라인에서 파괴됨.
                }

    2)  임시객체의 포인터
        -   임시객체는 해당 라인의 연산이 끝나고 세미콜론을 만나면 파괴되기 때문에
            포인터 변수를 통해 임시객체를 저장하는 것은 불가능하다.
            ex)
                target *t = &target(); // 에러
    
    3)  rvalue
        -   임시객체는 rvalue에 속한다. 그러므로 대입연산자의 왼쪽에 올 수 없다.
    
    4)  임시객체와 레퍼런스
        -   임시객체는 해당 라인의 연산이 끝나고 세미콜론을 만나면 파괴되기 때문에 레퍼런스를 얻는 것은 불가능하다.
            ex)
                target& t1 = t; // 정상
                target& t2 = target() // 에러
        -   그러나 const reference는 이를 허용한다. 임시객체를 const reference 변수에 담으면 임시객체의 lifetime은
            const reference 변수와 같아지게 된다. 그러나 const이기에 값을 변경할 수는 없다.
            ex)
                target const& t1 = target(); // 허용
        -   C++ 11 부터는 const를 제외한 임시객체를 reference하는 것이 허용됨.(rvalue reference)
            ex)
                targe&& t1 = target(); // 허용
    
    5)  Passing temporary object as parameter
        -   임시객체를 통해 parameter passing을 효율적으로 수행 할 수 있음.
            ex)
                void function(target t){ ...... }
                main{
                    target t;       // target 생성자
                    function(t);    // target 복사생성자
                }

                // 위에서 target의 생성자와 복사생성자가 한 번씩 호출됨.

                void function2(target const& t){ ...... }    
                main(){
                    function2(target()); // target 생성자
                }
                
                // 위 function2 호출에선 target 생성자만 호출됨.
                // main에서 target의 객체가 함수로의 전달되는 역할만 하고 function2에서 target의 값을 반환하지 않는다면
                // 임시객체로 전달하는 것이 효율적.

    6)  return value / return reference
        ex)
            target gt;
            target function(){
                return gt;
            }
            target& function2(){
                return gt;
            }
            main(){
                function().value = 999; // 에러
                function2().value = 9999; // 정상
            }
            // value return하는 함수를 호출한 쪽이 받는 value는 언제나 임시객체임. 그래서 에러 발생.
            // reference를 리턴하는 경우 리턴 값이 lvalue이고 function2는 전역변수를 리턴하기 때문에 에러발생하지 않음.
            // 그렇다고 지역변수를 reference로 리턴하면 안 됨.

    7)  type casting
        -   Derived에서 Base의 값에 접근할 때, 보통 type casting을 통해 접근하는데,
            이 때, Base 로 casting 하는 방식과 Base& 로 casting 하는 방식이 있다.
            ex)
                class Base{
                    public:
                        Base(){
                            std::cout<<"Base()\n";
                        }
                        int value;
                }
                class Derived : public Base{
                    public:
                        Derived(){
                                std::cout<<"Dervied()\n";
                        }
                        int value;
                }
                main(){
                    Derived d;
                    d.Base::value = 10;
                    d.value = 20;

                    std::cout<<d.value<<"\n";                           // 20
                    std::cout<<(static_cast<Base>(d)).value<<"\n";      // 10, 임시객체 생성.
                    std::cout<<(static_cast<Base&>(d)).value<<"\n";     // 10
                    std::cout<<"-------------------------------\n";

                //  (static_cast<Base>(d)).value = 30;                  // 에러, 임시객체는 rvalue이므로 대입연산자 에러.
                    (static_cast<Base&>(d)).value = 40;                 // 정상
                    std::cout<<d.value<<"\n";                           // 20
                    std::cout<<(static_cast<Base>(d)).value<<"\n";      // 40
                    std::cout<<(static_cast<Base&>(d)).value<<"\n";     // 40
                }
                
                // Base로 casting하면 임시객체가 리턴되어 대입연산 에러가 발생.
                // Base&로 casting하면 reference 값을 리턴하므로 임시객체 생성하지 않고, 리턴 값이 lvalue이므로 대입연산 가능.
                // 이에 따른 또 다른 예로 아래와 같은 증감연산자가 있음.
                {
                    int value = 1;
                    value++ = 9; // 에러, 후위 증감연산자의 경우 기존 값에 대한 임시객체를 리턴.
                    ++value = 9; // 정상, 전위 연산자는 reference를 리턴.
                }
*/

int main(){

    return 0;
}