/*************************************************************************
	> File Name: tcp_server.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月21日 星期二 20时54分59秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_IP "192.168.17.129"
#define SERVER_PORT 6666


void server_func(void* cfd);


int main()
{
    int sfd;

    //创建套接字
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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


    //允许地址重用
    int REUSE = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &REUSE,sizeof(REUSE));


    //绑定本机地址和端口
    if (bind(sfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind");
        return -1;
    }


    //转换监听套接字
    if (listen(sfd, 5) < 0)
    {
        perror("listen");
        return -1;
    }


    //接受连接请求
    int cfd;

    #if 0

    if ((cfd = accept(sfd, NULL, NULL)) < 0)
    {
        perror("accept");
        return -1;
    }
    
    printf("Server standing...\n");

    
    //读取数据
    
    while (1)
    {
        char buf[64];

        read(cfd, buf, sizeof(buf));

        if (strcmp(buf, "quit\n") == 0)
            break;
        else
            printf("recv > %s", buf);
    }


    //关闭套接字
    close(cfd);

    #endif

    //多线程实现并发
    //pthread_t tid;

    //多进程实现并发
    pid_t pid;

    while (1)
    {
        //接受连接请求
        if ((cfd = accept(sfd, NULL, NULL)) < 0)
        {
            perror("accept");
            return -1;
        }

        printf("Server standing...\n");

        //创建线程
        //pthread_create(&tid, NULL, (void*)&server_func, (void*)&cfd);
        
        //创建进程
        if ((pid = fork()) < 0)
        {
            perror("fork");
            return -1;
        }


        //子进程
        if (pid == 0)
        {
            close(sfd);     //关闭监听套接字
            

            //读取数据
            while (1)
            {
                char buf[64];

                //read(newfd, buf, sizeof(buf));
                read(cfd, buf, sizeof(buf));

                if (strcmp(buf, "quit\n") == 0)
                {
                    //printf("Client(fd = %d) is exit\n", newfd);
                    
                    printf("Client(fd = %d) is exit\n", cfd);
                    break;
                } 
                else
                printf("recv > %s", buf);
            }

            close(cfd);
        }
    }
   
    //关闭套接字
    //close(sfd);
}

void server_func(void* cfd)
{
    int newfd = *(int*)cfd;

    printf("newfd = %d\n", newfd);


    //读取数据
    while (1)
    {
        char buf[64];

        read(newfd, buf, sizeof(buf));

        if (strcmp(buf, "quit\n") == 0)
        {
            printf("Client(fd = %d) is exit\n", newfd);
            break;
        } 
        else
            printf("recv > %s", buf);
    }


    //关闭套接字
    close(newfd);
}
