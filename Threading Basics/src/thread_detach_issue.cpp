#include<iostream>
#include<thread>
#include<chrono>

// 定义一个结构体，用于在线程中修改外部整数变量的值
struct func
{
    int &_i;
    func(int& i):_i(i){

    }
    // 重载operator()，使结构体对象可以作为线程函数执行
    void operator()(){
        for(int i=0;i<3;i++){
            _i=i;
            std::cout<<"_i is"<<_i<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

// 此函数创建一个线程并分离它，可能导致主线程结束时子线程尚未完成
void oops(){
    int some_local_state=0;
    func f(some_local_state);
    std::thread functhread(f);

    // 分离线程，使其独立于创建它的线程
    functhread.detach();

    // 分离后主线程无需等待子线程完成
}

// 此函数创建一个线程并使用join等待其完成
void use_join(){
    int some_local_state=0;
    func f(some_local_state);
    std::thread functhread(f);
    // 使用join等待线程结束
    functhread.join();
}

void catch_exceptions(){
    int some_local_state=0;
    func f(some_local_state);
    std::thread functhread(f);
    try{
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }catch(std::exception & e){
        functhread.join();
        throw;
    }
    functhread.join();
}
class thread_guard
{
private:
    /* data */
    std::thread & _t;
public:
   explicit thread_guard(std::thread &t):_t(t){}
   ~thread_guard(){
    if(_t.joinable()){
        _t.join();
    }
   }
   thread_guard(thread_guard const&)=delete;
   thread_guard& operator=(thread_guard const&) = delete;
};
void auto_guard(){
   int some_local_state=0;
   func f(some_local_state);
   std::thread t(f);
   // 自动管理线程，当线程结束时自动调用join
   thread_guard g(t);
   std::cout<<"auto_guard"<<std::endl;
}
int main(){
    // // 调用oops函数演示分离线程的问题
    // oops();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // 调用use_join函数演示正确等待线程结束的方式
    use_join();
    catch_exceptions();
    auto_guard();
    return 0;
}