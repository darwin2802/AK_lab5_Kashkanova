#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/printk.h> 
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darina");
MODULE_DESCRIPTION("Laba 5: Caller module (Parameters)");
MODULE_VERSION("1.0");

extern void print_hello(void);

static unsigned int print_count = 1;
module_param(print_count, uint, 0644);
MODULE_PARM_DESC(print_count, "The number of times print_hello should be called (default: 1, max: 10)");

static int __init hello2_init(void)
{
  int i;
  pr_info("hello2: Caller module loaded. Call count: %u\n", print_count);
  
  if (print_count > 10) {
    pr_err("hello2: Call count is too high (%u). Max allowed is 10. Aborting.\n", print_count);
    return -EINVAL;
  }

  if (print_count == 0 || (print_count > 4 && print_count < 11))
    pr_warn("hello2: Call count is 0 or between 5 and 10. Warning issued.\n");

  for (i = 0; i < print_count; i++) {
    print_hello();
  }

  return 0;
}

static void __exit hello2_exit(void)
{
  pr_info("hello2: Caller module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
