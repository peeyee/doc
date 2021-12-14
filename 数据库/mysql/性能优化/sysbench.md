# sysbench

sysbench是一款性能测试工具，可以测试数据库的TPC-C基准性能，也可以测试io，内存，cpu等硬件的性能。

## 安装sysbench

```shell
# ubuntu系统
peter@bigdata:~$ sudo apt-get install sysbench
peter@bigdata:~$ man sysbench

# centOS
curl -s https://packagecloud.io/install/repositories/akopytov/sysbench/script.rpm.sh | sudo bash
sudo yum -y install sysbench
```

> SYSBENCH(1)                                           Benchmark tool for database systems                                          SYSBENCH(1)
>
> NAME
>        sysbench - multi-threaded benchmark tool for database systems
>
> SYNOPSIS
>        sysbench [common-options] --test=name [test-options] <command>
>
>        Commands: prepare run cleanup help version

## cpu

该测试用寻找素数来测试cpu性能。

```shell
peter@bigdata:~$ cat /proc/cpuinfo

peter@bigdata:~$ sysbench --test=cpu --cpu-max-prime=2000 run
WARNING: the --test option is deprecated. You can pass a script name or path on the command line without any options.
sysbench 1.0.11 (using system LuaJIT 2.1.0-beta3)

Running the test with following options:
Number of threads: 1
Initializing random number generator from current time


Prime numbers limit: 2000

Initializing worker threads...

Threads started!

CPU speed:
    events per second: 12909.63

General statistics:
    total time:                          10.0001s
    total number of events:              129113

Latency (ms):
         min:                                  0.07
         avg:                                  0.08
         max:                                  0.54
         95th percentile:                      0.08
         sum:                               9981.41

Threads fairness:
    events (avg/stddev):           129113.0000/0.00
    execution time (avg/stddev):   9.9814/0.00

```



## 磁盘IO

对普通的机械硬盘进行一些io测试，包括顺序和随机的读写。

```shell
# 准备20G文件，文件要比内存大 
peter@bigdata:~$ sysbench --test=fileio --file-total-size=20G prepare

# 笔记本SSD随机读写测试
peter@bigdata:/data$ sysbench --test=fileio --file-total-size=20G --file-test-mode=rndrw --max-time=60 run
Threads started!


File operations:
    reads/s:                      2061.79
    writes/s:                     1374.53
    fsyncs/s:                     4397.40

Throughput:
    read, MiB/s:                  32.22（1027.76顺序读写）
    written, MiB/s:               21.48

General statistics:
    total time:                          60.0003s
    total number of events:              470071

Latency (ms):
         min:                                  0.00
         avg:                                  0.13
         max:                                  9.63
         95th percentile:                      0.33
         sum:                              59312.27

Threads fairness:
    events (avg/stddev):           470071.0000/0.00
    execution time (avg/stddev):   59.3123/0.00
```

## OLTP

测试下数据TPC-C的基准性能。

```shell
# 准备数据，数据库需要事先创建好
sysbench --mysql-host=172.16.8.67 \
					--mysql-port=3308 \
					--mysql-user=root \
					--mysql-password=root \
					/usr/share/sysbench/oltp_read_write.lua \
					--table-size=1000000 \
					--db-driver=mysql \
					--mysql-db=test prepare

# 开始测试
peter@bigdata:/data$ sysbench --mysql-host=172.16.8.67 --mysql-port=3308 --mysql-user=root --mysql-password=root /usr/share/sysbench/oltp_read_write.lua --table-size=1000000 --db-driver=mysql --mysql-db=test --threads=8 --time=60 run
sysbench 1.0.11 (using system LuaJIT 2.1.0-beta3)

Running the test with following options:
Number of threads: 8
Initializing random number generator from current time


Initializing worker threads...

Threads started!

SQL statistics:
    queries performed:
        read:                            130256
        write:                           37216
        other:                           18608
        total:                           186080
    transactions:                        9304   (154.96 per sec.)
    queries:                             186080 (3099.16 per sec.)
    ignored errors:                      0      (0.00 per sec.)
    reconnects:                          0      (0.00 per sec.)

General statistics:
    total time:                          60.0368s
    total number of events:              9304

Latency (ms):
         min:                                 31.20
         avg:                                 51.60
         max:                                526.74
         95th percentile:                     66.84
         sum:                             480112.12

Threads fairness:
    events (avg/stddev):           1163.0000/6.42
    execution time (avg/stddev):   60.0140/0.01					
```

