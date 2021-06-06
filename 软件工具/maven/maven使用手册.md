# maven

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

##常见问题Q&A

* Dependency xxxx not found

第一次用idea创建Maven项目，导入依赖包时就出现Dependency ‘xxxx’ not found问题，在网上查了许多，发现只需要在idea中找到File–>Invalidate Caches / Restart点击Invalidate and Restart等待就可以了

* Could not transfer artifact org.apache.maven.plugins:maven-clean-plugin:pom:2.5 from/to nexus-aliyun

 ssl证书问题，在idea-> maven->importing->VM options中添加如下参数： -Dmaven.wagon.http.ssl.insecure=true -Dmaven.wagon.http.ssl.allowall=true