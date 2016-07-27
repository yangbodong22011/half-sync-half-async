/*************************************************************************
	> File Name: server.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 21 Jul 2016 05:27:28 PM CST
 ************************************************************************/

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<queue>
#include<sys/epoll.h>
#include<unistd.h>
#include<cstdlib>
#include<arpa/inet.h>
#include<cstring>
#include<thread>

#include"server.h"
#include"error.h"
#include"thpoll.h"

extern std::queue<epoll_event> MessageQueue;

void server::init(thpoll &mythpoll)
{
    error myerror;           
    if((listen_fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        myerror.set("socket",__LINE__).show();
    }

    int option_value = 1;
    int length = sizeof(option_value);
    setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&option_value,length);

    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listen_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) == -1) {
        myerror.set("bind",__LINE__).show();
    }


    if(listen(listen_fd,BACKLOG) == -1) {
        myerror.set("listen",__LINE__).show();

    }
    
    if((epoll_fd = epoll_create(EPOLL_SIZE)) == -1) {
        myerror.set("epoll_create",__LINE__).show();
    }

    ev.data.fd = listen_fd; 
    ev.events = EPOLLIN;   
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&ev) == -1) {
        myerror.set("epoll_ctl",__LINE__).show();
    }
    
    conn_len = sizeof(struct sockaddr_in);

    std::cout << "服务器启动..."<< std::endl; 

    while(1) {
        nfds = epoll_wait(epoll_fd,evs,EPOLL_SIZE,10);
        for(int i = 0;i < nfds;++i) {
            if(evs[i].data.fd == listen_fd) {
                conn_fd = accept(listen_fd,(struct sockaddr *)&conn_addr,&conn_len);
                std::cout << "accept a new connection : "<<inet_ntoa(conn_addr.sin_addr) << "fenpei: " << conn_fd << std::endl;
                ev.data.fd = conn_fd;
                ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
                MessageQueue.push(ev);
                if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,conn_fd,&ev) == -1) {
                    myerror.set("epoll_ctl",__LINE__).show();
                }
            }else if(evs[i].events &  EPOLLIN) {
                std::cout << "\n push EPOLLIN \n" <<std::endl;
                MessageQueue.push(evs[i]);
            }else if (evs[i].events & EPOLLOUT) {
                std::cout << "\n push EPOLLOUT \n" <<std::endl;
                MessageQueue.push(evs[i]);
            }
        }
    }
}


