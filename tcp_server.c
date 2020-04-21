/*************************************************************************
	> File Name: tcp_server.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月20日 星期一 17时09分34秒
 ************************************************************************/

#include "tcp_header.h"

int main()
{
    int sfd;    //套接字

    
    //创建套接字
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    //创建结构体类型，并清空
    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));
    
    
    //填充结构体信息
    myaddr.sin_family = PF_INET;    //地址族
    myaddr.sin_port = htons(SERVER_PORT);  //端口
#if 1
    myaddr.sin_addr.s_addr = inet_addr(SERVER_IPADDR);   //IP地址
#else
    //使用inet_pton来转换IP地址
    if ((inet_pton(AF_INET, SERVER_IPADDR, (void*)&myaddr.sin_addr.s_addr)) != 1)
    {
        perror("inet_pton");
        return -1;
    }
#endif

    
    //绑定本机地址和端口
    if (bind(sfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind");
        return -1;
    }

    
    //设置监听套接字，同时允许最大2*BACKLOG+1 = 11个客户端或者服务器连接
    if (listen(sfd, BACKLOG) < 0)
    {
        perror("listen");
        return -1;
    }


    //服务器接受连接请求，返回通信文件描述符
    int connect_fd;
    if ((connect_fd = accept(sfd, NULL, NULL)) < 0)
    {
        perror("accept");
        return -1;
    }


    //循环读取数据
    while (1)
    {
        char buf[BUFSIZE];
        int ret;

        //读取数据
        if ((ret = read(connect_fd, buf, BUFSIZE)) > 0)
        {
            if (strcmp(buf, "quit\n") != 0)
                //打印收到的数据
                printf("Recv > %s", buf);
            else
                break;
        }
    }

    //关闭文件描述符
    close(sfd);
    close(connect_fd);
}
