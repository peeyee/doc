# redis

redis是一款基于内存的键值数据库，常用于缓存，轻状态信息的存储，相比于数据库，吞吐量极大地提升了。

```shell
# 连接
[root@redis-master redis]# redis-cli
127.0.0.1:6379> auth Pinming9158@!~

# 选库
127.0.0.1:6379> select 15
OK

```

# redis配置

```shell
# 设置密码
requirepass Pinming9158
# 绑定监听地址
bind * -::*
# 设置日志文件
logfile logs/redis.log
```

# redis server管理

* 启动

nohup src/redis-server redis.conf 2>&1 &

# java redis

## maven 依赖

```xml
<!-- https://mvnrepository.com/artifact/redis.clients/jedis -->
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
    <version>3.6.0</version>
</dependency>
```

## demo代码

```java
public class TestRedis {
    public static void main(String[] args) {
        //连接Redis服务
        Jedis jedis = new Jedis("192.168.10.181", 6379);
        
        //如果Redis服务设置了密码，需要下面这行
        jedis.auth("Pinming9158");
        System.out.println("连接成功");
        
        //查看服务是否运行
        System.out.println("服务正在运行: "+jedis.ping());
    }
}
```

