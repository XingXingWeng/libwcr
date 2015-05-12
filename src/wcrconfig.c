/********************************************************
 * File Name    : wcrconfig.c
 * Author       : wanglu
 * Create Date  : 2013-12-19
 * Copyright    : 2012-2013
********************************************************/

#include "wcrpub.h"
#include "wcrconfig.h"

/***********************************************
 * unix配置文件读取
 * # 开头为注释
 * = 开头和结尾为错误配置，将忽略
***********************************************/
int parse_key_value(struct key_value_st *kv, const char *szPram);

struct key_value_st *read_local_conf(const char *filename)
{

        char    str[1024] = {0};
        int     ch;
        struct key_value_st stKeyValue;//存储
        struct key_value_st *p = &stKeyValue;

        if (NULL == filename || '\0' == *filename)
                return NULL;


        //打开配置文件
        FILE* fs = fopen(filename, "r");
        if (NULL == fs) 
        {
                perror("fopen");
                return NULL;
        }
        //逐行读取配置文件
        while (1) 
        {
                fgets(str, 1024, fs);
                //将末尾的'\n'换成'\0'
                str[strlen(str) - 1] = '\0';
                /* 去年str中所有的空格 */
                trim_str_all(str);

                if ( *str != '\0') 
                {
                        p->next = (struct key_value_st *)malloc(sizeof(struct key_value_st));
                        memset(p->next, 0, sizeof(stKeyValue));
                        if (parse_key_value(p->next, str) == 0) 
                        {
                                p = p->next;
                                p->next = NULL;
                                //printf("%s:%s\n", p->key, p->szValue);
                        } 
                        else 
                        {
                                free(p->next);
                                p->next = NULL;
                        }
                }
                //////////////////////
                memset(str, 0, sizeof(str));

                ch = fgetc(fs);
                if (EOF == ch)
                        break;

                ungetc(ch, fs);
        }

        fclose(fs);
        return (&stKeyValue)->next;
}

//解析一行参数，提取key,value到结构体中
int parse_key_value(struct key_value_st *kv, const char *szPram)
{
        int     iStrLen = 0;
        char    *szTemp = NULL;
        char    *pTemp = NULL;
        char    szKey[64] = {0};
        char    szValue[64] = {0};

        int     i;

        if (NULL == szPram ||'\0' == *szPram || NULL == kv)
                return WCR_ERR;

        iStrLen = strlen(szPram);
        szTemp = (char*)malloc(iStrLen + 1);//堆中申请内存
        memset(szTemp, 0, iStrLen + 1);
        strncpy(szTemp, szPram, iStrLen);

        //如果字符串开头为#，是注释，不解析
        if ('#' == *szTemp) 
                return WCR_ERR;
        //如果字符串开头为=，配置不正确，不解析
        if ('=' == *szTemp) 
                return WCR_ERR;
        //如果字符串结尾为=，配置不正确，不解析
        if ('=' == *(szTemp + iStrLen - 1)) 
                return WCR_ERR;
        //如果字符串中没有=，配置不正确，不解析
        pTemp = szTemp;
        while ('\0' != *pTemp) 
        {
                if ('=' == *pTemp)
                        break;

                pTemp++;
        }
        if ('\0' == *pTemp) 
                return WCR_ERR;

        //配置正确，开始解析
        pTemp = szTemp;
        i = 0;
        //复制=号前的字符串到szKey
        while ('=' != *pTemp) 
        {
                szKey[i] = *pTemp;
                i++;
                pTemp++;
        }
        pTemp++;
        //复制=号后的字符串到szValue
        strcpy(szValue, pTemp);
        free(szTemp);

        //复制数据
        //kv->next = NULL;
        strcpy(kv->key, szKey);
        strcpy(kv->value, szValue);

        return WCR_OK;
}

//释放创建链表时申请的内存
int free_key_value(struct key_value_st *head)
{
        struct key_value_st *pTemp = NULL;
        while (head != NULL) 
        {
                pTemp = head;
                head = head->next;
                free(pTemp);
        }
        return WCR_OK;
}

//通过key查找value值,后面的值会覆盖前面的值
char* find_value(struct key_value_st *head, char* szValue, const char *szKey)
{
        if (NULL == szKey || NULL == szValue || NULL == head)
                return NULL;

        while (head != NULL) 
        {
                if (strcmp(head->key, szKey) == 0)
                        strcpy(szValue, head->value);

                head = head->next;
        }
        return szValue;
}
