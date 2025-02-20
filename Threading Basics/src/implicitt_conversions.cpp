#include<iostream>
#include<thread>
#include<cstdio>
#include<string>
#include<chrono>
void print_string(int times,const std::string& str){
    for(int i=0;i<times;i++){
        std::cout<<"Printing string: "<<str<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void danger_function(int some_param){
    char buffer[1024];
    std::sprintf(buffer,"Danger function called with parameter %d",some_param);
    std::string str(buffer);//转换成为std::string类型？
    std::thread t(print_string,10,str);
    // std::thread t2(print_string,10,buffer);//错误，buffer是const char*类型
    t.join();
    // t2.detach();//错误
    std::cout<<buffer<<std::endl;
}

int main(){
    danger_function(42);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return 0;

}