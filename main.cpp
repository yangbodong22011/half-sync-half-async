/*************************************************************************
	> File Name: main.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Fri 22 Jul 2016 02:57:51 PM CST
	> description: 
 ************************************************************************/

#include<iostream>
#include<memory>
#include<queue>
#include<mutex>
#include"server.h"
#include"thpoll.h"

std::queue<epoll_event> MessageQueue;         //全局的任务队列
thpoll mythpoll(3);                   //初始化线程池，3个线程
std::mutex g_lock;                    //锁

int main(int argc,char *argv[])
{
    auto s = std::make_shared<server>();
    s->init(mythpoll);
    return 0;
}

