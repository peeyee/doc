# [JVM调优 dump文件怎么生成和分析](https://www.cnblogs.com/myseries/p/10827195.html)

**1、获取JVM的dump文件的两种方式**　　

　　1. JVM启动时增加两个参数:

```
#出现 OOME 时生成堆 dump: 
-XX:+HeapDumpOnOutOfMemoryError
#生成堆文件地址：
-XX:HeapDumpPath=/home/liuke/jvmlogs/
```

　　2. 发现程序异常前通过执行指令，直接生成当前JVM的dmp文件，6214是指JVM的进程号

```
jmap -dump:format=b,file=/home/admin/logs/heap.hprof 6214
```

　　获得heap.hprof以后，就可以分析你的java线程里面对象占用堆内存的情况了。

　　推荐使用Eclipse插件Memory Analyzer Tool来打开heap.hprof文件。　

由于第一种方式是一种事后方式，需要等待当前JVM出现问题后才能生成dmp文件，实时性不高，第二种方式在执行时，JVM是暂停服务的，所以对**线上的运行会产生影响**。所以建议第一种方式。

 

**2. 查看整个JVM内存状态** 

　　jmap -heap [pid]

[![img](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174042660-1563317412.png)](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174042660-1563317412.png)

------

 

**3. 查看JVM堆中对象详细占用情况**
　　jmap -histo [pid]


**4. 导出整个JVM 中内存信息，可以利用其它工具打开dump文件分析，例如jdk自带的visualvm工具**

　　jmap -dump:file=文件名.dump [pid]

　　jmap -dump:format=b,file=文件名 [pid]

　　format=b指定为二进制格式文件

 

利用MAT进行分析文件，下面是MAT安装教程

在Eclipse help -> Eclipse Marketplace下搜索Memory: 

 [![img](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174129989-1759341078.png)](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174129989-1759341078.png)

安装后打开导出的文件：

1、打开MAT面板

 [![img](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174135172-1890815862.png)](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174135172-1890815862.png)

 

2、打开导出文件

 [![img](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174141842-911767453.png)](https://img2018.cnblogs.com/blog/885859/201905/885859-20190507174141842-911767453.png)

3、分析

暂时不写了参照android的分析  https://www.jianshu.com/p/c8e0f8748ac0