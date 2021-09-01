# docker

## docker是什么

Docker 是一个开源的应用容器引擎，由go语言编写。开发者可以将应用和相关依赖打包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上。容器是完全使用沙箱机制，容器之间是相互隔离的，性能开销低，启动在ms级。

## docker的应用场景

由于docker的隔离机制，程序的运行运行时环境可以标准化，使得部署是一件很简单的事情。通常用于CD,CI。

## docker的基本概念

### 镜像

镜像就是模板，类似于面向对象的概念，在docker中，镜像是不可变的，意味着稳定和安全性。

### 容器

容器是镜像的实例化，类似于面向对象中的对象的概念。

### 镜像仓库

docker提供官方的镜像仓库，[dockerhub](https://hub.docker.com/)，上面有各种各样的镜像，是镜像的市场，包括redis，mysql等，可以一键部署相应的服务。

## docker安装

### 卸载旧版本

较旧的 Docker 版本称为 docker 或 docker-engine 。如果已安装这些程序，请卸载它们以及相关的依赖项。

$ sudo yum remove docker \
         docker-client \
         docker-client-latest \
         docker-common \
         docker-latest \
         docker-latest-logrotate \
         docker-logrotate \
         docker-engine

### 使用 Docker 仓库进行安装

在新主机上首次安装 Docker Engine-Community 之前，需要设置 Docker 仓库。之后，您可以从仓库安装和更新 Docker。

安装所需的软件包，yum-utils 提供了 yum-config-manager ，并且 device mapper 存储驱动程序需要 device-mapper-persistent-data 和 lvm2。

```shell
$ sudo yum install -y yum-utils \
 device-mapper-persistent-data \
 lvm2
```

使用以下命令来设置稳定的仓库。

### 配置yum源

```shell
$ sudo yum-config-manager \
可以选择国内的一些源地址：
## 阿里云

$ sudo yum-config-manager \
  --add-repo \
  http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo

## 清华大学源
$ sudo yum-config-manager \
  --add-repo \
  https://mirrors.tuna.tsinghua.edu.cn/docker-ce/linux/centos/docker-ce.repo

```
### 安装 Docker Engine-Community
安装最新版本的 Docker Engine-Community 和 containerd，或者转到下一步安装特定版本：

```
$ sudo yum install docker-ce docker-ce-cli containerd.io

$ yum list docker-ce --showduplicates | sort -r
docker-ce.x86_64  3:18.09.1-3.el7           docker-ce-stable
docker-ce.x86_64  3:18.09.0-3.el7           docker-ce-stable
docker-ce.x86_64  18.06.1.ce-3.el7           docker-ce-stable
docker-ce.x86_64  18.06.0.ce-3.el7           docker-ce-stable
通过其完整的软件包名称安装特定版本，该软件包名称是软件包名称（docker-ce）加上版本字符串（第二列），从第一个冒号（:）一直到第一个连字符，并用连字符（-）分隔。例如：docker-ce-18.09.1。

$ sudo yum install docker-ce-<VERSION_STRING> docker-ce-cli-<VERSION_STRING> containerd.io
```
启动 Docker。
```shell
$ sudo systemctl start docker
```

通过运行 hello-world 映像来验证是否正确安装了 Docker Engine-Community 。

```shell
$ sudo docker run hello-world
```

## 镜像相关命令

### docker images

查看相关镜像。

```shell
[root@pminfo182 ~]# docker images
REPOSITORY         TAG          IMAGE ID       CREATED        SIZE
python             latest       da24d18bf4bf   5 weeks ago    885MB

# 清理None镜像
[root@pminfo182 ~]# docker image prune
WARNING! This will remove all dangling images.
Are you sure you want to continue? [y/N] y
Total reclaimed space: 0B

# 清理无容器使用的镜像
[root@pminfo182 ~]# docker image prune -a
WARNING! This will remove all images without at least one container associated to them.
Are you sure you want to continue? [y/N] y
.......
Total reclaimed space: 696.6MB

```

### docker pull

拉取相关镜像，dockerhub比较慢，可以设置成国内的镜像仓库。

```shell
[root@pminfo182 ~]# vi /etc/docker/daemon.json
{
    "registry-mirrors":[ "https://registry.docker-cn.com" ]
}

#查找mysql镜像
[root@pminfo182 ~]# docker search mysql
NAME                              DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
mysql                             MySQL is a widely used, open-source relation…   10532     [OK]       

#获取镜像
docker pull mysql
```

### docker rmi

删除镜像使用 **docker rmi** 命令，比如我们删除 hello-world 镜像：

```
$ docker rmi hello-world
```

### docker build

构建镜像，经过一系列步骤，构建一个docker镜像文件。相关指令在Dockerfile中编写。从FROM开始，每一个指令都会在镜像上创建一个新的层，每一个指令的前缀都必须是大写的。

```shell
[root@pminfo182 ~]# vi Dockerfile
FROM    centos:6.7
MAINTAINER      Fisher "fisher@sudops.com"

RUN     /bin/echo 'root:123456' |chpasswd
RUN     useradd runoob
RUN     /bin/echo 'runoob:123456' |chpasswd
RUN     /bin/echo -e "LANG=\"en_US.UTF-8\"" >/etc/default/local
EXPOSE  22
EXPOSE  80
CMD     /usr/sbin/sshd -D

[root@pminfo182 ~]# docker build -t runoob/centos:6.7 .
```

* WORKDIR

  指定工作目录，需要提前创建好。可以理解为linux下的cd命令。

* RUN

执行一条命令，有两种模式。
```shell
# shell 格式：
RUN <命令行命令>

# exec 格式：
RUN ["可执行文件", "参数1", "参数2"]
# 等价于 RUN ./test.php dev offline
RUN ["./test.php", "dev", "offline"] 
```

* CMD

容器启动时的默认命令，仅最后一个生效。

```shell
CMD <shell 命令> 
CMD ["<可执行文件或命令>","<param1>","<param2>",...] 
CMD ["<param1>","<param2>",...]  # 该写法是为 ENTRYPOINT 指令指定的程序提供默认参数
```

* ENTRYPOINT

```shell
ENTRYPOINT ["<executeable>","<param1>","<param2>",...]
```

容器的入口点，覆盖 CMD 指令， docker run 的命令行参数会被当作参数送给 ENTRYPOINT 指令指定的程序。

entrypoint和cmd搭配使用，cmd提供默认参数，如果需求改变参数，则在run的后面添加：

```shell
FROM nginx

ENTRYPOINT ["nginx", "-c"] # 定参
CMD ["/etc/nginx/nginx.conf"] # 默认参数 
```

* EXPOSE

指定暴露的端口。

* COPY

复制指令，从上下文目录中复制文件或者目录到容器里指定路径。

```shell
COPY [--chown=<user>:<group>] <源路径1>...  <目标路径>

# 源路径：源文件或者源目录，这里可以是通配符表达式,例如：
COPY hom* /mydir/
COPY hom?.txt /mydir/
```

* VOLUME

定义匿名数据卷。在启动容器时忘记挂载数据卷，会自动挂载到匿名卷。

作用：

1. 避免重要的数据，因容器重启而丢失，这是非常致命的。
2. 避免容器不断变大。

* ENV

为了使新软件更易于运行，可以使用`ENV`设定环境变量。例如，`ENV PATH=/usr/local/nginx/bin:$PATH`确保它`CMD ["nginx"]` 正常工作。该`ENV`指令对于提供特定于您希望容器化的服务的必需环境变量（例如Postgres的）也很有用 `PGDATA`。

最后，`ENV`还可以用于设置常用的版本号，以便更容易维护版本凹凸，如以下示例所示：

```
ENV PG_MAJOR=9.3
ENV PG_VERSION=9.3.4
RUN curl -SL https://example.com/postgres-$PG_VERSION.tar.xz | tar -xJC /usr/src/postgress && …
ENV PATH=/usr/local/postgres-$PG_MAJOR/bin:$PATH
```

* ARG
  构建参数，构建命令 docker build 中可以用 --build-arg <参数名>=<值> 来覆盖。

  ```shell
  ARG VERSION=1.0
  ```

  

* docker build

  根据dockerfile构建镜像，Dockerfile要放在当前目录，标签名必须小写。

  ```shell
  docker bulid -t tagName .
  ```

  

## 容器相关命令

### docker run

根据一个镜像实例化某个容器。

```shell
docker run -itd --name containerName -p host:container -v host:container  -e NAME=VALUE <imageID>
```

-p：端口映射，把主机端口映射到容器端口。

-v：数据卷映射。

-e：环境变量设置，用NAME=VALUE的格式。

### docker stop|start

启停容器，`docker stop|start|restart containerID`。

### docker rm 

删除容器`docker rm axcfee`。

### docker exec

进入容器内部，进行维护或者状态查看。

```shell
docker exec -it containerID /bin/bash
```

### docker inspect

查看容器的一些配置信息，`docker inspect 344dcd974b62`。

### 导出容器

如果要导出本地某个容器，可以使用 **docker export** 命令。

```
$ docker export 1e560fca3906 > ubuntu.tar
```

### 导入容器

可以使用 docker import 从容器快照文件中再导入为镜像，以下实例将快照文件 ubuntu.tar 导入到镜像 test/ubuntu:v1:

cat docker/ubuntu.tar | docker import - test/ubuntu:v1

