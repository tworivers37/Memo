#include<iostream>
#include<thread>

// task는 thread 보다 한 단계 더 추상화 된 것이라 보면 된다.
// thread 기반일 때(thread 단위 수준에서), 어떤 작업을 비 동기적으로 하고 싶을 때, 직접 여러 thread를 만들고 관리해서 결과를 얻는다.
// 그러나 task 기반이라고 하면 우리는 비 동기적(std::asyc)으로 작업을 진행해라 라고 동작해야할 부분을 던져주고 결과만 확인 하면된다.
// 비 동기를 위해 내부적으로 thread를 더 만들던던 현재 thread에서 진행하던 그건 우리가 생각해야 할 부분이 아니다.
// 어떻게든 작업이 비 동기적으로 진행되기만 하면 된다.

int main(){

    return 0;
}