#include <stdio.h>
#include "libwcr.h"

int main()
{
        struct netcard_info *info = NULL;
        struct netcard_info *p = NULL;
        char str[] = "fuck";

        get_local_ip(&info);
        p = info;
        show_net_info(p);
        open_log("a.log");
        while (p != NULL) {
                add_log("%s\n", p->ip);
                p = p->next;
        }

        add_log("i have a dream %d\n", 1997);
        add_log("%s\n", str);
        add_log("if you had one shot.\n");

        free_net_info(&info);
        close_log();
        show_cur_time(8);
        return 0;
}
