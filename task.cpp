#include<iostream>
#include<thread>
#include<future>
#include<chrono>

// task는 thread 보다 한 단계 더 추상화 된 것이라 보면 된다.
// thread 기반일 때(thread 단위 수준에서), 어떤 작업을 비 동기적으로 하고 싶을 때, 직접 여러 thread를 만들고 관리해서 결과를 얻는다.
// 그러나 task 기반이라고 하면 우리는 비 동기적(std::asyc)으로 작업을 진행해라 라고 동작해야할 부분을 던져주고 결과만 확인 하면된다.
// 비 동기를 위해 내부적으로 thread를 더 만들던던 현재 thread에서 진행하던 그건 우리가 생각해야 할 부분이 아니다.
// 어떻게든 작업이 비 동기적으로 진행되기만 하면 된다.

// task는 작업 패키지 단위로 동작하며 promise와 future 등 서로 연동되는 두 컴포넌트로 구성.
// promise와 future은 연결된다고 보면되는데, promise는 발신자, future은 수신자 역할.
// promise에서 값을 set 하지 않으면 future의 get에선 계속 promise에 값이 set될 때까지 블로킹 상태.
// promise와 future 사이는 암묵적으로 보호되어, mutex 같은 보호 메커니즘을 사용해선 안 된다.
// future는 값을 딱 한 번만 요청해서 얻어올 수 있다. 만약 두 번이상 값을 요청하려면 std::shared_future를 사용해야한다.
// promise는 하나 이상의 future와 연동 가능하며, 값이나 예외 또는 알람을 future로 보낸다.


// std::async 함수는 비 동기 함수와 유사하며, 인자와 콜백함수를 받을 수 있다.
// std::async의 리턴 타입은 future이며, 리턴 값은 std::async로 전달된 콜백함수의 리턴 값이 할당되게 된다.
// std::async는 런타임에 별도의 thread에서 실행 될 지를 결정하게된다. std::async로는 실행해야할 task만 지정 할 뿐 이다.

// 부모 thread와 자식 thread 사이에 값을 주고 받을려면 두 thread가 모두 접근 가능한 메모리 영역에 변수를
// 할당해서 사용해야 하기에 잘못 사용 할 가능성이 있다. 
// 그러나 task에선 promise, future를 통해, 이 보다 한결 명시적이다.
// 생성된 thread에서 예외가 발생하면 thread는 중지되고, 상황에 따라 전체 프로세스가 중지된다.
// 이와 반대로 promise는 예외 처리 의무를 가진 future로 예외를 보낼 수 있다.


// ex1
void task1(){
    int ret = 0;
    std::thread t(
        [&]{
            std::cout<<"task1 thread lambda - thread id : "<<std::this_thread::get_id()<<"\n";
            ret = 1;
        }
    );

    t.join();

    std::cout<<"ret : "<<ret<<"\n";

    auto fut = std::async(
        []{
            std::cout<<"task1 async lambda - thread id : "<<std::this_thread::get_id()<<"\n";
            return 1 + 1;
        }
    );

    int fut_value = fut.get();
    std::cout<<"fut : "<<fut_value<<"\n";
}

// std::async는 호출되자마자 실행되는 eagar evaluation과 나중에 필요 할 때, 실행되는 lazy evaluation 방식이 있다.
// lazy evaluation을 사용하면 필요에 따라 실행하지 않을 수 있기에 컴퓨팅 파워를 줄일 수 있다.
// std::async는 기본적으로 eagar evaluation으로 곧 바로 실행된다.
// eagar evaluation 방식으로 하려면 std::launch::deferred를 첫 번째 인자로 주면되고 lazy evaluation 방식으로 하려면
// std::launch::async을 첫 번째 인자로 주면된다.

// ex2
void task2(){
    auto begin_time = std::chrono::system_clock::now();

    auto fut = std::async( 
        []{
            std::cout<<"task2 evaluation - thread id : "<<std::this_thread::get_id()<<"\n";
            return std::chrono::system_clock::now();
        }
    );

    auto eagar_fut = std::async(std::launch::deferred, 
        []{
            std::cout<<"task2 eagar evaluation - thread id : "<<std::this_thread::get_id()<<"\n";
            return std::chrono::system_clock::now();
        }
    );

    auto lazy_fut = std::async(std::launch::async,
        []{
            std::cout<<"task2 lazy evaluation - thread id : "<<std::this_thread::get_id()<<"\n";
            return std::chrono::system_clock::now();
        }
    );

    auto eagar_start_time = eagar_fut.get() - begin_time;
    auto lazy_start_time = lazy_fut.get() - begin_time;
    auto start_time = fut.get() - begin_time;

    auto eagar_duration = std::chrono::duration<double>(eagar_start_time).count();
    auto lazy_duration = std::chrono::duration<double>(lazy_start_time).count();
    auto duration = std::chrono::duration<double>(start_time).count();

    std::cout<<"empty : "<<duration<<"\n";
    std::cout<<"eagar : "<<eagar_duration<<"\n";
    std::cout<<"lazy : "<<lazy_duration<<"\n";


    // main thread id : 140631974872896
    // ......
    // task2 evaluation - thread id : 140631955998464
    // task2 eagar evaluation - thread id : 140631974872896
    // task2 lazy evaluation - thread id : 140631947544320
    // empty : 0.0009596
    // eagar : 0.0019925
    // lazy  : 0.0029236

    // 대략 위 처럼 나올 수 있는데, lazy가 get 호출 할 때, 실행되기에 duration이 eagar보다 더 큼.
    // thread id를 보면 std::launch::deferred 같은 경우(eagar evaluation)는 main thread의 id 와 동일. 즉, 하나의 thread에서 처리됨.
    // 이와 반대로 std::launch::async 같은 경우는 새로운 thread가 생성되고 거기서 실행됨.
    // 첫 번쨰 인자에 아무 것도 없는 거 같은 경우는 가장 앞서서 호출되었고 인자가 없을 땐, 즉시 실행이기에 duration이 가장 작다.
    // thread 같은 경우는 eagar evalution과는 다르게, 바로 실행되나 새로운 thread에서 실행 된 것을 확인 할 수 있다.
}

// fire & forget future라고 하는 것이 있는데, 이는 아래와 같다.
void task3(){
    // 일반 future
    auto fut = std::async(std::launch::async, [](){ return 100; });
    std::cout<<fut.get()<<"\n";

    // fire and forget future
    // std::async 의 리턴 값을 받는 변수가 없음.
    // 변수에 바인딩 되지 않으므로 곧바로 실행.
    // 별도의 thread를 만들어서 콜백함수 실행.
    std::async(std::launch::async, []{ std::cout<<"fire and forget\n"; });

    // fire and forget future에서 std::async에 의해 생성된 future는 promise가 완료될 때까지 destructor를 기다린다.
    // 즉, 콜백 함수가 끝날 때까지 멈춰있게 된다.
    // 그러므로 아래와 같은 경우 차례대로 cout이 출력될 것이다.
    std::async(std::launch::async, 
        [](){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout<<"first\n";
        }
    ); // 콜백 함수 끝날 때까지 대기.

    std::async(std::launch::async, 
        [](){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout<<"second\n";
        }
    );

}


int main(){
    std::cout<<"main thread id : "<<std::this_thread::get_id()<<"\n";
    std::cout<<"---------------------------------------------------------------------\n";
    task1();
    std::cout<<"---------------------------------------------------------------------\n";
    task2();
    std::cout<<"---------------------------------------------------------------------\n";
    task3();
    std::cout<<"---------------------------------------------------------------------\n";

    return 0;
}