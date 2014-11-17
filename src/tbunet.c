#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
//#define DEBUG 1
#include "tbupub.h"
#include "tbunet.h"


//定义最大网卡个数
#define MAXINTERFACES 16  

/*
 * 功能：获取网卡IP
 * 参数：netcard_name   网卡名称
 *       ip             获得的IP地址
 * 返回值：
 *      成功返回ip指针，失败返回NULL
 */
char *get_ipconfig(const char *netcard_name, char *ip)
{
        int sockfd; 
        sockfd = socket(PF_INET, SOCK_STREAM, 0);
        if (-1 == sockfd) 
        {
                perror("socket");
                return NULL;
        }

        struct ifreq req;
        struct sockaddr_in *host = NULL;
        memset(&req, 0, sizeof(struct ifreq));
        strcpy(req.ifr_name, netcard_name);

        if (ioctl(sockfd, SIOCGIFADDR, &req)) 
        {
                perror("ioctl");
                return NULL;
        }
        host = (struct sockaddr_in*)&req.ifr_addr;
        strcpy(ip, inet_ntoa(host->sin_addr));
        close(sockfd);

        return ip;
}

/*
 * 功能：将所有活动的网卡IP保存起来
 */
struct netcard_info *get_local_ip(struct netcard_info **netinfo)  
{        
        struct sockaddr_in sockfd;
        int fd;    
        int i;    
        int count;

        //存储获取的ip地址的信息
        struct ifreq buf[MAXINTERFACES];    
        //存储网络接口的信息
        struct ifconf ifc;    

        struct netcard_info head;
        struct netcard_info *tail = &head;

        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd < 0) 
                return NULL;

        ifc.ifc_len = sizeof(buf);      //存储获取的ip地址的信息的长度
        ifc.ifc_buf = (caddr_t)buf;     //存储获取的ip地址的信息的首地址

        if (ioctl(fd, SIOCGIFCONF, &ifc)) 
        {   //获取网卡信息，存储在buf中 
                close (fd);    
                return NULL;
        }

        count = ifc.ifc_len / sizeof(struct ifreq);    
        for (i = 0; i < count; i++) 
        {    
                if (!(ioctl (fd, SIOCGIFADDR, &buf[i]))) 
                {    
                        memset(&sockfd, 0, sizeof(struct sockaddr_in));
                        memcpy(&sockfd, &buf[i].ifr_addr, sizeof(struct sockaddr));
                        tail->next = (struct netcard_info *)malloc(sizeof(struct netcard_info));

                        strcpy(tail->next->name, buf[i].ifr_name);
                        strcpy(tail->next->ip, inet_ntoa(sockfd.sin_addr));
                        tail->next->next = NULL;

                        tail = tail->next;
                }                        
        }
        close (fd);    

        *netinfo = head.next;
        return head.next;
}

int free_net_info(struct netcard_info **head)
{
        if (NULL == head || NULL == *head) 
                return TBU_ERR;

        while (*head) 
        {
                struct netcard_info *p = *head;
                *head = p->next;
                free(p);
                p = NULL;
        }
        return TBU_OK;
}

void show_net_info(struct netcard_info *head)
{
        int i = 1;
        while (NULL != head) 
        {
                printf("网卡%d: %s \tIP: %s\n", i, head->name, head->ip);
                head = head->next;
                i++;
        }
}

/*
int main()
{
        struct netcard_info *info = NULL;
        get_local_ip(&info);
        show_net_info(info);
        free_net_info(&info);
        return 0;
}
*/



/*
 * 功能：创建TCP并发服务器
 */
int create_tcp_server(int port, tcp_client handle_client)
{

        int servdesc;
        socklen_t servsocklen;
        struct sockaddr_in servaddr;

        int clientdesc;
        socklen_t clisocklen;
        struct sockaddr_in cliaddr;

        pid_t pid;

        signal(SIGCLD, SIG_IGN);//防止僵

        //1.创建套接字
        if((servdesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("socket error");
                return TBU_ERR;
        }

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port); 
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        memset(&servaddr.sin_zero, 0, 8);

        servsocklen = (socklen_t)sizeof(servaddr);
        clisocklen = (socklen_t)sizeof(cliaddr);

        //2.将本地地址与套接字绑定
        if((bind(servdesc, (struct sockaddr *)&servaddr, servsocklen)) < 0)
        {
                perror("bind error");
                return TBU_ERR;
        }

        //3.监听
        if(listen(servdesc, 5) < 0)
        {
                perror("Listen Error");
                return TBU_ERR;
        }

        printf("监听端口号:%d\n", port);

        while(1)
        {
                //4.接受客户端连接
                //阻塞式
                if((clientdesc = accept(servdesc, (struct sockaddr *)&cliaddr, &clisocklen)) < 0)
                {
                        perror("accept error");
                        return TBU_ERR;
                }

                //创建进程
                pid = fork();
                if(pid < 0)//创建失败
                {
                        perror("fork error");
                        return TBU_ERR;
                }
                if(pid == 0)//子进程
                {
                        printf("处理客户端\n");
                        close(servdesc);//子进程关闭服务端描述符
                        //(*handle_client)(clientdesc); 
                        handle_client(clientdesc); 

                        //等待客户端读取数据
                        sleep(1);
                        close(clientdesc);
                        return TBU_OK;
                }
                close(clientdesc);//父进程关闭客户端描述符
        }
        return TBU_OK;
}


/*
 * 功能：连接服务器，并可以接收和发送数据
 * 参数：
 *      hostname        服务器IP
 *      port            服务器端口
 * 返回值：
 *      -1              失败
 *      >0              socket描述符
 *
 * */
int conn_server(const char *hostname, const int port)
{
        int socketfd;
        struct sockaddr_in svr_addr;
        int option;

        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (-1 == socketfd) 
        {
#ifdef DEBUG
                perror( "socket:" );
                printf("%s %d\n", __FILE__, __LINE__);
#endif
                return TBU_ERR;
        }

        // 设置地址可复用
        option = 1;
        setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        // 服务器IP
        memset(&svr_addr, 0, sizeof(svr_addr));
        svr_addr.sin_family = AF_INET;
        svr_addr.sin_addr.s_addr = inet_addr(hostname);
        svr_addr.sin_port = htons(port);

        //printf("%s:%d\n", hostname, port);
        // 连接
        if (-1 == connect(socketfd, (struct sockaddr *) &svr_addr, sizeof(svr_addr))) 
        {
#ifdef DEBUG
                perror( "connect" );
                printf("%s %d\n", __FILE__, __LINE__);
#endif
                close(socketfd);
                return TBU_ERR;
        }
        printf("connect to %s:%d successed.\n", hostname, port );
        return socketfd;
}

/*
 * 功能：发送数据到服务器连接sockfd
 * */
int tcp_send(int sockfd, char *sendbuf, int slen)
{
        int httplen = slen;
        int sz = 0;         //实际发送出去的长度
        int index = 0;      //读取缓冲区的下标
        int len = 0;        //每次send数据的长度

        //printf("%s\n", sendbuf);
        while (httplen > 0) 
        {
                sz = 0;
                if (httplen >= 1024) 
                {
                        len = 1024;
                } 
                else 
                {
                        len = httplen;
                }

                sz = write(sockfd, sendbuf + index, len);
                index += sz;
                httplen -= sz;
                if (sz < 1024)
                        break;
        }
        return TBU_OK;
}

/*
 * 功能：从服务器连接接收数据
 * */
int tcp_receive(int sockfd, char *rcvbuf, int rlen)
{
        int httplen = 0;
        int sz = 0;       
        char buf[BUF_SIZE] = {0};

        memset(rcvbuf, 0, rlen);
        while (1) 
        {
                usleep(1500);
#ifdef DEBUG
                printf("开始读取：%s %d\n", __FILE__, __LINE__);
#endif

                sz = read(sockfd, buf, 1024);

#ifdef DEBUG
                printf("%s\n", buf);
                printf("结束读取：%s %d 长度：%d 字节\n", __FILE__, __LINE__, sz);
#endif

                if (sz < 1024) 
                {
                        strncat(rcvbuf, buf, sz);
                        break;
                }


                httplen += sz;
                if (httplen > rlen) 
                {
#ifdef DEBUG
                        printf("接收缓冲区太小%s %d\n", __FILE__, __LINE__);
#endif
                        break;
                }

                strncat(rcvbuf, buf, sz);

                memset(buf, 0, sizeof(buf));
        }

        return TBU_OK;
}
