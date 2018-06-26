# 日志系统

# 编译

log和系统函数重复

	gcc logger.c -fno-builtin


# 函数调用

方法:logger.log(loglevel,path,content)

如logger.log(DEBUG,"/home/linkzw/test","content-test")

output:

[2018-06-26 17:59:25 000013] => [debug] => content-test
