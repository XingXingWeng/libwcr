#include "tbupub.h"
#include "tbuconv.h"

#include <stdint.h>
#include <locale.h>
#include "iconv.h"


/*********************************************************************************************************
    * 功能：转换字符编码
    * 参数：
    *   src_code   - 原始编码,如:GBK,UTF8
    *   dest_code     - 要转换到的编码
    *   src      - 要转换的字符串
    *   src_len      - 要转换的字符串长度
    *   desc     - 转换后输出字符串,长度建议设置为src的2倍
    *   dest_len     - 转换后输出字符串长度
    * 返回值：
    *   0   成功
    *   -1  失败
*********************************************************************************************************/
int code_convert(const char *src_code, 
                const char *dest_code, 
                char *src, 
                size_t *src_len, 
                char *desc, 
                size_t *dest_len)
{
        int result = 0;
        char **p_src  = &src;
        char **p_dest = &desc;

        //打开字符集转换
        iconv_t codec = iconv_open(dest_code, src_code);
        if ((iconv_t)-1 == codec)
                return TBU_ERR;

        //开始转换
        result = iconv(codec, p_src, src_len, p_dest, dest_len);
        *p_dest = '\0';
        //关闭字符集转换
        iconv_close(codec);
        return result;
}


/******************************************************************************
 * FUNCTION: gbk2utf8
 * DESCRIPTION: 实现由gbk编码到utf8编码的转换 
 * 
 * Input: dest,转换后的字符串;  src,待转换的字符串; dest_len, dest的最
            大长度
 * Output: dest
 * Returns: -1,fail;>0,success
 * 
 * modification history
 * --------------------
 *  2011-nov-25, lvhongya written
 * --------------------
 ******************************************************************************/
int gbk2utf8(char *dest, const char *src, int dest_len)
{
        if (NULL == src) 
        {
                printf("Bad Parameter\n");
                return TBU_ERR;
        }

        //首先先将gbk编码转换为unicode编码
        if (NULL == setlocale(LC_ALL, "zh_CN.gbk")) 
        {        //设置转换为unicode前的码,当前为gbk编码
                printf("Bad Parameter\n");
                return TBU_ERR;
        }

        int unicodeLen = mbstowcs(NULL, src, 0);//计算转换后的长度
        if (unicodeLen <= 0) 
        {
                printf("Can not Transfer!!!\n");
                return TBU_ERR;
        }
        wchar_t *unicodeStr = (wchar_t *)calloc(sizeof(wchar_t), unicodeLen + 1);
        mbstowcs(unicodeStr, src, strlen(src));//将gbk转换为unicode

        //将unicode编码转换为utf8编码
        //if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))//设置unicode转换后的码,当前为utf8
        if (NULL == setlocale(LC_ALL, "en_US.utf8")) 
        {    //设置unicode转换后的码,当前为utf8
                printf("Bad Parameter\n");
                return TBU_ERR;
        }

        int utfLen = wcstombs(NULL, unicodeStr, 0);//计算转换后的长度

        if (utfLen <= 0) 
        {
                printf("Can not Transfer!!!\n");
                return TBU_ERR;
        } 
        else if (utfLen >= dest_len) 
        {        //判断空间是否足够
                printf("Dst Str memory not enough\n");
                return TBU_ERR;
        }

        wcstombs(dest, unicodeStr, utfLen);
        dest[utfLen] = 0;//添加结束符
        free(unicodeStr);
        return utfLen;
}
