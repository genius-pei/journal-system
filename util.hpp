
#include<iostream>
#include<ctime>
#include<unistd.h>
#include<sys/stat.h>
#include<string>

namespace yimingcode{
    namespace util
    {
        class Date
        {
            public:
            static size_t getTime()
            {
                return (size_t)time(nullptr);
            }
        };

        class File
        {
            public:
            static bool exists(const std::string &pathname)//判断文件是否存在
            {
                struct stat st;
                if(stat(pathname.c_str(),&st)<0)
                {
                    return false;
                }
                return true;
            }
            static std::string path(const std::string &pathname)//获取文件路径
            {
                size_t pos =pathname.find_last_of("/\\");
                if(pos==std::string::npos)
                {
                    return ".";
                }
                return pathname.substr(0,pos+1);
            }
           
            static void createDirectory(const std::string &pathname)//创建目录
            {
                size_t pos =0,idx=0;
                while(idx<pathname.size())
                {

                pos =pathname.find_first_of("/\\",idx);
                if(pos == std::string::npos)
                {
                       mkdir(pathname.c_str(),0777);
                }
                std::string parent_dir = pathname.substr(idx,pos - idx + 1);
                if(parent_dir=="."||parent_dir=="..")
                {
                    idx=pos+1;
                    continue;
                }
                if(exists(parent_dir)==true) 
                {
                    idx=pos+1;
                    continue;
                }
                 mkdir(pathname.c_str(),0777);
                  idx=pos+1;
                }
            }
        };

    }
    

}