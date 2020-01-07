#include<iostream>
#include<thread>
#include<mutex>

thread_local int value = 1;
std::mutex mutex;

void thread_function(int i){
    //쓰레드 별로 value를 각각 가짐.
    //전역변수로 보이나 그렇지 않고 여러 쓰레드에서 동시에 하나의 변수에 접근하는게 아니라
    //각 쓰레드에서 각자의 변수에 접근하는 형태.(thread local storage)
    value+=i;
    std::lock_guard<std::mutex> g(mutex);
    std::cout<<std::this_thread::get_id()<<" : thread"<<i<<" / "<<value<<"("<<&value<<")"<<"\n";
}

int main(){
    std::thread threads[10];
    for(int i=0;i<10;++i) threads[i]=std::thread{thread_function, i};
    for(int i=0;i<10;++i) threads[i].join();

    return 0;
}