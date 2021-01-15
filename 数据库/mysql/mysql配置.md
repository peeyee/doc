# 配置文件

不同的系统下位置不同，首先确认下读取配置文件的顺序。

```shell
[root@tiflash1 ~]# mysqld --verbose --help|grep -A 1 'Default options'
Default options are read from the following files in the given order:
/etc/my.cnf /etc/mysql/my.cnf /usr/etc/my.cnf ~/.my.cnf 
```

在Centos下，默认位置是/etc/my.cnf。一般只设置【mysqld】下的这一段服务器配置，一定要确保放对位置，否认配置不生效。

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

# 设置sql_mode
sql_mode=STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
```



## 调优配置

调优配置，尤其是一些和IO，内存相关的配置项，可以提升服务器读写性能，当然这要配合基准测试来验证。以下是一个例子：

### before tuning

redo 日志的大小将极大地影响事务的性能，如果设置的过小，将频繁的刷脏，而带来大量的随机IO。当前是48M，2组，服务器的tps是160。

```sql
show  variables like '%innodb_log_file%';
```

| Variable_name             | Value    |
| :------------------------ | -------- |
| innodb_log_file_size      | 50331648 |
| innodb_log_files_in_group | 2        |

```sql
SQL statistics:
    queries performed:
        read:                            134820
        write:                           38520
        other:                           19260
        total:                           192600
    transactions:                        9630   (160.30 per sec.)
    queries:                             192600 (3206.00 per sec.)
    ignored errors:                      0      (0.00 per sec.)
    reconnects:                          0      (0.00 per sec.)
```

### tuning system variable

innodb_log_file_size这是一个全局的非动态变量，这意味着需要修改配置文件，并重启服务器。

```shell
# 设置redo日志的大小
innodb_log_file_size=1073741824

# 重启之后验证下文件
[root@localhost mysql8]# ll -h ib_logfile*
-rw-r----- 1 polkitd input 1.0G 1月  14 11:19 ib_logfile0
-rw-r----- 1 polkitd input 1.0G 1月  14 11:19 ib_logfile
```

### after tuning

```shell
SQL statistics:
    queries performed:
        read:                            134946
        write:                           38556
        other:                           19278
        total:                           192780
    transactions:                        9639   (160.54 per sec.)
    queries:                             192780 (3210.81 per sec.)
    ignored errors:                      0      (0.00 per sec.)
    reconnects:                          0      (0.00 per sec.)
```

调整之后，tps没有提升，具体原因待查。大致看了下sysbench里的OLTP benchmark测试是读多写少的，可能对于redo日志的要求不是很大。