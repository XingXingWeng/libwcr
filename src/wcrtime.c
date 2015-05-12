#include "wcrpub.h"
#include "wcrtime.h"


/**************************************************************
 * 功能：获取当前时间，并将其转换为字符串
 *       存储在timestamp中，timestamp
 *       必须为可用内存,精确到秒
 * 参数：
 *      timestamp 存储时间字符串，内存空间要不小于15字节
 *      timezone   时区设置，
 *                      为0是为GMT时间(UTC)
 *                      为8是为东8区时间(北京时间)
 * 返回值：
 *      0   成功
 *      -1  失败
**************************************************************/
int get_time_stamp(char *timestamp, const int timezone)
{
        if (timezone < 0 || timezone > 23) 
        {
                printf("Time Zone Error\n");
                return WCR_ERR;
        }

        //struct tm tmnow = {0};
        struct tm tmnow = {0};
        time_t now;
        time(&now);
        now += timezone * 3600;
        gmtime_r(&now, &tmnow);
        sprintf(timestamp, "%04d%02d%02d%02d%02d%02d",
                        tmnow.tm_year + 1900,
                        tmnow.tm_mon + 1,
                        tmnow.tm_mday,
                        tmnow.tm_hour,
                        tmnow.tm_min,
                        tmnow.tm_sec
               );

        return WCR_OK;
}

/**************************************************************
 * 功能：获取当前时间,精确到秒
 * 参数：
 *      curtime      存储时间结构体
 *      timezone   时区设置，
 *                      为0是为GMT时间(UTC)
 *                      为8是为东8区时间(北京时间)
 * 返回值：
 *      0   成功
 *      -1  失败
**************************************************************/
int get_cur_time(struct tm *curtime, const int timezone)
{
        if (timezone < 0 || timezone > 23) 
        {
                printf("Time Zone Error\n");
                return WCR_ERR;
        }

        struct tm tmnow = {0};
        time_t now;
        time(&now);
        now += timezone * 3600;
        gmtime_r(&now, &tmnow);

        memset(curtime, 0, sizeof(struct tm));
        curtime->tm_year     = tmnow.tm_year + 1900;
        curtime->tm_mon      = tmnow.tm_mon + 1;
        curtime->tm_mday     = tmnow.tm_mday;
        curtime->tm_hour     = tmnow.tm_hour;
        curtime->tm_min      = tmnow.tm_min;
        curtime->tm_sec      = tmnow.tm_sec;

        return WCR_OK;
}


/**************************************************************
 * 功能：显示当前时间,精确到秒
 * 参数：
 *      timezone   时区设置，
 *                      为0是为GMT时间(UTC)
 *                      为8是为东8区时间(北京时间)
 * 返回值：
 *      0   成功
 *      -1  失败
**************************************************************/
int show_cur_time(const int timezone)
{
        if (timezone < 0 || timezone > 23) 
        {
                printf("Time Zone Error\n");
                return WCR_ERR;
        }

        struct tm tmnow = {0};
        time_t now;
        time(&now);
        now += timezone * 3600;
        gmtime_r(&now, &tmnow);
        printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                        tmnow.tm_year + 1900,
                        tmnow.tm_mon + 1,
                        tmnow.tm_mday,
                        tmnow.tm_hour,
                        tmnow.tm_min,
                        tmnow.tm_sec
              );

        return WCR_OK;
}


/**************************************************************
 * 功能：显示当前时间,精确到秒
 * 参数：
 *      curtime   存储时间的字符串
 *      timezone   时区设置，
 *                      为0是为GMT时间(UTC)
 *                      为8是为东8区时间(北京时间)
 * 返回值：
 *      curtime的指针
**************************************************************/
char *get_cur_time_str(char *curtime, const int timezone)
{
        if (timezone < 0 || timezone > 23) 
        {
                printf("Time Zone Error\n");
                return NULL;
        }

        struct tm tmnow = {0};
        time_t now;
        time(&now);
        now += timezone * 3600;
        gmtime_r(&now, &tmnow);
        sprintf(curtime, "%04d-%02d-%02d %02d:%02d:%02d",
                        tmnow.tm_year + 1900,
                        tmnow.tm_mon + 1,
                        tmnow.tm_mday,
                        tmnow.tm_hour,
                        tmnow.tm_min,
                        tmnow.tm_sec
               );

        return curtime;
}

/************************************************************************************************
 * 功能：计算当前时间的前N天或后N天的日期
 * 参数：
 *      date      存储时间字符串
 *      timezone   时区，中国为8
 *      days       前N天或后N天
 *      type        0代表当前时间向前days天，非0代表当前时间向后days天
************************************************************************************************/
char *cal_date(char *date, const int timezone, const int days, const int type)
{
        if (timezone < 0 || timezone > 23) 
        {
                printf("Time Zone Error\n");
                return NULL;
        }

        struct tm tmnow = {0};
        time_t now;
        time(&now);
        now += timezone * 3600;
        if (0 == type) 
        {
                now -= days * 24 * 60 * 60;
        } 
        else 
        {
                now += days * 24 * 60 * 60;
        }

        gmtime_r(&now, &tmnow);
        sprintf(date, "%04d%02d%02d",
                        tmnow.tm_year + 1900,
                        tmnow.tm_mon + 1,
                        tmnow.tm_mday
               );

        return date;
}
