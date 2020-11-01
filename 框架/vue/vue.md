# 安装cnpm

安装cnpm，加速nodejs模块安装速度。

```shell
npm install -g cnpm --registry=https://registry.npm.taobao.org
sudo ln -s /opt/nodejs/bin/cnpm /usr/bin
```

首先配置npm的全局模块的存放路径、cache的路径，此处我选择放在：**D:\Program Files\nodejs**
输入如下命令：

```shell
npm config set prefix "/opt/nodejs/global_modules"
npm config set cache "/opt/nodejs/global_cache"
```

