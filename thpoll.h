/*************************************************************************
	> File Name: thpoll.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Sat 23 Jul 2016 09:28:40 AM CST
	> description: 
 ************************************************************************/
#ifndef _THPOLL_H
#define _THPOLL_H

#include<vector>
#include<thread>
#include<string>


class thpoll {
public:
    thpoll() = default;
    thpoll(int size);
    void func();

private:
    std::vector<std::shared_ptr<std::thread>> poll;         
    int size;
    int popfd;
    char buf[1024];
};
#endif

