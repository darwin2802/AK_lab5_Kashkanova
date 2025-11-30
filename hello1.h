#ifndef _HELLO1_H
#define _HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct hello_entry {
  struct list_head list;
  ktime_t timestamp_start;
  ktime_t timestamp_end;
};

void print_hello(void);

#endif
