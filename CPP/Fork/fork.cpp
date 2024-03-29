﻿#include<stdio.h>
#include<unistd.h>
int main()
{
	//fork()返回两个值

	//	返回一个大于0的值给父进程
	//	返回0给子进程
	//	返回其他值说明fork失败了
	pid_t pid;
	int count = 0;
	pid = fork();	//fork一个进程
	if (pid == 0) {               //pid为0,
		printf("this is child process, pid is %d\n", getpid());//getpid返回的是当前进程的PID
		count += 2;
		printf("count = %d\n", count);
	}
	else if (pid > 0) {
		printf("this is father process, pid is %d\n", getpid());
		count++;
		printf("count = %d\n", count);
	}
	else {
		fprintf(stderr, "ERROR:fork() failed!\n");
	}
	return 0;
}