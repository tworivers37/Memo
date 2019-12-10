#include<iostream>
#include<typeinfo>
// 가변 인자
// fold expression
/*
    (... op pack)           ->  ((((pack1 op pack2) op pack3) op pack4) ... packN)
    (pack op ...)           ->  (pack1 op (... ( packN-1 op packN)))
    (init op ... op pack)   ->  (((init op pack1) op pack2) ... op packN)
    (pack op ... op init)   ->  (pack1 op ( ... (packN op init)))
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