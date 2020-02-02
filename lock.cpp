#include<iostream>
#include<mutex>
#include<thread>

// lock_guard
// lock이 필요한 구간이 있으면 mutex를 사용해서 lock 해야 될 구간 앞에 lock() 호출 하고 
// 마지막 구간에 unlock() 호출 하여 사용한다.
// 그런데 간혹 unlock() 함수 호출을 까먹는 실수를 하곤한다.
// 그래서 RAII(Resource Acquisition Is Initialization)를 이용한 lock_guard를 사용하면 이러한 실수를 방지 할 수 있다.
// lock_guard는 lock 이 필요한 구간 앞에 lock_guard만 호출 하고 따로 해제하는 것을 신경쓰지 않아도된다.
// 이는 RAII를 활용한 방법으로 해당 scope내에서만 lock_guard가 존재하여 scope를 벗어나게 되면 lock_guard가 소멸되어
// 자연스럽게 lock이 해제되기 때문이다.

// RAII
// C++에서 자주 쓰이는 idiom으로 자원의 안전한 사용을 위해 객체가 쓰이는 스코프를 벗어나면 자원을 해제해주는 기법이다. 
// C++에서 heap에 할당된 자원은 명시적으로 해제하지 않으면 해제되지 않지만, 
// stack에 할당된 자원은 자신의 scope가 끝나면 메모리가 해제되며 destructor가 불린다는 원리를 이용한 것이다.
// 원래는 exception 등으로 control flow가 예상치 못하게 변경될 때를 대비하기 위해서 쓰이던 기법이다.

// scoped_lock
// lock을 사용하다 보면 DeadLock 상황이 발생 할 수 있다.
// 그 예로 아래와 같은 상황이 있다.

int common_value_1 = 0;
int common_value_2 = 0;
std::mutex m1;
std::mutex m2;

void func1(){
    std::lock_guard<std::mutex> g1(m1);
    ++common_value_1; // func1.1
    std::lock_guard<std::mutex> g2(m2);
    ++common_value_2;
}

void func2(){
    std::lock_guard<std::mutex> g2(m2);
    --common_value_2; // func2.1
    std::lock_guard<std::mutex> g1(m1);
    --common_value_1;
}

int main(){
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();

    return 0;
}

// 위 예제에서 두 쓰레드가 func1.1, func2.1 부분을 돌고 있을 때, 서로 m2 및 m1의 lock을 필요로하여
// DeadLock 상황이 발생하게된다.
// 보통 위와 같은 DeadLock 상황을 피하기 위해선 두 쓰레드에서 아래와 같이 동일한 순서로 lock을 걸어주어야 한다.

void func1_1(){
    std::lock_guard<std::mutex> g1(m1);
    std::lock_guard<std::mutex> g2(m2);
    ++common_value_1;
    ++common_value_2;
}
void func2_1(){
    std::lock_guard<std::mutex> g1(m1);
    std::lock_guard<std::mutex> g2(m2);
    --common_value_2;
    --common_value_1;
}

// 그런데 c++17에선 scope_lock이라는게 생겼는데, 이는 한 번에 여러 mutex를 lock에 걸어줄 수 있다.
// 이는 동일 scope내에서 lock_guard를 여러 개 호출 할 때, 위 와 같은 DeadLock 상황에 대해 신경을 쓰지 않아도 된다.
// 아래 처럼 여러 mutex를 걸어주면 scope_lock에서 DeadLock이 발생하지 않게 해준다.

void func1_2(){
    std::scoped_lock<std::mutex, std::mutex> s(m1, m2);
    ++common_value_1;
    ++common_value_2;
}
void func2_2(){
    std::scoped_lock<std::mutex, std::mutex> s(m1, m2);
    --common_value_2;
    --common_value_1;
}

// recursive_mutex
// DeadLock은 lock 하나만으로도 발생할 수 있다.
// 아래와 같이 func3 함수에 m에 대해 lock이 걸려있는 상태에서 func4 함수를 호출하여
// m에 대한 lock을 걸려고 할 때, DeadLock이 발생하게 된다.(self deadlock)

void func4();

std::mutex m;
void func3(){
    std::scoped_lock<std::mutex> s(m);
    func4(); // DeadLock
}

void func4(){
    std::scoped_lock<std::mutex> s(m);
}

// 이러한 상황 자체는 피해야 하겠지만 정말 어쩔수 없는 상황이라면
// 이 땐, recursive_mutex를 사용해야한다.(이러한 상황이 발생한다면 이는 디자인의 실패라 볼 수 있다)
// recursive_mutex는 self lock을 지원하며, 여러 번 lock을 걸수 있다.
// 단, lock을 걸었던 만큼 lock을 해제 해주어야한다.

void func4_1();

std::recursive_mutex r_m;
void func3_1(){
    std::scoped_lock<std::recursive_mutex> s(r_m);
    func4_1();
}
void func4_1(){
    std::scoped_lock<std::recursive_mutex> s(r_m);
}

// unique_lock
// unique_lock은 lock_guard와 비슷하나 추가적인 함수를 함수를 더 제공해준다.
// unique_lock은 생성 시점에 lock을 걸지 않을 수 있고, 소멸하기 전에 unlock 또는 lock을 다시 걸수도 있다.
// 만약 소멸 시점에 lock 걸려있다면 unlock을 수행한다.
// 만약 생성과 동시에 lock을 걸지 않으려면 defer_lock을 인자로 주면 된다.
/*
    std::unique_lock<std::mutex> g(m, std::defer_lock);
    std::unique_lock<std::mutex> g2(m2, std::defer_lock);
    ...
    std::lock(g, g2); // 이 때, lock걸림.
*/

/*
    {
        std::unique_lock<std::mutex> g(m);
    } // 소멸되는 시점에 알아서 unlock
*/

/*
    {
        std::unique_lock<std::mutex> g(m);
        ...
        g.unlock(); // lock 해제
    }
*/

// unique_lock은 unlock을 호출하지 않아 발생하는 문제를 막을 수 있고, 실행 중간에 exception 발생 등에 의한 
// 흐름이 끊기게 되는 경우에도 안전하게 unlock을 해 줄 수 있다.
// unique_lock은 lock_guard보다 유연하며 여러 기능을 제공하지만 mutex의 소유권을 정보를 저장하고 업데이트 하는 공간이 필요로하고
// 부분적으로 lock_guard보다 느리다.
