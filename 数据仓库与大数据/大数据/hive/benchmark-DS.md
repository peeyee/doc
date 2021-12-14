#  环境准备

找一台安装hive的linux机器，hive-testbench必须在hive的安装机器上运行。

# 安装benchmark工具

1. 下载github

   从GitHub官网clone hive-testbench源码，Git地址如下：

```shell
[root@ip-172-31-16-68 ~]# git clone https://github.com/hortonworks/hive-testbench.git
```

2. 安装编译环境

如果已有，跳过。

```shell
[root@ip-172-31-16-68 ~]# yum -y install gcc gcc-c++
```

3. 编译hive-testbench

```shell
[root@ip-172-31-16-68 hive-testbench]# ./tpcds-build.sh 
```

4. 生成测试数据

```shell
[root@ip-172-31-16-68 hive-testbench]# ./tpcds-setup.sh 10 /extwarehouse/tpcds
```

其中第一个参数是数据量，10表示10GB，第二参数是hdfs的路径。

# Q&A

* setup.sh中途失败

根据日志，分析setup.sh，手动执行相关hivesql。

# 参考资料

Fayson的github：https://github.com/fayson/cdhproject
