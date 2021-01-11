# mysql8.0安装

## 下载安装包

```shell
wget https://downloads.mysql.com/archives/get/p/23/file/mysql-8.0.21-linux-glibc2.12-x86_64.tar.xz
```

MD5: `d39efe001766edfa956e673c1a60a26a` 

校验下md5码,确保文件完整.

``` >shell
echo "d39efe001766edfa956e673c1a60a26a mysql-8.0.21-linux-glibc2.12-x86_64.tar.xz" > mysql8.0.21.md5 && md5sum -c mysql8.0.21.md5
```

返回成功就ok了.

## 安装前准备

### 安装依赖文件

```shell
yum search libaio  # search for info
yum install libaio # install library
```

### 清理环境

采用二进制安装的化,如果原环境有安装过mysql,一定要卸载干净,不然会报一些稀奇古怪的错误,导致安装失败.

## 安装

```shell
 groupadd mysql
 useradd -r -g mysql -s /bin/false mysql
 cd /usr/local
 sudo tar -xvf mysql-8.0.21-linux-glibc2.12-x86_64.tar.xz -C /usr/local
 mv full-path-to-mysql-VERSION-OS mysql
 cd mysql
 mkdir mysql-files
 chown mysql:mysql mysql-files
 chmod 750 mysql-files
 bin/mysqld --initialize-insecure --user=mysql
 bin/mysql_ssl_rsa_setup
 bin/mysqld_safe --user=mysql &
# Next command is optional
 cp support-files/mysql.server /etc/init.d/mysql.server

```

### 测试下mysql

1. 开始mysql服务

```shell
bin/mysqld_safe --user=mysql &
```

2. 测试

```shell
bin/mysqladmin version
bin/mysqladmin variables

# 测试开关服务
bin/mysqladmin -u root shutdown
bin/mysqld_safe --user=mysql &

#查看数据
bin/mysqlshow
bin/mysqlshow mysql
bin/mysql -e "SELECT User, Host, plugin FROM mysql.user" mysql
```

如果以上测试都正常就说明基本OK了.

### 初始化数据库用户

```shell
/usr/local/mysql# bin/mysql -u root --skip-password;
create user 'root'@'%' identified by 'Pinming@1024';
grant all on *.* to 'root'@'%';
#启用本地密码
alter user 'root'@'%' identified with mysql_native_password BY 'root'; 
```



## 配置mysql

