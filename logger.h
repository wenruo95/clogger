// logger
#include<stdlib.h>
#include<time.h>

#ifndef LOGGER_H

#define LOGGER_H

//enum loglevel {DEBUG,INFO,WARNING,ERROR,CRITICAL}

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3
#define CRITICAL 4	// 严重错误
#define SYSTEM 5	// 只有开启关闭log使用

static char *loglevel_s[6] = {"debug","info","warning","error","critical","system"};

typedef struct Logger {
	char *name;
	int loglevel;
	unsigned int last_seconds;
	unsigned long int count;	// 当前s数打印第x条
} Logger;

static Logger *logger = NULL;

/*
 * 可被重写
 */
void _print();


// success 0
// error -1
int logger_init(char *name,int loglevel);

// 打印所有等级日志(showall)
int showall();

// 禁止打印日志(banlog)
int banlog();

// success:old-loglevel
// error:-1
int setloglevel(int loglevel);

int getloglevel();

// 打印日志(print log)
//[2018-06-26 17:59:25 000013] => [debug] => content-test
int logger_log(int loglevel,char *path,char *content);


int logger_close();


#endif
