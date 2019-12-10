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
    std::cout<<arg<<"\n";
}

template<typename T, typename... Types>
void print2(T first, Types... args){
    print2(first);
    print2(args...);
}

template<typename... T>
void printAll(T const&... args){
    print2(args + args...);
}


int main(){
    std::cout<<isTest(1, 3.4, "56")<<"\n";
    std::cout<<isTest2(123, 1.2, 321)<<"\n";
    printAll(1,10,100); // print2(1 + 1, 10 + 10, 100 + 100)
    return 0;
}