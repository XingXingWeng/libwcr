#include "tbupub.h"
#include "tbustr.h"


#define STR_BUFFER_SIZE 1024

/*****************************************************************************
 * 功能：将src中的字符oldchar替换为newchar
 * 参数：
 *      src   需要处理的字符串
 *      oldchar    需要替换的字符
 *      newchar    替换成的新字符
 * 返回值：
 *      0   成功
 *      -1  失败
*****************************************************************************/
int replace_char(char *src, const char newchar, const char oldchar)
{
        if (src == NULL) 
        {
                printf("[libwl]:%s %d replace_char:src is NULL.\n", __FILE__, __LINE__);
                return TBU_ERR;
        }

        char *temp = src;
        while (*temp != '\0') 
        {
                if (*temp == oldchar)
                        *temp = newchar; 
                temp++;
        }

        return TBU_OK;
}


/**********************************************************
 * 功能：去掉字符串前后的空白
 * 参数：
 *      src   需要处理的字符串,同时用来存储处理后的结果
 * 返回值：
 *      返回处理后的src的首地址
**********************************************************/
char *trim_str(char *src)
{
        int     len;
        int     index;
        char    *temp;
        char    *str;

        len = strlen(src);

        if (NULL == src || 0 == len)
                return src;

        /* 去年左边的空格 */
        temp = (char *)malloc(len + 1);
        str = temp;

        memset(temp, 0, len + 1);
        memcpy(temp, src, len);

        while (' '  == *str || '\n' == *str || '\t' == *str || '\r' == *str)
                str++;

        memset(src, 0, len);
        strncpy(src, str, strlen(str));
        free(temp);

        /* 去年右边的空格 */
        index = strlen(src) - 1;

        while (' '  == *(src + index)
                        || '\n' == *(src + index)
                        || '\t' == *(src + index)
                        || '\r' == *(src + index)) 
        {

                index--;
        }
        *(src + index + 1) = '\0';

        return src;
}

/**********************************************************
 * 功能：去掉字符串前后及中间的空白
 * 参数：
 *      src   需要处理的字符串,同时用来存储处理后的结果
 * 返回值：
 *      返回处理后的src的首地址
**********************************************************/
char *trim_str_all(char *src)
{
        int     len;
        char    *temp;
        int     i = 0;
        int     j = 0;

        len = strlen(src);

        if (NULL == src || 0 == len)
                return src;

        temp = (char *)malloc(len + 1);

        for (i = 0, j = 0; '\0' != *(src + i); i++, j++) 
        {
                //跳过空白
                while(' '  == *(src + i)
                       || '\n' == *(src + i)
                       || '\t' == *(src + i)
                       || '\r' == *(src + i))
                {
                        i++;
                }

                *(temp + j) = *(src + i);
        }
        *(temp + j) = '\0';
        strcpy(src, temp);

        return src;
}

/*
 * 将单个十六进制字符转化为相应的十进制数
 */
int c2i(char ch) 
{
        int num;

        if (isdigit(ch)) 
        {
                num = ch - 48; 
        } 
        else if (isalpha(ch)) 
        {
                if (ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z')
                        num = -1;
                else
                        num = (isupper(ch) ? ch - 55 : ch - 87); 
        } 
        else 
        {
                num = -1;
        }

        return num; 
}

/*
 * 功能：将十六进制字符串转换为整型(int)数值
 * */
int hex2dec(char *hex)
{
        int len;
        int num = 0;
        int temp;
        int bits;
        int i;

        len = strlen(hex);

        for (i = 0, temp = 0; i < len; i++, temp = 0) 
        {   
                temp = c2i( *(hex + i) );
                bits = (len - i - 1) * 4;
                temp = temp << bits;
                num = num | temp;
        }   
        return num;
}

/*
 * 获取指定分隔符最后的字符串
 */
char *last_str(char *desc, const char *src, const char ch)
{
        int index;
        if (NULL == desc || NULL == src) 
        {
                assert(0);
                return NULL;
        }

        index = strlen(src) - 1;
        while (ch != *(src + index))
                index--;

        strcpy(desc, src + index + 1);
        return desc;
}
