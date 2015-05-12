#ifndef WCRCONFIG_H
#define TUBCONFIG_H

#include "wcrstr.h"

#define KEYVALUE_SIZE 128
struct key_value_st 
{
    char    key[KEYVALUE_SIZE];
    char    value[KEYVALUE_SIZE];
    //struct key_value_st *pLNode;
    //struct key_value_st *pRNode;
    struct key_value_st *next;
};


#ifdef __cplusplus
extern "C" {
#endif

/********************************
 * 第 8 区
 * UNIX风格配置文件处理 相关函数声明
 * 文件：libwlcnf.c
********************************/

struct key_value_st *read_local_conf(const char *filename);
int free_key_value(struct key_value_st *head);
char *find_value(struct key_value_st *head, char *szValue, const char *szKey);
/***************************************************************
使用示例:

int main(int argc, char **argv)
{
    char szValue[1024] = {0};
    1. 读取配置文件,生成键值对字典
    key_value_st *head = read_local_conf("aaa.txt");
    key_value_st *p = head;
    while(p != NULL)
    {
        printf("%s:%s\n", p->szKey, p->szValue);
        p = p->pNext;
    }

    2. 查找配置文件中的键所对应的值
    printf("找到值： %d\n", atoi(find_value(head, szValue, "wang")));
    printf("找到值： %s\n", find_value(head, szValue, "ip"));


    3. 释放内存
    free_key_value(head);
    return 0;
}
***************************************************************/


#ifdef __cplusplus
}
#endif

#endif
