 #include <iostream>
#include"level.hpp"
#include"util.hpp"
#include"message.hpp"
#include"format.hpp"


int main()
{
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::DEBUG);
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::INFO);
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::WARN);
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::ERROR);
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::FATAL);
    //  std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::OFF);
     
    yimingcode::LogMsg msg(yimingcode::LogLevel::value::INFO, 53, "main.c","root","格式化功能测试");
    yimingcode::Formatter fmt;
    
    return 0;
}