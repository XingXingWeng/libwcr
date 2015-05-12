#ifndef WCRTIME_H
#define WCRTIME_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************
 * 第 2 区
 * 时间处理 相关函数声明
 * 文件：libwltime.c
********************************/
int get_time_stamp(char *timestamp, const int timezone);

int get_cur_time(struct tm *curtime, const int timezone);

int show_cur_time(const int timezone);

char *get_cur_time_str(char *curtime, const int timezone);

char *cal_date(char *date, const int timezone, const int days, const int type);


#ifdef __cplusplus
}
#endif

#endif
