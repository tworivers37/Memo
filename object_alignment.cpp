#include<iostream>

/*
    1.  멤버변수 자료형 크기의 배수가 되는 메모리 주소 값에서 멤버변수의 메모리 할당이 시작 되어야함.
        그러므로 안 맞으면 padding을 넣어 맞춰주게됨.
        ex) int 형 멤버변수가 있다면, 그 멤버변수의 메모리 시작 주소는 4, 8, 12, 16, ... 등이 되어야함.
            class ....
            {
                ....
                char c; // 1byte이지만 뒤의 int 멤버변수의 메모리 주소를 맞춰주기 위해 padding을 추가(3byte)해서 4 byte를 차지하게됨.
                int i;
            }
            
    2.  object의 전체 사이즈는 가장 큰 멤버변수 크기의 배수의 크기로 끝나야함.
        ex) int, double 멤버변수가 있다면 8byte의 배수로 object 전체 크기가 되어야함.
        
*/

class A{
    public:
        char a;     //  1byte
        char b;     //  1byte
                    //  총 2byte. double c의 시작 주소가 8byte의 배수가 되어야하므로 6byte의 padding이 들어감.
        double c;   //  8byte
};

class B{
    public:
        int a;      //  4byte
                    //  double b의 시작 주소를 맞추기 위해 padding 4byte 들어감.
        double b;   //  8byte
        int c;      //  4byte
                    //  object의 총 크기가 class B에서 가장 큰 자료형인 double의 배수가 되어야하므로 padding 4byte가 들어감.
};

int main(){
    std::cout<<sizeof(A)<<"\n"; //  16
    std::cout<<sizeof(B)<<"\n"; //  24

    return 0;
}