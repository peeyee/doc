# maven

maven是一个解决项目**依赖**，完成项目的**编译，测试，构建，发布**等生命周期的项目管理工具。

# 安装

下载解压：

```shell
wget http://mirrors.hust.edu.cn/apache/maven/maven-3/3.3.9/binaries/apache-maven-3.3.9-bin.tar.gz
tar -zxvf  apache-maven-3.3.9-bin.tar.gz
mv -f apache-maven-3.3.9 /usr/local/
```

编辑 **/etc/profile** 文件 **sudo vim /etc/profile**，在文件末尾添加如下代码：

```shell
export MAVEN_HOME=/usr/local/apache-maven-3.3.9
# ${}精确界定变量范围
export PATH=${PATH}:${MAVEN_HOME}/bin
```

保存文件，并运行如下命令使环境变量生效：

\# source /etc/profile

在控制台输入如下命令，如果能看到 Maven 相关版本信息，则说明 Maven 已经安装成功：

```
# mvn -v
```

# pom.xml

pom.xml是maven的配置文件。

```xml

```



# 设置镜像仓库

```xml
<settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
   xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0 
   http://maven.apache.org/xsd/settings-1.0.0.xsd">

	  
<mirrors>
	<mirror>  
		<id>nexus-aliyun</id>  
		<mirrorOf>central</mirrorOf>    
		<name>Nexus aliyun</name>  
		<url>http://maven.aliyun.com/nexus/content/groups/public</url>  
	</mirror> 
</mirrors>

<localRepository>E:\MavenRepository</localRepository>

</settings>
```



# 常用命令

```shell
mvn package ：打包
mvn site ： 产生site
mvn test ： 运行测试
mvn compile ： 编译
mvn test-compile ： 编译测试代码
mvn archetype:generate ： 反向生成项目的骨架
mvn jar ： 生成jar包
mvn install ： 本地安装
mvn clean ： 清除编译后的项目文件
mvn eclipse:eclipse ： 生成eclipse项目
mvn idea:idea ： 生成idea项目
mvn -Dtest package ： 只打包不测试
mvn test -skipping comiple ： 只测试不编译
mvn dependency:list ： 查看当前项目已被解析的依赖
mvn deploy ： 上传到私服
mvn source:jar ： 源码打包
mvn -e ： 显示详细错误信息
mvn validate ： 验证工程是否正确
mvn jetty:run ： 运行项目于jetty上
```

# 常见问题Q&A

* Dependency xxxx not found

第一次用idea创建Maven项目，导入依赖包时就出现Dependency ‘xxxx’ not found问题，在网上查了许多，发现只需要在idea中找到File–>Invalidate Caches / Restart点击Invalidate and Restart等待就可以了

* Could not transfer artifact org.apache.maven.plugins:maven-clean-plugin:pom:2.5 from/to nexus-aliyun

 ssl证书问题，在idea-> maven->importing->VM options中添加如下参数： -Dmaven.wagon.http.ssl.insecure=true -Dmaven.wagon.http.ssl.allowall=true

# 其他

## 手工安装包

```shell
mvn install:install-file -Dfile="C:\Users\peter\Desktop\plugin-unstructured-storage-util-0.0.1-SNAPSHOT.jar" \
-DgroupId=com.alibaba.datax \
-DartifactId=plugin-unstructured-storage-util \
-Dversion=0.0.1-SNAPSHOT \
-Dpackaging=jar
```

## 添加打大包插件

```xml
 <pluginManagement><!-- lock down plugins versions to avoid using Maven defaults (may be moved to parent pom) -->
      <plugins>
<plugin>
  <groupId>org.apache.maven.plugins</groupId>
  <artifactId>maven-assembly-plugin</artifactId>
  <version>2.4</version>
  <configuration>
    <descriptorRefs>
      <descriptorRef>jar-with-dependencies</descriptorRef>
    </descriptorRefs>
  </configuration>
  <executions>
    <execution>
      <id>make-assembly</id>
      <phase>package</phase>
      <goals>
        <goal>single</goal>
      </goals>
    </execution>
  </executions>
</plugin>
</plugins>
</pluginManagement>
```

在插件中点击mvn assembly:assembly开始打大包。