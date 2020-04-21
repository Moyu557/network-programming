/*************************************************************************
	> File Name: tcp_client.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月21日 星期二 09时58分26秒
 ************************************************************************/

#include "tcp_header.h"

int main()
{
    int sfd;
    
    //创建套接字
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }


    //创建结构体
    struct sockaddr_in myaddr;
    
    //清空
    memset(&myaddr, 0, sizeof(myaddr));

    //补充结构体
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(CLIENT_PORT);
    myaddr.sin_addr.s_addr = inet_addr(SERVER_IPADDR);
    
    //请求连接
    if (connect(sfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("connect");
        return -1;
    }


    //读写数据
    while (1)
    {
        char buf[BUFSIZE];
        fgets(buf, BUFSIZE, stdin);
        write(sfd, buf, BUFSIZE);
    }

    //关闭套接字
    close(sfd);
}
