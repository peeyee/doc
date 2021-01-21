# docker安装

## 卸载旧版本

较旧的 Docker 版本称为 docker 或 docker-engine 。如果已安装这些程序，请卸载它们以及相关的依赖项。

```shell
$ sudo yum remove docker \
         docker-client \
         docker-client-latest \
         docker-common \
         docker-latest \
         docker-latest-logrotate \
         docker-logrotate \
         docker-engine
```

## 自动安装

安装命令如下：

```shell
curl -fsSL https://get.docker.com | bash -s docker --mirror Aliyun
```

也可以使用国内 daocloud 一键安装命令：

```shell
curl -sSL https://get.daocloud.io/docker > docker_ce_install.sh
chmod u+x docker_ce_install.sh
./docker_ce.install.sh
```

## 手动安装

1. 下载docker-ce

```shell
yum -y install wget
cd /etc/yum.repos.d
wget http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
yum makecache fast
```

2. 安装docker社区版本

```shell
yum -y install docker-ce
mkdir -p /app/docker
mkdir -p /etc/docker
```

3. 配置docker仓库镜像

```shell
vi /etc/docker/daemon.json 
{"registry-mirrors": ["https://a14c78qe.mirror.aliyuncs.com"],
"log-driver": "json-file",
    "log-opts": {
        "max-size": "100m",
        "max-file": "5"
    },
"live-restore": false,
"insecure-registries": [
	"reg.pinming.org"
 ]
}
```

4. 修改docker启动服务 

```shell
mkdir -p /etc/systemd/system/docker.service.d/

vi /etc/systemd/system/docker.service.d/override.conf

[Service]
ExecStart=
ExecStart=/usr/bin/dockerd --data-root=/app/docker -H 0.0.0.0:2375 -H unix:///var/run/docker.sock $DOCKER_NETWORK_OPTIONS
```

5. docker启动

```shell
systemctl daemon-reload &&\
systemctl enable docker &&\
systemctl start docker &&\
systemctl status docker
```



