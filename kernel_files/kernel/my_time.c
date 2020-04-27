#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/uaccess.h>

asmlinkage void sys_my_time(struct timespec __user *t) {
	struct timespec tt;
	getnstimeofday(&tt);
	copy_to_user(t, &tt, sizeof(struct timespec));
}
