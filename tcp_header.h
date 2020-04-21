/*************************************************************************
	> File Name: tcp_header.h
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月21日 星期二 10时55分35秒
 ************************************************************************/

#ifndef _TCP_HEADER_H
#define _TCP_HEADER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888     //服务器端口
#define SERVER_IPADDR "192.168.43.43"     //服务器IP地址
#define CLIENT_PORT 8888     //客户端端口
#define CLIENT_IPADDR "192.168.43.43"     //服务器IP地址
#define BACKLOG 5           //最大连接数
#define BUFSIZE 64

#endif
