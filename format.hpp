#ifndef __M_FMT_H__
#define __M_FMT_H__

#include"level.hpp"
#include<ctime>
#include "message.hpp"
#include<vector>
#include <memory>
#include<assert.h>
#include<sstream>

namespace yimingcode
{
  class FormatItem//抽象格式化子类基项
  {
    public:
    using ptr = std::shared_ptr<FormatItem>;
    virtual ~FormatItem() {}
    virtual void format(std::ostream &out, LogMsg &msg)=0;
  };
  
  class MsgFormatItem : public FormatItem {  //消息格式化子项
  public:
    MsgFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << msg._payload;
    }
  };

  class LevelFormatItem : public FormatItem {  //等级格式化子项
  public:
    LevelFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << LogLevel::toString(msg._level);
    }
  };

  class TimeFormatItem : public FormatItem {  //时间格式化子项
  public:
    TimeFormatItem(const std::string &format = "%H:%M:%S")  // 添加构造函数
        : _time_fmt(format) 
    {
        if (format.empty()) _time_fmt = "%H:%M:%S";
    }
    
    void format(std::ostream& out, LogMsg& msg) override {
        struct tm t;
        localtime_r(&msg._ctime,&t);
        char tmp[32] ={0};
        strftime(tmp,31,_time_fmt.c_str(),&t);
        out<<tmp;
    }
  private:
    std::string _time_fmt;
  };

  class FileFormatItem : public FormatItem {  //文件名格式化子项
  public:
    FileFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << msg._file;
    }
  };

  class LineFormatItem : public FormatItem {  //行号格式化子项
  public:
    LineFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << msg._line;
    }
  };

  class ThreadFormatItem : public FormatItem {  //线程ID格式化子项
  public:
    ThreadFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << msg._tid;
    }
  };

  class LoggerFormatItem : public FormatItem {  //日志器名称格式化子项
  public:
    LoggerFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << msg._logger;
    }
  };

  class TabFormatItem : public FormatItem {  //制表符
  public:
    TabFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << '\t';
    }
  };

  class NLineFormatItem : public FormatItem {  //换行
  public:
    NLineFormatItem(const std::string &str = ""){}  // 添加构造函数
    void format(std::ostream& out, LogMsg& msg) override {
        out << "\n";
    }
  };

  class OtherFormatItem : public FormatItem {  //普通字符串
  public:
    OtherFormatItem(const std::string &str)  // 已有构造函数，保持不变
        :_str(str)
    {
    }
    void format(std::ostream& out, LogMsg& msg) override {
        out << _str;
    }
  private:
    std::string _str;
  };

  /*
    %d 日期
    %t 线程id
    %c 日志器名称
    %l 原码行号
    %p 日志等级
    %T 制表符缩进
    %m 主体消息
    %n 换行
  */
  class Formatter
  {
  public:
    Formatter(const std::string &pattern ="[%d{%H:%M:%S}][%t][%c][%f:%l][%p]%T%m%n"):
      _pattern(pattern)
    {
        assert(parsePattern());
    }
    
    void format(std::ostream &out, LogMsg &msg)
    {
        for(auto &item :_items)
        {
            item->format(out,msg);
        }
    }
    
    std::string format(LogMsg &msg)
    {
        std::stringstream ss;
        format(ss,msg);
        return ss.str();
    }
    
    bool parsePattern()//对格式化规则字符进行解析
    {
      //1.对格式化规则字符进行解析
      //abcde[%d{%H:%M%S}][%p]%T%m%n
      //2.根据解析得到的数据初始化格式化子项初始成员
      return;
    }

  private:
    FormatItem::ptr createItem(const std::string &key, const std::string &val)
    {
        if(key == "d") {
            // 如果val为空，使用默认格式
            std::string fmt = val.empty() ? "%H:%M:%S" : val;
            return std::make_shared<TimeFormatItem>(fmt);
        }
        if(key == "t") {
            return std::make_shared<ThreadFormatItem>();
        }
        if(key == "c") {
            return std::make_shared<LoggerFormatItem>();
        }
        if(key == "f") {
            return std::make_shared<FileFormatItem>();
        }
        if(key == "l") {
            return std::make_shared<LineFormatItem>();
        }
        if(key == "p") {
            return std::make_shared<LevelFormatItem>();
        }
        if(key == "T") {
            return std::make_shared<TabFormatItem>();
        }
        if(key == "m") {
            return std::make_shared<MsgFormatItem>();
        }
        if(key == "n") {
            return std::make_shared<NLineFormatItem>();
        }
        
        return std::make_shared<OtherFormatItem>(val);
    }
    
  private:
    std::string _pattern;
    std::vector<FormatItem::ptr> _items;
  };
}

#endif