#include<stdio.h>
#include<unistd.h>

#include "logger.h"

int main() {
	logger_init("test",0);
	int count = 1;
	unsigned int seconds = 1;

	while(count++ < 10) {
		setloglevel(DEBUG);
		logger_log(ERROR,"logger","op=test1");
		logger_log(INFO,"logger","op=test2");
		logger_log(WARNING,"logger","op=test3");
		logger_log(CRITICAL,"logger","op=test4");
		// 测试loglevel.count计数功能
		sleep(seconds);
		setloglevel(CRITICAL);
		logger_log(ERROR,"logger","op=test5");
		logger_log(INFO,"logger","op=test6");
		logger_log(WARNING,"logger","op=test7");
		logger_log(CRITICAL,"logger","op=test8");
	}

	logger_close();

	return 0;
}
