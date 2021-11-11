# hadoop伪分布式安装

简单快速，有利于体验hadoop的各项功能和api练习。当然也可以考虑docker方式，但是docker方式不利于后续的集群安装。

参考https://hadoop.apache.org/docs/stable/hadoop-project-dist/hadoop-common/SingleCluster.html

# 安装前准备

* 关闭防火墙

```shell
systemctl stop firewalld &&\ 
systemctl status firewalld &&\
systemctl disable firewalld
```

看到结果为inactive即可。

* 关闭selinux

```shell
[root@localhost hadoop-3.2.2]# getenforce
Enforcing
     
# 关闭SELinux：
# 1、临时关闭
##setenforce 0 permissive模式, 1 enforcing模式
setenforce 0                  
                             
# 2、修改配置文件
修改/etc/selinux/config 文件
将SELINUX=enforcing改为SELINUX=disabled
```

* 安装jdk

```shell
yum install -y java-1.8.0-openjdk-devel.x86_64
# 验证
[root@localhost hadoop-3.2.2]# java -version
openjdk version "1.8.0_292"
```

* host

```shell
# 增加本机域名解析
vi /etc/hosts

```

# 修改相关配置文件

`etc/hadoop/core-site.xml`:

```
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://node1:9000</value>
    </property>
</configuration>
```

`etc/hadoop/hdfs-site.xml`:

```
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
    <property>
       <name>dfs.webhdfs.enabled</name>
       <value>true</value>
    </property>
</configuration>
```

`etc/hadoop/mapred-site.xml`:

```
<configuration>
    <property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
    <property>
        <name>mapreduce.application.classpath</name>
        <value>$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/*:$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/lib/*</value>
    </property>
</configuration>
```

`etc/hadoop/yarn-site.xml`:

```
<configuration>
    <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
    </property>
    <property>
        <name>yarn.nodemanager.env-whitelist</name>
        <value>JAVA_HOME,HADOOP_COMMON_HOME,HADOOP_HDFS_HOME,HADOOP_CONF_DIR,CLASSPATH_PREPEND_DISTCACHE,HADOOP_YARN_HOME,HADOOP_MAPRED_HOME</value>
    </property>
</configuration>
```

`etc/hadoop/hadoop-env.sh`:

```shell
export JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk
export HDFS_DATANODE_USER=root
export HDFS_DATANODE_SECURE_USER=root
export HDFS_NAMENODE_USER=root
export HDFS_SECONDARYNAMENODE_USER=root

export YARN_RESOURCEMANAGER_USER=root
export YARN_NODEMANAGER_USER=root
```



# 配置ssh免密

```shell
 ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
 cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
 chmod 0600 ~/.ssh/authorized_keys
 
 # 测试
 ssh node1
```

# 配置环境变量

```shell
JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk
HADOOP_HOME=/data/hadoop-3.2.2
PATH=$PATH:$HOME/bin:$JAVA_HOME/bin:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
source .bash_profile
```

# 开始安装

## 格式化namenode

```shell
[root@node1 ~]# hdfs namenode -format
```

## 启动dfs

```shell
[root@node1 hadoop]# start-dfs.sh
```

## 启动yarn

```shell
[root@node1 hadoop]# start-yarn.sh
```

# 端口列表

| 序号 | 服务            | 端口 |
| ---- | --------------- | ---- |
| 1    | hdfs            | 9000 |
| 2    | webHDFS         | 9870 |
| 3    | ResourceManager | 8088 |

