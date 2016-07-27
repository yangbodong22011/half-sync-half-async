/*************************************************************************
	> File Name: server.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 21 Jul 2016 04:02:06 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include<queue>
#include<sys/epoll.h>
#include<netinet/in.h>
#include"thpoll.h"

#define BACKLOG 1024                         //listen 的第二个参数 backlog
#define EPOLL_SIZE 1024                      //epoll_create 向内核中注册的兴趣事件的个数，虽然在内核2.6之后没用
#define SERV_PORT 8888

class server {
public:
    void init(thpoll &);

private:
    int  listen_fd;                           //socket返回
    int  epoll_fd;                            //epoll_create 返回
    int  conn_fd;                             //accept返回
    int  nfds;                                //epoll_wait 返回
    socklen_t  conn_len;
    struct sockaddr_in serv_addr,conn_addr;
    struct epoll_event ev, evs[EPOLL_SIZE];

};




#endif
