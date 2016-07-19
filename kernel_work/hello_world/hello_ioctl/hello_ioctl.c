#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>		/* ioctl */

#define IOCTL_SET_AGE	1001
#define IOCTL_GET_AGE	1002

void ioctl_set_age(int file_desc, int age)
{
	int ret_val;

	ret_val = ioctl(file_desc, IOCTL_SET_AGE, &age);

	if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
}

void ioctl_get_age(int file_desc)
{
	int ret_val;
	int age;

	ret_val = ioctl(file_desc, IOCTL_GET_AGE, &age);

	if (ret_val < 0) {
		printf("ioctl_get_msg failed:%d\n", ret_val);
		exit(-1);
	}

	printf("get_age:%d\n", age);
}

int main(int argc, char *argv[])
{
	int file_desc, ret_val;
	int age = 99;

	file_desc = open("/proc/hello_proc", 0);
	if (file_desc < 0) {
		printf("Can't open device file\n");
		exit(-1);
	}

	ioctl_set_age(file_desc, age);
	ioctl_get_age(file_desc);

	close(file_desc);
	
	return 0;
}

