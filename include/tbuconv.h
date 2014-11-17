#ifndef TBUCONV_H
#define TBUCONV_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************
 * 第 7 区
 * 编码处理 相关函数声明
 * 文件：libwlconv.c
********************************/
int code_convert(const char *src_code, 
                const char *dest_code, 
                char *src, 
                size_t *src_len, 
                char *desc, 
                size_t *dest_len);

int gbk2utf8(char *dest,const char *src,int dest_len);

#ifdef __cplusplus
}
#endif

#endif
