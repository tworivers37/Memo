#include<iostream>
#include<thread>
#include<boost/bind.hpp>
#include<boost/thread.hpp>
#include<boost/asio.hpp>

/*
    boost::asio::io_service::strand 
        :   strand를 통해 전달된 핸들러는 명시적 동기화가 필요없음.                           
        :   strnad는 두 개의 핸들러가 동시에 실행되지 않는 것을 보장함.

        :   io_context::run이 여러 스레드에서 호출 되었고, 해당 io_context의 post로 동일한 핸들러가
            여러 번 등록되었다면 그 핸들러들은 io_context::run이 호출된 여러 스레드에서 호출이 되게 될 것이다.
            그렇게되면, 핸들러가 한 스레드에서 호출되어 실행되는 도중에 다른 스레드에서 동일한 핸들러가 
            호출되어 실행될 수 있다. 동일한 핸들러이므로 값에 대한 동시접근 문제가 발생할 수 있기에 핸들러 내에서
            명시적으로 lock을 걸어줘야 될 경우가 발생한다.
            그런데 strand는 내부의 핸들러 queue에 post로 등록되는 핸들러를 쌓아놓고 스레드에서 strand 핸들러 queue에서
            차례대로 핸들러를 빼서 호출하므로 핸들러가 여러 스레드에서 동시에 실행되지 않는 것을 보장해준다.

        :   strand 내부 queue에 핸들러를 쌓음. io_context의 work queue에는 각 strand들이 enqueue되고,
            work thread(io_context::run 호출된 스레드)에서는 work queue에서 dequeue하여 strand를 가져가서
            strand의 핸들러 queue에서 핸들러 하나를 꺼내 해당 스레드에서 실행. 즉, 핸들러 queue에 쌓인 순서대로 실행됨.    
*/

boost::mutex cout_mutex;

class target{
    public:
        target() = default;
        target(boost::asio::io_service& io) : st(io){
        }

        void execution(std::size_t num){
            st.get_io_service().post(
                st.wrap(
                    [&, num, this](){
                        {
                            boost::lock_guard<boost::mutex> g(cout_mutex);
                            std::cout<<std::hex<<std::this_thread::get_id()<<" : target num : "<<std::dec<<num<<"\n";
                        }
                    }
                )
            );
        }

    private:
        boost::asio::io_service::strand st;

};

int main(){
    boost::asio::io_service io_s;
       
    target t1(io_s);
    t1.execution(0);
    t1.execution(1);
    t1.execution(2);
    t1.execution(3);
    t1.execution(4);
    t1.execution(5);
    t1.execution(6);
    t1.execution(9999);
    t1.execution(999);
    t1.execution(99);

    boost::function<void()> f(
        [&](){
            {
                boost::lock_guard<boost::mutex> g(cout_mutex);
                std::cout<<std::hex<<std::this_thread::get_id()<<"\n";
            }
            
            io_s.run();
        }
    );

    boost::thread_group tg;
    tg.create_thread(f);
    tg.create_thread(f);
    tg.create_thread(f);

    tg.join_all();

    // 어떤 여러 스레드에서 핸들러가 호출되든 핸들러 등록된 순서를 유지하면서 호출됨.
    // 하나의 strand 내 핸들러 queue에 차례대로 post호출된 순서대로 쌓여있으므로.
    /*
        7f2964820700
        7f2964820700 : target num : 0
        7f2964820700 : target num : 1
        7f2965030700
        7f2964010700
        7f2964820700 : target num : 2
        7f2964820700 : target num : 3
        7f2964820700 : target num : 4
        7f2964820700 : target num : 5
        7f2964820700 : target num : 6
        7f2964820700 : target num : 9999
        7f2964820700 : target num : 999
        7f2964820700 : target num : 99
    */

    return 0;
}