## 下载压缩包
wget https://obs-mirror-ftp4.obs.cn-north-4.myhuaweicloud.com/database/mysql-8.0.20.tar.gz

## 安装依赖包
yum install -y perl openssl openssl-devel libaio perl-JSON autoconf 

## 解压并安装
tar -xvf mysql-8.0.20.tar.gz
cd mysql-8.0.20
yum remove -y mariadb-libs
rpm -ivh *.rpm

## 启动MySQL，查看状态
systemctl start mysqld
systemctl status mysqld

## 登录数据库
密码生成在/var/log/mysqld.log中，通过/password查找