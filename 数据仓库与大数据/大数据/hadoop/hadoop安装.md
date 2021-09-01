# 安装hadoop

hadoop是一个分布式的计算，存储框架，用于解决TB级的数据计算问题。安装hadoop需要相关背景知识：

* linux：精通shell
* java ：精通java，jvm
* 分布式原理



# 安装前准备

参考文档:

http://hadoop.apache.org/docs/r1.0.4/cn/cluster_setup.html

https://cloud.tencent.com/developer/article/1676789

## 安装jdk1.8

```shell
[root@pminfo181 hadoop]# yum list java*
java-1.8.0-openjdk.x86_64
[root@pminfo181 hadoop]# yum install java-1.8.0-openjdk.x86_64
```

##  关闭防火墙
service iptables status

## SSH配置免密

```shell
# 生成密钥文件 
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
# 将公钥拷贝至各节点,并导入至公钥文件中。[
scp id_rsa.pub xxx@ip:~/.ssh
或 ssh-copy-id hadoop1@ip
# cat id_rsa.pub >> authorized_keys
配置SSHD的配置，启用如下两项
RSAAuthentication yes
PubkeyAuthentication yess
```

如果发现ssh hostname 还是提示输入密码的话，需查看/var/log/secure中的日志信息，查询具体的错误，通常是目录权限不对，
一般要把密码文件的权限设为600，chmod 600 .ssh/xxx

##  关闭Selinux
很多稀奇古怪的问题都是SELINUX导致的。

## 下载安装包

```shell
wget -c https://mirrors.tuna.tsinghua.edu.cn/apache/hadoop/common/hadoop-3.2.2/hadoop-3.2.2.tar.gz
wget https://downloads.apache.org/hadoop/common/hadoop-3.2.2/hadoop-3.2.2.tar.gz.sha512
# 验证文件完整性
[root@pminfo181 download]# sha512sum -c hadoop-3.2.2.tar.gz.sha512
hadoop-3.2.2.tar.gz: 确定
```

## hostname解析

hadoop通过hostname通信，需要配置主机hosts文件

```shell
192.168.10.181 pminfo181
192.168.10.182 pminfo182
192.168.10.184 pminfo184
```



# 配置hadoop

hadoop的核心配置文件为：

- `etc/hadoop/core-site.xml`

| Parameter             | Value                                  | Notes                                            |
| :-------------------- | :------------------------------------- | :----------------------------------------------- |
| fs.defaultFS          | [hdfs://host:port/](hdfs://host:port/) | namenode的访问地址                               |
| `io.file.buffer.size` | 131072                                 | Size of read/write buffer used in SequenceFiles. |

- `etc/hadoop/hdfs-site.xml`
  - Configurations for NameNode:

| Parameter                         | Value                                                        | Notes                                                        |
| :-------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| `dfs.namenode.name.dir`           | Path on the local filesystem where the NameNode stores the namespace and transactions logs persistently. | If this is a comma-delimited list of directories then the name table is replicated in all of the directories, for redundancy. |
| `dfs.hosts` / `dfs.hosts.exclude` | List of permitted/excluded DataNodes.                        | If necessary, use these files to control the list of allowable datanodes. |
| `dfs.blocksize`                   | 268435456                                                    | HDFS blocksize of 256MB for large file-systems.              |
| `dfs.namenode.handler.count`      | 100                                                          | More NameNode server threads to handle RPCs from large number of DataNodes. |

* Configurations for DataNode:

| Parameter               | Value                                                        | Notes                                                        |
| :---------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| `dfs.datanode.data.dir` | Comma separated list of paths on the local filesystem of a `DataNode` where it should store its blocks. | If this is a comma-delimited list of directories, then data will be stored in all named directories, typically on different devices. |

- `etc/hadoop/yarn-site.xml`
- Configurations for ResourceManager and NodeManager:

| Parameter                     | Value            | Notes                                                        |
| :---------------------------- | :--------------- | :----------------------------------------------------------- |
| `yarn.acl.enable`             | `true` / `false` | Enable ACLs? Defaults to *false*.                            |
| `yarn.admin.acl`              | Admin ACL        | ACL to set admins on the cluster. ACLs are of for *comma-separated-usersspacecomma-separated-groups*. Defaults to special value of ***** which means *anyone*. Special value of just *space* means no one has access. |
| `yarn.log-aggregation-enable` | *false*          | Configuration to enable or disable log aggregation           |

其他详情参照：http://hadoop.apache.org/docs/stable3/hadoop-project-dist/hadoop-common/ClusterSetup.html#Installation

## workers

配置hadoop节点的文件

## hadoop-env.sh

hadoop一些环境变量，动态参数的设置文件。

```shell
export JAVA_HOME=/usr/local/jdk1.8.0_231
HDFS_DATANODE_USER=root
HDFS_SECONDARYNAMENODE_USER=root
HDFS_NAMENODE_USER=root
YARN_RESOURCEMANAGER_USER=root
YARN_NODEMANAGER_USER=root
```

## Logging

 `etc/hadoop/log4j.properties`是hadoop的日子配置文件。

# 配置环境变量

```shell
vi ~/.bash_profile
export HADOOP_HOME=/usr/local/hadoop-3.2.2
export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
source /etc/profile
```

# 正式安装

## 格式化namenode

```shell
hdfs namenode -format
# 看到如下信息就说明namenode已经初始化成功
......
Storage directory /data/hadoop/hdfs/name has been successfully formatted.
```

## 启动hdfs

```shell
[root@pminfo181 hadoop]# start-dfs.sh
```

## 启动yarn

```shell
[root@pminfo181 hadoop]# stop-yarn.sh
```

## 启动historyServer

```shell
mapred --daemon start historyserver
```

| 序号 | 服务       | 地址                                   |
| ---- | ---------- | -------------------------------------- |
| 1    | webHDFS    | http://192.168.10.181:9870/            |
| 2    | jobHistory | http://192.168.10.181:19888/jobhistory |

# 常见问题Q&A

* webHDFS上传失败

查看谷歌浏览器，发现如下信息：

Access to XMLHttpRequest at 'http://pminfo181:9864/webhdfs/v1/user/root/%E5%B7%A5%E7%A8%8B%E6%95%B0%E6%8…caddress=192.168.10.181:9000&createflag=&createparent=true&overwrite=false' from origin 'http://192.168.10.181:9870' has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource.

被跨越策略阻塞了。

* /tmp目录无法访问

hdfs dfs -chmod 777 /tmp