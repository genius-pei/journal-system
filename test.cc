 #include <iostream>
#include"level.hpp"


int main()
{
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::DEBUG);
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::INFO);
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::WARN);
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::ERROR);
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::FATAL);
     std::cout<<yimingcode::LogLevel::toString(yimingcode::LogLevel::value::OFF);
     
    return 0;
}