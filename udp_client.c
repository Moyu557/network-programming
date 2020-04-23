/*************************************************************************
	> File Name: udp_client.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月21日 星期二 21时13分48秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Uasge: <%s>, <IP>, <PORT>\n", argv[0]);
        return -1;
    }

    int sfd;

    //创建套接字
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }


    //初始化结构体(服务器的结构体)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);


    
    //发送数据
    
    while (1)
    {
        char buf[64];

        //清空buf
        bzero(buf, sizeof(buf));
        
        //获取键盘输入
        fgets(buf, sizeof(buf), stdin);

        //发送数据
        if (sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("sendto");
            return -1;
        }

        //退出
        if (strcmp(buf, "quit\n") == 0)
            break;
    }


    //关闭套接字
    close(sfd);
}
