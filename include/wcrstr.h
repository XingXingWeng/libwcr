#ifndef WCRSTR_H
#define WCRSTR_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************
 * 第 3 区
 * 字符处理 相关函数声明
 * 文件：libwlstr.c
********************************/
int replace_char(char *src, const char newchar, const char oldchar);
char *trim_str(char *src);
char *trim_str_all(char *src);
int hex2dec(char *hex);
char *last_str(char *desc, const char *src, const char ch);

#ifdef __cplusplus
}
#endif

#endif
