#ifndef TBUNET_H
#define TBUNET_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************
 * 第 4 区
 * 网络 相关函数声明
 * 文件：libwlnet.c
********************************/
typedef void (*tcp_client)(int);

char *get_ifconfig(const char *netcard_name, char *ip);

struct netcard_info 
{
        char name[20];
        char ip[20];
        struct netcard_info *next;
};
struct netcard_info *get_local_ip(struct netcard_info **netinfo); 
int free_net_info(struct netcard_info **head);
void show_net_info(struct netcard_info *head);

/* 创建TCP服务器，返回socket */
int create_tcp_server(int port, tcp_client handle_client);
/* 连接TCP服务器，返回socket */
int conn_server(const char *hostname, const int port);
/* 发送数据 */
int tcp_send(int sockfd, char *sendbuf, int slen);
/* 接收数据 */
int tcp_receive(int sockfd, char *rcvbuf, int rlen);



#ifdef __cplusplus
}
#endif

#endif
