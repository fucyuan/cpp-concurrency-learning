#include<iostream>
#include<thread>
#include<string>
void thread_function(const std::string& name){
    std::cout<<"name of thread is "<<name<<std::endl;
}
class background_task
{ 
public:
    void operator()(std::string name){
        std::cout<<"name of background task is "<<name<<std::endl;

    }
};


int main(){
    std::string name="hello_thread";
    std::thread t(thread_function,name);//普通函数
    t.join();
    std::thread t2(background_task(),name);//仿函数
    t2.join();
    std::thread t4([](std::string name){std::cout<<"name of lambda thread is "<<name<<std::endl;},name);//lambda表达式
    t4.join();
    return 0;
}