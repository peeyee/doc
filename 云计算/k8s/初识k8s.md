# kubernetes

kubernetes是一个容器编排系统，由谷歌开源，简称k8s。通过k8s可以非常快速的实现应用的部署，扩展，故障恢复，滚动升级等生产级应用运维需求。

## 上手实验

教程地址：https://kubernetes.io/docs/tutorials/kubernetes-basics/

该教程在网页端实现k8s的极简部署，常规操作，让学习人员快速接受相关知识。

1. 创建minikube

```shell
$ minikube version
minikube version: v1.18.0
commit: ec61815d60f66a6e4f6353030a40b12362557caa-dirty

$ minikube start
* minikube v1.18.0 on Ubuntu 18.04 (kvm/amd64)
* Using the none driver based on existing profile
......
* Done! kubectl is now configured to use "minikube" cluster and "default" namespace by default

$ kubectl get nodes
NAME       STATUS   ROLES                  AGE    VERSION
minikube   Ready    control-plane,master   103s   v1.20.2

$ kubectl cluster-info
Kubernetes control plane is running at https://172.17.0.56:8443
KubeDNS is running at https://172.17.0.56:8443/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
```

2. 部署应用

```shell
$ kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1

# 查看应用
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   1/1     1            1           37s

# 查看应用实例
$ kubectl get pods
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-57978f5f5d-5bfjv   1/1     Running   0          3m9s

# 暴露8080端口
$ kubectl expose deployment/kubernetes-bootcamp --type="NodePort" \
> --port 8080
service/kubernetes-bootcamp exposed

# 查看端口映射情况，8080端口已经被映射到主机的30515端口
$ kubectl get services
NAME                  TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)          AGE
kubernetes            ClusterIP   10.96.0.1       <none>        443/TCP          6m51s
kubernetes-bootcamp   NodePort    10.110.24.232   <none>        8080:30515/TCP   48s

# 通过主机端口访问应用
$ curl minikube:30515
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-57978f5f5d-5bfjv | v=1
```

3. 扩展应用

```shell
$ kubectl scale deployments/kubernetes-bootcamp --replicas=3
deployment.apps/kubernetes-bootcamp scaled

# 检查应用豆荚情况
$ kubectl get pods
NAME                                  READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-fb5c67579-699mr   1/1     Running   0          2m55s
kubernetes-bootcamp-fb5c67579-hvhp7   1/1     Running   0          21s
kubernetes-bootcamp-fb5c67579-mwmws   1/1     Running   0          21s

# 访问应用,可以看到已经实现了负载均衡
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-fb5c67579-hvhp7 | v=1
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-fb5c67579-mwmws | v=1
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-fb5c67579-699mr | v=1

# 收缩应用至2个
$ kubectl scale deployments/kubernetes-bootcamp --replicas=2
deployment.apps/kubernetes-bootcamp scaled

$ kubectl get pods
NAME                                  READY   STATUS        RESTARTS   AGE
kubernetes-bootcamp-fb5c67579-699mr   1/1     Running       0          11m
kubernetes-bootcamp-fb5c67579-hvhp7   1/1     Terminating   0          9m20s
kubernetes-bootcamp-fb5c67579-mwmws   1/1     Running       0          9m20s
```

4. 滚动更新

```shell
# 升级kubernetes-bootcamp至v2
$ kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=jocatalin/kubernetes-bootcamp:v2
deployment.apps/kubernetes-bootcamp image updated

$ kubectl get pods
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-7d44784b7c-4bcgg   1/1     Running   0          115s
kubernetes-bootcamp-7d44784b7c-p8w9b   1/1     Running   0          111s

# 已经升级到v2了
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-7d44784b7c-4bcgg | v=2

# 回滚更新
$ kubectl rollout undo deployments/kubernetes-bootcamp
deployment.apps/kubernetes-bootcamp rolled back

$ kubectl get pods
NAME                                   READY   STATUS        RESTARTS   AGE
kubernetes-bootcamp-7d44784b7c-4bcgg   1/1     Terminating   0          5m14s
kubernetes-bootcamp-7d44784b7c-p8w9b   1/1     Terminating   0          5m10s
kubernetes-bootcamp-fb5c67579-4p2f4    1/1     Running       0          25s
kubernetes-bootcamp-fb5c67579-n8ftk    1/1     Running       0          28s

# 验证回滚后的版本
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-fb5c67579-4p2f4 | v=1
$ curl minikube:30273
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-fb5c67579-n8ftk | v=1
```

## 相关概念

* cluster

集群，管理的最大单位，是计算，存储，网络的集合。

* master

管理者，管理集群的各项任务，对外提供管理接口。

* node

工作节点，负责管理具体的容器，和执行master的指令。

* pod

豌豆荚，k8s管理的最小单元，可理解为最小的服务单元。

* controller

pod控制器，定义了pod的各种属性。

* service

service定义和实现了外界访问k8s的一种方式，service有ip + port，并且实现负载均衡。

* namespace

集群的逻辑空间，用于划分和隔离同一个集群下不同组织的资源。k8s默认有default，system两个空间。

## 安装集群

### 机器规划

| ip            | 内容              |
| ------------- | ----------------- |
| 192.168.1.106 | master，Centos6.4 |
| 192.168.1.107 | node1，Centos6.4  |
| 192.168.1.108 | node2，Centos6.4  |

```shell
# 配置yum源
cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF
```



## 安装minikube

minikube提供一个单机学习k8s的环境，易于安装。

参考：https://github.com/AliyunContainerService/minikube/wiki

1. 安装docker

```shell
# 下载仓库信息
curl https://download.docker.com/linux/centos/docker-ce.repo -o /etc/yum.repos.d/docker.repo

# 安装docker
yum install docker-ce docker-ce-cli containerd.io

# 验证版本
docker -v
Docker version 20.10.6, build 370c289

# 启动docker
systemctl start docker && systemctl enable docker
```

2. 安装kubectl

kubectl是k8s的管理客户单。

```shell
# 下载，时间比较长，耐心等待
curl -Lo minikube https://kubernetes.oss-cn-hangzhou.aliyuncs.com/minikube/releases/v1.18.1/minikube-linux-amd64 && chmod +x minikube && sudo mv minikube /usr/local/bin/
 
# 将文件放到 PATH 路径下：
chmod a+x ./kubectl && mv ./kubectl /usr/local/bin/kubectl
 
# 测试
kubectl version --client
```

3. 启动minikube

```shell
# 创建用户，minikube不允许root运行
groupadd docker
useradd docker -g docker -m
su - docker

# 启动
[docker@localhost ~]$ minikube start --driver=docker
* Centos 7.9.2009 上的 minikube v1.18.1
* 根据用户配置使用 docker 驱动程序

X The requested memory allocation of 2200MiB does not leave room for system overhead (total system memory: 2797MiB). You may face stability issues.
* 建议：Start minikube with less memory allocated: 'minikube start --memory=2200mb'

# 验证
[docker@localhost ~]$ kubectl cluster-info
Kubernetes control plane is running at https://192.168.49.2:8443
KubeDNS is running at https://192.168.49.2:8443/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
```

## k8s架构

k8s使用主从架构，master充当管理节点，对外提供api，node执行具体的容器管理。

### master

master主要负责管理集群资源，保存pod元信息等。

* api server

api server提供RESTful api，包括管理k8s集群的各种接口。

* Scheduler

调度器，根据集群的拓扑结构和各node的资源负载情况，调度pod。

* controller manager

负责管理cluster的资源，并使pod处于预期的状态。包括replication controller 、namespace controller、serviceaccounts controller等。

* etcd

是一个分布式的持久化组件，主要用于保存k8s的配置信息和状态信息。

* pod网络

用于pod之间相互通信，flannel是一个备选方案。

事实上master还运行kubelet，kube-proxy。

### node

node负责运行具体的pod，执行master的指令。node主要由kubelet，kube-proxy，pod网络组成。

* kubelet

是node的代理，kubelet执行具体操作，并向master报告相关运行信息。

* kube-proxy

service通过kube-proxy来完成对具体pod的访问，kube-proxy类似于中介者，起到负载均衡的作用。

* pod网络

用于pod之间的相互通信。

```shell
[docker@localhost ~]$ kubectl get pod --all-namespaces -o wide
NAMESPACE              NAME                                         READY   STATUS    RESTARTS   AGE    IP             NODE       NOMINATED NODE   READINESS GATES
kube-system            coredns-54d67798b7-w96mg                     1/1     Running   0          124m   172.17.0.2     minikube   <none>           <none>
kube-system            etcd-minikube                                1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kube-system            kube-apiserver-minikube                      1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kube-system            kube-controller-manager-minikube             1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kube-system            kube-proxy-rsf98                             1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kube-system            kube-scheduler-minikube                      1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kube-system            storage-provisioner                          1/1     Running   0          124m   192.168.49.2   minikube   <none>           <none>
kubernetes-dashboard   dashboard-metrics-scraper-7886f6d855-5l6dr   1/1     Running   0          121m   172.17.0.3     minikube   <none>           <none>
kubernetes-dashboard   kubernetes-dashboard-66f6c8f7c5-mf7wv        1/1     Running   0          121m   172.17.0.4     minikube   <none>           <none>
```

### 一个案例

通过httpd服务来理解整个k8s的架构。

```shell
# 创建http服务
kubectl run httpd-app-demo --image=httpd

# 查看pod
[docker@localhost ~]$ kubectl get pods -o wide
NAME             READY   STATUS    RESTARTS   AGE    IP           NODE       NOMINATED NODE   READINESS GATES
httpd-app-demo   1/1     Running   0          4m8s   172.17.0.5   minikube   <none>           <none>
```

应用创建的流程：

1. kubectl发送命令。
2. api server接受到命令，并解析命令。
3. 调用controller manager创建一个deployment资源。
4. scheduler执行调度任务，在node上创建一个pod。
5. node上的kubelet执行pod创建流程。
6. api server收集pod的信息并存储在etcd上。