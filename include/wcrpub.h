#ifndef WCRPUB_H
#define WCRPUB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

/*
 * 定义C中的“布尔”类型
 */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 1
#endif

/*
 * 定义错误与返回结果类型
 */
#define WCR_OK          0   //正常
#define WCR_ERR         -1  //错误

#define WCR_EQ          0   //相等
#define WCR_GT          1   //大于
#define WCR_LT          -1  //小于



#endif
