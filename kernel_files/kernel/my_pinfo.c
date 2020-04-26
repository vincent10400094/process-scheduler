#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_my_pinfo(int pid, unsigned long start_sec, unsigned long start_nsec, unsigned long end_sec, unsigned long end_nsec) {
	printk(KERN_INFO "[Project 1] %d %lu.%09lu %lu.%09lu\n", pid, start_sec, start_nsec, end_sec, end_nsec);
}
