# mysql8.0安装

# 1.安装前准备

1.1禁用selinux

```shell
$ vi /etc/sysconfig/selinux
# 改为
SELINUX=disabled
$ setenforce 0
```

1.2 查看iptables

# 2.安装

```shell
docker pull mysql:8.0

docker run --name=mysql8.0 -e MYSQL_ROOT_PASSWORD=root -p 3308:3306 -v /alidata/mysql8:/var/lib/mysql -d mysql:8.0 
```

# 3.初始化root远程账号

```shell
docker exec -it mysql1 mysql -uroot -p
ALTER USER 'root'@'%' IDENTIFIED BY 'password';
flush privileges;
```



# 4 故障排查

*  容器启动报错 (iptables failed: iptables --wait -t nat -A DOCKER -p tcp -d 0/0 --dport]

解决办法：systemctl restart docker

# 5. 参数配置

修改配置文件/etc/my.cnf。加入如下参数：

```shell
max-connections=300
default-time_zone='+8:00'
```

