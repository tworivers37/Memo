#include<iostream>
#include<typeinfo>

// 가변 인자
void print_variadic(){
    std::cout<<"\n";
}

template<typename T, typename... ARGS>
void print_variadic(T t, ARGS... args){
    std::cout<<t<<" / ";
    print_variadic(args...); // 인자가 1개 남았을 때, print_variadic() 호출을 위한 함수 필요. 인자가 없는 함수는 템플릿으로 못 만듦.
}

template<typename T, typename... ARGS>
void print_variadic2(T t, ARGS... args){
    std::cout<<t<<" / ";
    // sizeof... 을 활용해 남은 args의 갯수가 0개 일 때, print_variadic2를 호출 안하게 하려 했으나, 컴파일 에러 발생.
    // 왜냐하면 마지막 인자 1개 일 때, print_variadic2(args...) 함수가 호출이 되든 안 되든 컴파일 타임에 인스턴스화 되기 때문에
    // 인자가 하나도 없는 print_variadic2 함수가 있어야함. (템플릿 함수로는 인자가 없는 print_variadic2 함수를 만들지 못함)
    if(sizeof...(args) != 0) print_variadic2(args...); 
}

template<typename T, typename... ARGS>
void print_variadic3(T t, ARGS... args){
    std::cout<<t<<" / ";
    // c++17에선 if constexpr 로 컴파일 타임에 특정 조건에따라 표현문을 활성화/비활성화 할 수 있음.
    if constexpr(sizeof...(args) != 0) print_variadic3(args...);
}

// fold expression을 사용하여, print하는데 출력 단위 마다 '/' 로 나눠주고 싶을 때, 아래와 같이 할 수 있다.
template<typename T>
class Delim{
    public:
        Delim(T const& obj) : t(obj){ 
        
        };
        friend std::ostream& operator<<(std::ostream& os, Delim const& d){
            return os<<d.t<<" / ";
        }
    private:
        T const& t;
};

template<typename T, typename... ARGS>
void print_variadic4(T t, ARGS... args){
    // (((std::cout << Delim(a1)) << Delim(a2)) << Delim(a3)) << .....
    // 아래의 fold expression 에서 항목3. 에 해당하는 표현식.
    // 계속해서 std::ostream& operator<<(std::ostream& os, Delim const& d) 함수가 호출되는 형태.
    (std::cout<<...<<Delim(args))<<"\n"; 
}

// 아래는 fold expression에 대한 예이다.

// fold expression
/*
   1. (... op pack)           ->  ((((pack1 op pack2) op pack3) op pack4) ... packN)
   2. (pack op ...)           ->  (pack1 op (... ( packN-1 op packN)))
   3. (init op ... op pack)   ->  (((init op pack1) op pack2) ... op packN)
   4. (pack op ... op init)   ->  (pack1 op ( ... (packN op init)))
*/
template<typename T>
bool print(T a){
    std::cout<<"a : "<<a<<"\n";
    return true;
}

template<typename T1, typename... TN>
bool isTest(T1 a, TN... b){
    //std::is_same<T1, TN1>::value && std::is_same<T1, TN2>::value && ...
    return (std::is_same<T1, TN>::value && ...); // c++ 17 부터 지원
}

template<typename T1, typename... TN>
bool isTest2(T1 a, TN... b){
    return (print(std::is_same<T1, TN>::value) && ...); // c++ 17 부터 지원
}


// 가변 표현식

template<typename T>
void print2(T arg){
    std::cout<<"print2 std::cout call\n";
    std::cout<<arg<<"\n";
}

template<typename T, typename... Types>
void print2(T first, Types... args){
    std::cout<<"print2 called\n";
    print2(first); // first = args + args  //  first = args + 1
    print2(args...);
}

template<typename... T>
void printDouble(T const&... args){
    std::cout<<"printDouble\n";
    print2(args + args...);
}

template<typename... T>
void printAddOne(T const&... args){
    std::cout<<"printAddOne\n";
    print2(args + 1 ...); // 1 (space) ... // 1... -> 소수점으로 인식
}

int main(){
    // 가변인자 출력 예시
    print_variadic("test1",1,2,3);
    // print_variadic2("test2",12,22,32); // error
    print_variadic3("test3",13,23,33);
    std::cout<<"\n";
    print_variadic3("test4",14,24,34);

    std::cout<<"--------------------------------------------------------------\n";

    std::cout<<isTest(1, 3.4, "56")<<"\n";
    std::cout<<isTest2(123, 1.2, 321)<<"\n";
    /*
        0
        a : 0
        a : 1
        1
    */
    std::cout<<std::endl;
    printDouble(1,10,100); // print2(1 + 1, 10 + 10, 100 + 100)
    std::cout<<std::endl;
    printAddOne(1,10,100);
    /*
        printDouble
        print2 called
        print2 std::cout call
        2
        print2 called
        print2 std::cout call
        20
        print2 std::cout call
        200

        printAddOne
        print2 called
        print2 std::cout call
        2
        print2 called
        print2 std::cout call
        11
        print2 std::cout call
        101
    */

    return 0;
}