#include<stdio.h>

#include "logger.h"

void _print(char *str) {
}

int logger_init(char *name,int loglevel) {
	logger = (Logger *) malloc(sizeof(Logger));
	if (logger == NULL) {
		printf("failed to allocate memory");
		exit(1);
	}
	logger->name = name;
	logger->loglevel = loglevel;
	logger->count = 0;
	time_t now;
	time(&now);
	struct tm beg = *localtime(&now);
	logger->last_seconds = mktime(&beg);

	printf("init");
	logger_log(SYSTEM,"logger","op=init");
	return 0;
}

int banlog() {
	return setloglevel(SYSTEM);
}

int showall() {
	return setloglevel(DEBUG);
}

int setloglevel(int loglevel) {
	int oldlevel = logger->loglevel;
	if (loglevel == oldlevel) {
		return oldlevel;
	}
	char str[100];
	sprintf(str,"op=changelevel:%s==>%s",loglevel_s[oldlevel],loglevel_s[loglevel]);
	logger_log(SYSTEM,"logger",str);
	logger->loglevel = loglevel;
	return oldlevel;
}

int logger_log(int loglevel,char *path,char *content) {
	if (loglevel < logger->loglevel) {
		return 0;
	}

	time_t now;
	time(&now);
	struct tm beg = *localtime(&now);
	int now_seconds = mktime(&beg);
	if (now_seconds != logger->last_seconds) {
		logger->count = 1;
		logger->last_seconds = now_seconds;
	} else {
		logger->count = logger->count + 1;
	}
	int year = 1900 + beg.tm_year;
	int month = 1 + beg.tm_mon;
	int day = beg.tm_mday;
	char filename[256],logdate[20],logcontent[4096];
	// path2018-06-26.log
	if (loglevel != SYSTEM) {
		sprintf(filename,"%s%04d-%02d-%02d.log",path,year,month,day);
	} else {
		sprintf(filename,"%s.log",path);
	}
	FILE *pfile = NULL;
	if (!(pfile = fopen(filename,"a"))) {
		printf("failed to append log");
		exit(1);
	}
	sprintf(logdate,"%04d-%02d-%02d",year,month,day);
	sprintf(logcontent,"[%s %s %06ld] [%s] %s\n",logdate,__TIME__,logger->count,loglevel_s[loglevel],content);

	fputs(logcontent,pfile);

	printf("filename:%s==>%s\n",filename,logcontent);
	fclose(pfile);
	return logger->count;
}

int logger_close() {
	logger_log(SYSTEM,"logger","op=close");
	free(logger);
	logger= NULL;

}

