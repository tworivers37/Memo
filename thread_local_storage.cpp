#include "thread_local_storage.h"

std::mutex mutex;

void thread_function(tls_class* test, int index){
    
    //TLS에 값이 없을 때, 값을 할당.
    //이는 결국 쓰레드 별로 각각 할당하게됨.
    //즉, 쓰레드 별로 test의 tls 값이 다르다는 것.
    if(test->tls.get()==nullptr){
        std::string s="thread" + std::to_string(index);
        test->tls.reset(new std::string(s));
    }

    //출력되는 값이 모두 다름.
    //즉, 쓰레드 별로 tls가 nullptr이라서 새로 할당 되었다는 것을 의미.
    boost::lock_guard<std::mutex> g(mutex);
    std::cout<<std::this_thread::get_id()<<" : "<<*(test->tls)<<"\n";
}

int main(){
    tls_class * test = new tls_class();
    boost::thread threads[10];
    for(int i=0;i<10;++i) threads[i]=boost::thread{thread_function, test, i};
    for(int i=0;i<10;++i) threads[i].join();

    return 0;
}

