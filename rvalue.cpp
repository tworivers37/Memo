#include<iostream>
#include<algorithm>

// Lvalue : 표현식이 종료된 이후에도 없어지지 않고 지속되는 객체.(ex. 모든 변수)
// Rvalue : 표현식이 종료되면 더 이상 존재하지 않는 임시적인 객체.(ex. 상수, 임시객체 등)

// Lvalue, Rvalue 헷갈리면 주소연산자를 붙여서 에러가 나면 Rvalue
// ex. &(++x)
// ex. &(x++) // error. rvalue

// Rvalue 문법
// int&& n = rvalue();

// Lvalue Reference는 Lvalue만 참조 가능
// Rvalue Reference는 Rvalue만 참조 가능
// Q. Rvalue Reference는 Lvalue임.

// Move Semantics
// 불필요한 Rvalue 복사 과정이 존재함.
/*
    1)
    std::string s1 = "test1";
    std::string s2 = "1234";
    std::string s3;
    s3 = s1 + s2; // s1+s2 임시 객체(Rvalue) 생성. s3 변수에 복사가됨.

    2)
    std::string append(std::string p);  // function
    std::string s = append("test");     // "test"라는 임시 객체, append 함수의 리턴되는 임시 객체.

    1)에서 s1+s2는 어차피 사라질 객체. 이걸 s3로 복사하는게 아니라 객체를 이동 시키면 효율적.
    임시 객체(Rvalue)의 복사 -> 이동 되는 것이 상식적인 개념.
    c++11 이전에는 이런 개념을 구현할 방법이 없었음.

    Move Semantics를 구현 하려면?
    - Move 생성자 구현
    - Move 대입 연산자 구현
    ex) test(test&& other);
    ex) test& operator=(test&& other);
*/

// 아래 MemClass는 내가 만드는 클래스에 Move sementics를 적용한 예제

class MemClass{
    public:
        MemClass(unsigned int length) : length_(length), data_(new int[length]) { }
        ~MemClass(){
            delete[] data_;
        }

        //Copy constuctor
        MemClass(MemClass const& other) : length_(other.length_), data_(new int[other.length_]){
            std::copy(other.data_, other.data_ + length_, data_);
        }

        //Assignment operator
        MemClass& operator=(MemClass const& other){
            if(this != &other){
                delete[] data_;
                length_ = other.length_;
                data_ = new int[length_];
                std::copy(other.data_, other.data_ + length_, data_);
            }
            return *this;
        }

        //Move constuctor
        MemClass(MemClass&& other) : length_(other.length_), data_(other.data_){ // 포인터만 복사해옴.
            other.data_ = nullptr; // other가 사라질 때, data_가 같이 없어질 수 있기에 nullptr로 지정.
            other.length_ = 0;
        }

        //Move Assignment operator
        MemClass& operator=(MemClass&& other){
            if(this != &other){
                delete[] data_;
                length_ = other.length_;
                data_ = other.data_;
                other.data_ = nullptr; // other가 사라질 때, data_가 같이 없어질 수 있기에 nullptr로 지정.
                other.length_ = 0;
            }
            return *this;
        }

    private:
        unsigned int length_;
        int * data_;
};

// std::move 함수는 파라미터를 무조건 Rvalue Reference로 타입캐스팅만 함. Lvalue를 Rvalue로 취급하고 싶을 때 사용.
// 컴파일러에게 해당 객체가 이동해도 무관하다고 알리기 위해.
class Person{
    public:
        Person(Person&& other){
            name_ = other.name_; // Rvalue 복사 발생.
            // -> name_ = std::move(other.name_);
        }
        void set_name(std::string&& new_name){
            name_ = new_name; // Rvalue 복사 발생. new_name은 Lvalue이므로(Rvalue reference 자체는 Lvalue) 복사 발생.
            // -> name_ = std::move(new_name);
        }
    private:
        std::string name_;
};

//Perfect forwarding

/*
    1) void f(std::string&& s)          // Rvalue
    2) std::string&& s = std::string()  // Rvalue
    3) auto&& a = b;                    // Universal Reference
    4) template<typename T>
       void f(T&& p);                   // Universal Reference

    - && 참조자가 템플릿 파라미터 또는 auto 타입과 사용되었을 경우 -> Universal reference
    - Universal reference : Lvalue와 Rvalue를 모두 참조 할 수 있는 포괄적 reference.
    - 반드시 Rvalue와 구분해야함.


    ex)
    template<typename T, typename Arg>
    T* fac(Arg& arg){
        return new T(arg);
    }

    class X{
        X(int& n){}
    }

    class Y{
        Y(int const& n){}
    }

    int n = 0;
    X* px = fac<X>(n);      // 문제 없음.
    Y* py = fac<Y>(100);    // error. fac함수는 const 레퍼런스가 아니라 그냥 레퍼런스로(&)만 받고 있기에 상수를 받지 못함.

    그러므로 fac 함수를 const 레퍼런스 파라미터 함수와 그냥 레퍼런스 파라미터 함수를 만들어야함.

    template<typename T, typename Arg>
    T* fac(Arg& arg){
        return new T(arg);
    }

    template<typename T, typename Arg>
    T* fac(Arg const& arg){
        return new T(arg);
    }

    이러면 작성해야 할 함수의 개수가 2^n으로 증가.(n은 파라미터 개수)
    만약 가변인자라면 끝이 없을 수 도 있음.

    이를 Universal reference를 사용하면 해결.
    template<typename T, typename Arg>
    T* fac(Arg&& arg){
        return new T(arg);
    }


    template<typename T>
    void f(T&& p);

    int n = 0;
    f(n);   // Lvalue 전달 : T -> int&로 추론   => void f(int& && p);   -> void f(int& p);
    f(10);  // Rvalue 전달 : T -> int로 추론    => void f(int&& p);     -> void f(int&& p);

    Reference Collapsing Rules
    - T& & -> T&
    - T& && -> T&
    - T&& & -> T&
    - T&& && -> T&& 
    -> Rvalue + Rvalue일 때만 Rvalue reference로 추론됨.

    근데 위 fac(Arg&& arg) 함수에서 new T(arg) 할 때, arg가 Rvalue 면 Rvalue로 전달, Lvalue면 Lvalue로 전달 해줘야함.
    Lvalue는 Lvalue로 Rvalue는 Rvalue로 전달되어야 완벽한 포워딩이라 할 수 있음.

    template<typename T, typename Arg>
    T* fac(Arg&& arg){
        return new T(std::forward<Arg>(arg));
    }

    위 처럼 std::forward 함수를 사용하면 완벽한 포워딩이됨.

    std::forward : 파라미터를 '조건에 따라' Rvalue reference로 타입 캐스팅. -> Rvalue/Rvalue refernce 일 때만 Rvalue reference로 타입 캐스팅함.
    (std::forward 함수 내부에선 Rvalue reference로 타입캐스팅 하게 구현되어 있는데, Reference Collapsing Rules이 적용이됨)

    std::move와 std::forward 중 어떤 것을 사용 해야 할 지 헷갈리면,
    Rvalue reference에서 std::move, Universal reference라면 std::forward를 사용.

*/


int main(){

    return 0;
}