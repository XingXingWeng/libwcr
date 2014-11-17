#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tbupub.h"
#include "tbustr.h"
#include "tbulog.h"

//static FILE *logfd = NULL;
static int logfd = -1;
#define BUF_SIZE 1024

char *get_exec_name(pid_t pid, char *name);

/*
 * 打开日志文件
 */ 
int open_log(const char *path)
{
        logfd = open(path, O_WRONLY | O_APPEND | O_CREAT, 00644);
        return logfd >= 0 ? TRUE : FALSE;
}

/*
 * 关闭日志文件
 */ 
int close_log()
{
        int flag;
        fsync(logfd);
        flag = close(logfd);
        logfd = -1;
        return (0 == flag) ? TRUE : FALSE;
}

/*
 * 写入一条日志
 */ 
int add_log(const char *format, ...)
{
        /* 1.定义参数列表 */
        va_list ap;

        int     i;
        char    c;
        char    *s;
        float   f;
        time_t  now;

        char    hostname[30] = {0};
        char    execname[100] = {0};
        char    buf[BUF_SIZE] = {0};
        char    key[100] = {0};

        /* 取得当前时间 */
        time(&now);
        /* 东8区时间 */
        //now += 8 * 3600;

        /* 获取主机名 */
        gethostname(hostname, sizeof(hostname));
        pid_t pid = getpid();
        get_exec_name(pid, execname);
        last_str(key, execname, '/');

        sprintf(buf, "%s %s %s[%d]: ", trim_str(ctime(&now)) + 4, hostname, key, pid);

        /* 2.初始化参数列表 */
        va_start(ap, format);

        while (*format) 
        {
                if (*format != '%') 
                {
                        strncat(buf, format, 1);
                        format++;
                        continue;
                }

                format++;
                if (*format == '\0') 
                {
                        buf[strlen(buf)] = '\n';
                        break;
                }

                switch (*format) 
                {
                case '%':
                        buf[strlen(buf)] = '%';
                        break;
                case 'c':
                        c = (char)va_arg(ap, int);
                        //fprintf(logfd, "%c", c);
                        strncat(buf, &c, 1);
                        break;
                case 'd':
                        i = va_arg(ap, int);
                        sprintf(key, "%d", i);
                        strncat(buf, key, strlen(key));
                        break;
                case 's':
                        s = va_arg(ap, char *);
                        sprintf(key, "%s", s);
                        strncat(buf, key, strlen(key));
                        break;
                case 'f':
                        f = (float)va_arg(ap, double);
                        sprintf(key, "%f", f);
                        strncat(buf, key, strlen(key));
                        break;
                }

                format++;
        }

        /* .关闭参数列表 */
        va_end(ap);


        /* 如果文件末尾不是\n，则在最后加入\n */
        if (buf[strlen(buf) - 1] != '\n')
                buf[strlen(buf)] = '\n';

        write(logfd, buf, strlen(buf));
        fsync(logfd);
        
        return TBU_OK;
}

char *get_exec_name(pid_t pid, char *name)
{
        char    cmd[50] = {0};
        FILE    *fd = NULL;

        sprintf(cmd, "readlink /proc/%d/exe", pid);

        fd = popen(cmd, "r");
        if (NULL == fd) 
        {
                //assert(0);
                return NULL;
        }
        fscanf(fd, "%s", name);
        pclose(fd);
        fd = NULL;

        return name;
}
