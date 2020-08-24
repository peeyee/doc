# springboot

## why springboot

springboot大大简化了spring开发的大量配置和难度。试想一下，一个spring项目需要在xml中配置各种属性，还需要管理好dependency。这通常都要耗费大量的时间，还容易引进一些配置性的错误。springboot通过自动化配置，和起步依赖，大大缩短了初始化和开发一个项目的难度。

### 安装springboot cli

springboot cli 是管理和使用springboot的工具。

[springboot cli](https://repo.spring.io/release/org/springframework/boot/spring-boot-cli/2.3.3.RELEASE/spring-boot-cli-2.3.3.RELEASE-bin.tar.gz "下载")

下载完成后，解压并创建软连接，就可以使用了。

```shell
tar -zxvf spring-boot-cli-2.3.3.RELEASE-bin.tar.gz -C /opt
sudo ln -s  /opt/spring/bin/spring /bin/spring

peter@bigdata:~$ spring --version
Spring CLI v2.3.3.RELEASE
```

### springboot的注解

> ```java
> @SpringBootApplication //这个注解等同于以下3个注解的功能
> @Configuration  //开启配置类
> @ComponentScan // 开启组件扫描
> @EnableAutoConfiguration //开启自动配置
> ```

### 起步依赖

spring提供了一个jar包，里面包含了web开发所需的各种依赖，内置了tomcat。当然也可以根据需要添加其他的依赖，例如访问redis，mysql的jar包。

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
```



