# 配置文件

默认位置是/etc/my.cnf.

```shell
[mysqld]
# 设置最大连接数
max-connections = 300
# 设置时区
default-time_zone='+8:00'

# 设置data-cache，影响效率的最大因素之一
# 运行时设置 4G 一般设置为服务器内存的50%
# set global @@innodb_buffer_pool_size = 4294967296
innodb_buffer_pool_chunk_size=4294967296

# 设置错误日志
log-error=/var/lib/mysql/error.log

# 关闭binlog
skip-log-bin 
```

