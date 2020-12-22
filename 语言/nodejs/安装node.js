1. 下载
官方网站：https://nodejs.org/en/download/
wget https://nodejs.org/dist/v12.18.4/node-v12.18.4-linux-x64.tar.xz

2.　解压和安装
tar -xvf node-v12.18.4-linux-x64.tar.xz -C /opt
mv /opt/node-v12.18.4 /opt/nodejs
sudo ln -s /opt/nodejs/bin/node   /usr/local/bin/
sudo ln -s /opt/nodejs/bin/npm   /usr/local/bin/

3.测试
helloworld.js
 console.log("Hello World");

node helloworld.js
