/*************************************************************************
	> File Name: thpoll.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Sat 23 Jul 2016 10:01:08 AM CST
	> description: 
 ************************************************************************/
#include<iostream>
#include<thread>
#include<mutex>
#include<sys/epoll.h>
#include<queue>
#include<sys/types.h>
#include<sys/socket.h>
#include<chrono>
#include<string.h>
#include"thpoll.h"
#include"server.h"


extern std::mutex g_lock;
extern std::queue<epoll_event> MessageQueue;
struct epoll_event ev;

thpoll::thpoll(int size)
{
    for(int i = 0;i < size;++i ) {
        std::shared_ptr<std::thread> t = std::make_shared<std::thread>(&thpoll::func,this);
        poll.push_back(t);
        t->detach();
    }
}

void thpoll::func()
{
    while(1) {
        g_lock.lock();

        if(MessageQueue.empty() == false) {
            std::cout << "从队列中取出来了fd : ";
            ev = MessageQueue.front();
            std::cout << ev.data.fd << std::endl;
            MessageQueue.pop();
            std::cout << "当前队列的长度: " << MessageQueue.size() << std::endl;
            if(ev.events & EPOLLIN) {
                bzero(buf,1024);
                recv(ev.data.fd,buf,1024,0);
                std::cout << "我是线程 : " << std::this_thread::get_id() << " 我读出了: "  << buf << "我将要工作5s" << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(5));
                std::cout << "我工作完了"<< std::endl;
            }else if(ev.events & EPOLLOUT) {
                //bzero(buf,1024);
                strcpy(buf,"来自服务器的消息：收到\n");
                std::cout << "我是线程 : " << std::this_thread::get_id() << "   我将要工作5s" << std::endl;
                send(ev.data.fd,buf,sizeof(buf),0);
                //std::this_thread::sleep_for(std::chrono::seconds(5));
                std::cout << "我工作完了"<< std::endl;
            }
        }
        g_lock.unlock();

    }
}
