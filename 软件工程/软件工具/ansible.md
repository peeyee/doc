# ansible

ansible是一个自动化部署安装工具，尤其适用于集群环境下的软件安装，能够大大的提高部署效率。

# 安装ansible

```shell
[root@pminfo181 download]# yum install ansible
[root@pminfo181 download]# ansible --version
ansible 2.9.10
```

# ansible配置

## 编辑hosts文件

```txt
vi /etc/ansible/ansible.cfg
[hadoop_servers]
172.18.18.120 namenode_active=true namenode_standby=false datanode=true
172.18.18.121 namenode_active=false namenode_standby=true datanode=true
172.18.18.122 namenode_active=false namenode_standby=false datanode=true

创建相关目录
[root@pminfo181 hadoop-3.2.2]# mkdir -p /opt/ansible/vars
[root@pminfo181 hadoop-3.2.2]# mkdir -p /opt/ansible/roles/files
[root@pminfo181 hadoop-3.2.2]# mkdir -p /opt/ansible/roles/templates/
```

测试下ssh连通性

```shell
[root@pminfo181 ~]# ansible hadoop_servers -a 'ps'
192.168.10.181 | CHANGED | rc=0 >>
  PID TTY          TIME CMD
16483 pts/4    00:00:00 sh
16495 pts/4    00:00:00 python
16514 pts/4    00:00:00 ps
192.168.10.182 | CHANGED | rc=0 >>
  PID TTY          TIME CMD
28813 pts/0    00:00:00 sh
28824 pts/0    00:00:00 python
28829 pts/0    00:00:00 ps
192.168.10.184 | CHANGED | rc=0 >>
  PID TTY          TIME CMD
19885 pts/0    00:00:00 sh
19896 pts/0    00:00:00 python
19901 pts/0    00:00:00 ps
```

## playbook

剧本，安装部署软件资源，就像演员演戏，有着一些的步骤，和道具支持。在ansible的帮助下，安装软件，只要把资源，顺序定义好，即把剧本写好，演绎出来就可以了。剧本使用yml格式编写，一个简单的列子：

```shell
[root@pminfo181 ~]# cat /opt/ansible/simple-playbook.yml 
- hosts: all
  tasks:
    - name: whoami
      shell: 'whoami'


[root@pminfo181 ~]# ansible-playbook /opt/ansible/simple-playbook.yml
PLAY [all] **************************************************************************************************************************

TASK [Gathering Facts] **************************************************************************************************************
ok: [192.168.10.184]
ok: [192.168.10.182]
ok: [192.168.10.181]

TASK [whoami] ***********************************************************************************************************************
changed: [192.168.10.181]
changed: [192.168.10.182]
changed: [192.168.10.184]

PLAY RECAP **************************************************************************************************************************
192.168.10.181             : ok=2    changed=1    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0   
192.168.10.182             : ok=2    changed=1    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0   
192.168.10.184             : ok=2    changed=1    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0  
```

