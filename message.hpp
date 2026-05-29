#include<iostream>
#include<string>
#include<thread>
#include"level.hpp"

namespace yimingcode
{
    struct LogMsg
    {
        size_t ctime;//日志产生的时间戳
        LogLevel::value _level;//日志等级
        size_t _line;
        std::thread::id _tid;
    };
    
}