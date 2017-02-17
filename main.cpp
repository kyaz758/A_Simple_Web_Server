/******************************************************************************
 ***** File Name : main.cpp
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2017-02-11 11:57
 * Last Modified : 2017-02-17 12:10
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
using namespace std;

#define IP "127.0.0.1"
#define PORT 8080

//socket server
//socket()
//bind()
//listen(socket, 5) //转换socket状态，第二个参数的意义
//已经完成链接，却没被accept接收的socket，存放于队列中，backlog参数指定其大小
//一般超出其大小，导致失败，但有些具有重连机制，会暂时不进行报错，一旦成功即可
//accept(socket,) 无法接收主动状态的socket，故需要listen进行转化
//socket状态的意义：主动状态的socket无需额外资源来建立链接，
//而被动状态的socket需要队列（内存）和其他系统资源，故将socket划分状态
//accept进行的时机：
//在三次握手的第二次握手时已经建立链接，已经可以携带需要传输的数据。

int main()
{
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd == -1)
    {
        perror("Socket failed.");
        exit(-1);
    }
    struct sockaddr_in listenAddr;
    bzero(&listenAddr, sizeof(listenAddr));
    listenAddr.sin_family = AF_INET;
    //ip
    inet_pton(AF_INET, IP, &(listenAddr.sin_addr.s_addr));
    //port
    listenAddr.sin_port = htons(PORT);

    //支持可扩展的类型
    int ret = bind(listenFd, 
                (struct sockaddr *) &listenAddr, 
                sizeof(listenAddr));
    //C语言高级技巧，实现泛型，这里的强转保证了即使未来协议变化，但接口依旧可用
    if (ret == -1)
    {
        perror("Bind failed.");
        exit(-1);
    }
    printf("Bind successed %s:%d\n", IP, PORT);
    ret = listen(listenFd, 5);
    if (ret == -1)
    {
        perror("Listen failed.");
        exit(-1);
    }
    printf("Listen successed %s:%d\n", IP, PORT);
    ///
    int clientFd = -1;
    while (1)
    {
        clientFd = accept(listenFd, NULL, 0);
        printf("A new connect is establishing.\n");
        uint8_t buf[1024];
        again:
        int ret = recv(clientFd, buf, 1024, 0);
        //返回0代表数据接收完毕
        if (ret == -1) // 是否意味着真的发生了错误？可能是被意外的信号打断
        {
            if (errno == EINTR)
            {
                goto again;
            }
            perror("Recv error.");
            close(clientFd);
            continue;
        }
        //以用户模式实现
        HttpRequest p(clientFd);
        while (p.isHasNextLine())
        {
            p.getNextLine();
        }
        //recv(clientFd, buf, bufLen);
        // 请求
        // 读取数据，判断数据（的完整性）
        // 解析HTTP请求
        //
        // 方式 路径 协议
        // GET / HTTP/1.1^M
        // Host: loaclhost:8080^M
        // Connection: keep-alive^M
        // Cache-Control: max-age=0^M
        // Upgrade-Insecure-Requests: 1^M
        
        // http响应
        /*
        const char *response = "HTTP/1.0 200 OK\r\n"
            "Accept-Ranges: bytes\r\n"
            "Last-Modified: Fri, 13 Jan 2017 03:13:14 GMT\r\n"
            "Content-Type: text/c; charset=UTF-8\r\n"
            "Contect-Length: 5\r\n"
            "Date: Fri, 10 Feb 2017 03:55:49 GMT\r\n"
            "\r\n"
            "Hello";
            */
        HttpResponse rep(200);
        rep.headersAdd("Accept-Ranges", "bytes");
        rep.headersAdd("Last-Modified", "Fri, 13 Jan 2017 03:13:14 GMT");
        rep.headersAdd("Content-Type", "text/c; charset=UTF-8");
        rep.headersAdd("Content-Length", "5");
        rep.headersAdd("Date", "Fri, 10 Feb 2017 03:55:49 GMT");
        rep.writeBody("hello");
        string package = rep.getPackage();
        send(clientFd, package.data(), package.length(), 0);
        //send(clientFd, response, strlen(response), 0);
        close(clientFd);
        clientFd = -1;
    }
    return 0;
}
//.configure
//make
//sudo make install
//1.适度包装
//2.个性
//3.男同学头像意义不大
