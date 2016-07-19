#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>	/* Needed for the macros */

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

#define IOCTL_SET_AGE	1001
#define IOCTL_GET_AGE	1002

int age = 30;
module_param(age, int, 0);

static char *name = "cafer";
module_param(name, charp, 0);

static int hello_proc_show(struct seq_file *m, void *v) {
  seq_printf(m, "Hello proc! age=%d name=%s\n", age, name);
  return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, hello_proc_show, NULL);
}

long hello_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	switch (ioctl_num) {
	case IOCTL_SET_AGE:
		copy_from_user(&age, (int *)ioctl_param, sizeof(int));
		break;
	case IOCTL_GET_AGE:
		copy_to_user((int *)ioctl_param, &age, sizeof(int));
		break;
	}
	return 0;
}

static const struct file_operations hello_proc_fops = {
  .owner = THIS_MODULE,
  .open = hello_proc_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
  .unlocked_ioctl = hello_ioctl,
};

static int __init hello_proc_init(void) {
  proc_create("hello_proc", 0, NULL, &hello_proc_fops);
  return 0;
}

static void __exit hello_proc_exit(void) {
  remove_proc_entry("hello_proc", NULL);
}

module_init(hello_proc_init);
module_exit(hello_proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bilal Hatipoglu");	/* Who wrote this module? */
MODULE_DESCRIPTION("Hello world module!");	/* What does this module do */
