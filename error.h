/*************************************************************************
	> File Name: error.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 21 Jul 2016 06:06:46 PM CST
    > description: 错误日志类
 ************************************************************************/

#ifndef _ERROR_H
#define _ERROR_H

#include<errno.h>

class error {
public:

    error() = default;

    error(const std::string errmsg,int errline) {
        msg = errmsg;
        line = errline;
    }
    
    void show() {
        std::cerr << line << " : ";
        perror(msg.c_str());
    }

    error set(const std::string errmsg, const int errline) {
        msg = errmsg;
        line = errline;
        
        return *this;
    }
private:
    std::string msg;
    int  line;
    
};


#endif
