# io系统

io，输入输出设备，在linux中，io通常指磁盘io，传统的机械硬盘，使用磁臂，磁头加柱面的方式，读写速度在10ms左右，是计算机系统中较慢的组件。

## io监控

### iostat

iostat可以监控磁盘的使用情况，包括读写速率，请求情况。

```shell
# 每隔1秒监控下磁盘读写性能
iostat -m -x -d 1 10
Device:         rrqm/s   wrqm/s     r/s     w/s    rMB/s    wMB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
vda               0.00     0.01    0.00    0.08     0.00     0.01   333.99     0.00   30.15   11.10   31.08   0.37   0.00
vdb               0.16     1.07  168.69   18.74     2.64     0.33    32.48     0.18    1.02    0.39    6.68   0.09   1.69
```

await：io请求平均等待时间，通常应该在5ms左右。

%util：磁盘使用率。

性能分析：%util接近100，说明磁盘负载满。

### iotop

iotop查看进程/线程使用io的明细情况。

```shell
Total DISK READ :       0.00 B/s | Total DISK WRITE :       0.00 B/s
Actual DISK READ:       0.00 B/s | Actual DISK WRITE:       9.97 K/s
  TID  PRIO  USER     DISK READ  DISK WRITE  SWAPIN     IO>    COMMAND                                                               
 9735 be/4 mysql       0.00 B/s    0.00 B/s  0.00 %  0.00 % mysqld --basedir=/usr/local/mysql -...
```

IO>：该进程占用磁盘的百分比。

### lsof

lsof，list open files，是一个强大的文件系统监控命令。由于unix奉行**一切皆文件**，所以使用lsof几乎可以监控linux的所有内容。

```shell
# 列出网络端口
[root@mysql-master ~]#  lsof -i|head -n 2
COMMAND     PID   USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
chronyd     879 chrony    5u  IPv4   24532      0t0  UDP localhost:323

# 列出进程9098打开的文件
[root@mysql-master ~]# lsof -p 9098
COMMAND    PID USER   FD   TYPE DEVICE  SIZE/OFF      NODE NAME
mysqld_sa 9098 root  cwd    DIR  253,2       129 134322670 /usr/local/mysql-5.7.33
mysqld_sa 9098 root  rtd    DIR  253,2       250        64 /
mysqld_sa 9098 root  txt    REG  253,2    964536 201328707 /usr/bin/bash
```

### 总结

通过 iostat -> iotop -> lsof 的分析链，可以从整体到局部的排查出系统的io故障问题。

