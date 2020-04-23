/*************************************************************************
	> File Name: udp_server.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月22日 星期三 22时01分50秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888
#define SERVER_IP "192.168.17.135"

int main()
{
    int sfd;

    //创建套接字
    if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }


    //初始化结构体
    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(SERVER_PORT);
    myaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    //绑定本机地址和端口
    if (bind(sfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind");
        return -1;
    }

    printf("Server starting...\n");


    //接收数据
    char buf[64];

    while (1)
    {
        bzero(buf, sizeof(buf));    //将buf清空
        struct sockaddr_in client;  //接受对象的结构体信息
        socklen_t addrlen = sizeof(client);     //结构体的大小

        if (recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr*)&client, &addrlen) < 0)
        {
            perror("recvform");
            return -1;
            continue;
        }

        if (strcmp(buf, "quit\n") == 0)
        {
            printf("Client exit.\n");
        }
        else
        {
            char client_ip[16];     //存放客户端的IP信息

            //将IP信息（网络字节序），转换为字符串
            if (inet_ntop(AF_INET, (void*)&client.sin_addr, client_ip, sizeof(client)) != 0)
            {
                perror("inet_ntop");
                return -1;
            }


            printf("recvfrom(%s:%d) > %s", client_ip, ntohs(client.sin_port), buf);
        }
    }

    close(sfd);
}
