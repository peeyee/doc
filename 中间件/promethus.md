# 第一章

dolphinDB提供了丰富的监控指标，本文通过promethus + grafana的组合，快速构建dolphinDB集群的监控，有效地支撑日常的运维管理工作，保障集群稳定、高效运行。

## 1.1 安装promethus

promethus是一款开源的监控系统，使用非常简单而方便。

### 1.1.1 二进制安装

``` shell
wget -c https://github.com/prometheus/prometheus/releases/download/v2.35.0/prometheus-2.35.0.linux-amd64.tar.gz
tar -zxvf prometheus-2.35.0.linux-amd64.tar.gz
mv prometheus-2.35.0.linux-amd64 prometheus
```

### 1.1.2 安装node_exporter

node_exporter是promethuese的一款插件，主要用于监控硬件层面的相关指标，包括cpu，io，memory等。需要在集群的每个节点上安装node_exporter，并启动。

```shell
wget -c https://github.com/prometheus/node_exporter/releases/download/v1.3.1/node_exporter-1.3.1.linux-amd64.tar.gz
tar -zxvf node_exporter-1.3.1.linux-amd64.tar.gz
nohup ./node_exporter > node.log 2>&1 &
```

### 1.1.3 配置

修改prometheus.yml，部分配置如下：

```shell
scrape_configs:
  # The job name is added as a label `job=<job_name>` to any timeseries scraped from this config.
  - job_name: "prometheus"

    # metrics_path defaults to '/metrics'
    # scheme defaults to 'http'.

    static_configs:
      - targets: ["localhost:9090"]

  - job_name: node
    static_configs:
      - targets: 
        - localhost:9100
      # - add other node here.
```

根据实际集群的拓扑，在node.static_configs.targets数组中增加其他节点。

### 1.1.3 启动

创建启动脚本run.sh，输入如下内容：

```shell
#!/bin/bash

function start()
{
  nohup ./prometheus --config.file=prometheus.yml > prometheus.log 2>&1 &
  exit 0
}

function stop()
{
  ps -ef|grep prometheus|grep -v grep|awk '{print "kill -9 " $2}'|sh
  exit 0
}

case $1 in
   -h|--help)
     echo "Usage $0 stop|start|restart"
     ;;

   'stop')
     stop
     ;;

   'start')
     start
     ;;

   'restart')
     stop
     start
     ;;
esac
```

```shell
chmod u+x run.sh
./run start
```

**验证**

访问promethus所在服务器，默认端口是9090，在status->targets菜单下，验证各服务状态，都是up，说明已经成功安装。



## 1.2  安装grafana

grafana是一款开源的可视化工具，用于提供图形化监控界面。

### 1.2.1 二进制安装

```shell
wget https://dl.grafana.com/enterprise/release/grafana-enterprise-8.5.0.linux-amd64.tar.gz
tar -zxvf grafana-enterprise-8.5.0.linux-amd64.tar.gz
```

### 1.2.2 启动

```shell
nohup ./bin/grafana-server web > grafana.log 2>&1 &
```

默认用户是admin/admin。

###  1.2.3 配置

* datasource

configration->datasource中添加promethus数据源，根据需求修改Scrape interval，Query timeout。

### 1.2.4 导入dashboard

在grafana官网中，product-> dashboard，可以找到共享的dashboard。

https://grafana.com/grafana/dashboards/

* *Node Exporter Full*

一个全面的机器监控面板，包含cpu，内存，网络等。

https://grafana.com/api/dashboards/1860/revisions/26/download

1. dashboard->import，导入下载的json
2. 设定promethus数据源，点击import完成导入。



# 参考资料

* https://grafana.com/
* https://prometheus.io/docs/introduction/overview/
* https://grafana.com/grafana/dashboards/