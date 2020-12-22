## actuator

端点，springboot提供的用于监控和探查spring运行情况的服务。启用actuator,需要加入配置项：

```xml```

```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
    <optional>true</optional>
</dependency>
```

并在配置文件aplication.properties中加入相关的配置项。

```yaml
management:
  endpoints:
    shutdown:
      enabled: true #开启shutdown
    web:
      exposure:  
        include: "*" #开启所有端点
      base-path: /monitor #监控的默认路径
```

### actuator的端点

* /beans   Bean说明的端点。
* /configprops 描述配置属性如何注入bean。
* /env  /env/{name}描述所有的环境变量。
* /health 报告健康信息。
* /info 获取定制信息。需要在application.yml文件中填写，通常是一些开发者信息。
* /mappings 描述controll和映射地址URL的关系。
* /metrics /metrics/{name} 描述某些应用程序运行时的度量信息。
* /loggers 记录日志信息。
* /threaddump 线程的运行信息。

可以在浏览器中，以及使用curl命令来访问上述信息。

### shell

除了web的方式，也可以通过shell访问。在maven中加入如下依赖：但是试了下还是没起来shell的服务。

```xml
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-remote-shell</artifactId>
            <version>1.5.22.RELEASE</version>
        </dependency>
```





# 部署应用

## 打包

通过maven将应用打成war包，然后将war包放入tomcat的webapp目录。

> mvn package

配置生产环境profile

在application.yml中配置生产环境profile，并通过环境变量来激活配置。

```yaml
---
spring:
  profiles: Production
  datasource:
    url: jdbc:mysql://localhost:3306/springtest
    username: root
    password: St@r0702
  jpa:
    database-platform: org.hibernate.dialect.MySQL57Dialect
```

并在生产环境的机器上配置环境变量SPRING_PROFILES_ACTIVE。

> export SPRING_PROFILES_ACTIVE=production