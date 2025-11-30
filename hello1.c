#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/printk.h> 
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darina");
MODULE_DESCRIPTION("Laba 5: Base module (List and Export)");
MODULE_VERSION("1.0");

static LIST_HEAD(hello_list_head);

void print_hello(void)
{
  struct hello_entry *new_entry;
  ktime_t start_time;

  start_time = ktime_get();

  pr_info("hello: Hello, world!\n");

  new_entry = kmalloc(sizeof(*new_entry), GFP_KERNEL);
  if (!new_entry) {
    pr_err("hello1: Failed to allocate memory for list entry.\n");
    return;
  }

  new_entry->timestamp_start = start_time;
  new_entry->timestamp_end = ktime_get();
  list_add_tail(&new_entry->list, &hello_list_head);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
  pr_info("hello1: Base module loaded. Exporting print_hello.\n");
  return 0;
}

static void __exit hello1_exit(void)
{
  struct hello_entry *entry, *next;
  int count = 0;
  long long duration_ns;

  pr_info("hello1: Module unloading. Printing recorded durations:\n");

  list_for_each_entry_safe(entry, next, &hello_list_head, list) {
    duration_ns = ktime_to_ns(ktime_sub(entry->timestamp_end, entry->timestamp_start));

    pr_info("hello1: Event %d: Duration = %lld ns (Start: %lld, End: %lld)\n",
      ++count, duration_ns, ktime_to_ns(entry->timestamp_start), ktime_to_ns(entry->timestamp_end));

    list_del(&entry->list);
    kfree(entry);
  }

  pr_info("hello1: Module unloaded. Total %d entries processed.\n", count);
}

module_init(hello1_init);
module_exit(hello1_exit);
