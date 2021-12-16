# Assembly 

assembly是一款用于组装程序的插件，形成程序的发版版本，包括文档，依赖库，可执行程序等。

# pom配置

```shell
<project>
  [...]
  <build>
    [...]
    <plugins>
      <plugin>
        <artifactId>maven-assembly-plugin</artifactId>
        <version>3.3.0</version>
        <configuration>
          <descriptors>
            <descriptor>src/assembly/src.xml</descriptor> #配置文件
          </descriptors>
          <descriptorRefs>
            <descriptorRef>jar-with-dependencies</descriptorRef> #后缀
          </descriptorRefs>
          <archive>
            <manifest>
              <mainClass>org.sample.App</mainClass> #入口类
            </manifest>
          </archive>
        </configuration>
        <executions>
          <execution>
            <id>make-assembly
            <phase>package</phase>
            <goals>
              <goal>single</goal>
            </goals>
          </execution>
        </executions>
        [...]
</project>
```

# assembly配置

```shell
<assembly xmlns="http://maven.apache.org/ASSEMBLY/2.1.0"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/ASSEMBLY/2.1.0 http://maven.apache.org/xsd/assembly-2.1.0.xsd">
  <id>distribution</id>
  <formats>
    <format>jar</format>
    <format>tar.gz</format>
     <format>dir</format>
  </formats>
  <fileSets>
    <fileSet>
      <directory>${basedir}</directory>
      <includes>
        <include>*.txt</include>
      </includes>
      <excludes>
        <exclude>README.txt</exclude>
        <exclude>NOTICE.txt</exclude>
      </excludes>
    </fileSet>
  </fileSets>
  <files>
    <file>
      <source>README.txt</source>
      <outputDirectory></outputDirectory>
      <filtered>true</filtered>
    </file>
    <file>
      <source>NOTICE.txt</source>
      <outputDirectory></outputDirectory>
      <filtered>true</filtered>
    </file>
  </files>
</assembly>
```



# 参考文档
https://maven.apache.org/plugins/maven-assembly-plugin/index.html