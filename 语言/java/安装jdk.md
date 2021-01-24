# 安装jdk

## 下载jdk

[oracle官方网址](https://www.oracle.com/cn/java/technologies/javase-downloads.html)

```shell
tar -zxvf jdk-8u281-linux-x64.tar.gz -C /opt
mv /opt/jdk1.8.0_281/ /opt/jdk
```

## 设置环境变量

```shell
vi ~/.bashrc
export JAVA_HOME=/opt/jdk
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export PATH=$JAVA_HOME/bin:$JAVA_HOME/jre/bin:$PATH
source .bashrc
```



