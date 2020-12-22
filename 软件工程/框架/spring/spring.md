# Spring

[toc]

## 核心概念

### 依赖注入

Dependence Injection，依赖注入。一般class 可以通过new的方式产生，为啥要spring 来注入对象呢？

* 动态改变对象

  ```java
  class Example
  {
      private Animal animal;
      
      public setAnimal(Animal animal)
      {
          this.animal = animal;
      }
  }
  
  abstract class Animal
  {
      public abstract void eat(Food food);
  }
  ```

  如果使用new的方式，那文件已编译就不能改变，想更改下就需要重新编写，重新编译。通过spring ，注入的对象可以是具体的狗，猫之类的，这些在程序运行过程中都可以动态的改变。

* 减少耦合

  如果某个类ClassA，依赖于外部的类。所引用的对象设定为接口或者抽象类，那么可以将耦合降低，具体的实现可以交给spring来完成。

### IOC

控制反转，通过依赖注入的方式，可以将创建对象的选择权交给用户。例如，榨果汁，用户选择什么水果，经spring组装、注入，形成相应的果汁。类的对象创建主动权在用户，程序是不需要修改的。只要程序保持高度的抽象。

```java
//抽象水果类
public abstract class Fruit
{
   public abstract float price();
   public abstract float weight();
}

//榨汁机
@Bean
public class JuiceMaker
{
    
    private Fruit[] fruits;
    
    public void setFruits(Fruit[] fruits)
    {
        this.fruits = fruits;
    }
    
    public void makeJuice()
    {
        System.out.println("做了一杯"+fruits+"果汁");
    }
}

======web========
    用户选择具体的水果
    
    user.select(Orange)
    user.select(Apple)
    
  =====spring========
JuiceMaker juicemaker =  context.getBeans("JuiceMaker").setFruits(...);
juicemaker.makeJuice()
    
```

 框架通过setFruits注入对象，最后创建对象，完成榨汁。整个过程中，选什么水果，是由用户选择的。此外，下次店铺来了新的水果，比如番石榴，那么加上番石榴的类就好。程序不需要修改已有的代码，这也体现了开闭原则。对扩展开放，对修改关闭。

#### Bean的配置

spring可以通过多种方式配置托管的bean。

* xml文件

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  <beans xmlns="http://www.springframework.org/schema/beans"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:aop="http://www.springframework.org/schema/aop"
         xsi:schemaLocation="http://www.springframework.org/schema/beans
   http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/aop http://www.springframework.org/schema/aop/spring-aop.xsd">
      <bean id="circle" class="org.example.DAO.Circle"/>
      <bean id="room" class="org.example.DAO.Room">
          <property name="num" value="1"></property>
      </bean>
  </beans>
  ```

  通过xml文件显示的声明，来配置bean，设置bean的id，名称，完整的类路径，属性等。

* 配置类

  ```java
  @Configuration
  public class AppConfig {
      @Bean
      public Room room(){
          return new Room();
      }
  
      @Bean
      public MyService myService() {
          return new MyService();
      }
  }
  ```

  通过@Configuration注解，可以将一个类声明为配置类。在配置类中通过@Bean注解的公开方法来声明bean。

* Component Scan

  通过配置文件加注解 @Component，@Resource等等注解，可以实现自动扫描。

  ```xml
  <beans>
   	<context:component-scan base-package="com.example.DAO"/>
  </beans>
  ```

  spring会扫描com.example.DAO包下带有@Component，@Resource注解的类，作为bean。

### AOP

#### 应用场景

AOP，aspect of programming,面向切面的编程。在系统运行过程中，我们可能要验证用户的权限，记录日志，记录性能等等，这些都是通用的功能。这些通用功能称为切面aspect。如果要在类中实现这些功能，那么类的代码会非常的庞大且难以维护。spring通过动态代理的方式，实现了业务功能与通用功能的动态组合，方便了开发。

spring使用aop需要导入如下的包。

```java
    <dependency>
      <groupId>org.aspectj</groupId>
      <artifactId>aspectjweaver</artifactId>
      <version>1.9.4</version>
    </dependency>
```



#### 术语

#### 通知advice

切面的工作称为通知，也就是通用的方法。

##### 前置通知

在目标方法前的通知。

#####　后置通知

在目标方法返回后的通知，可以处理返回值。

##### 环绕通知

前后环绕目标方法的通知。

#### 切点pointCut

advice执行的地点称为切点。切点定义了“何处”。切点描述了如何匹配目标方法。

```java
@AfterReturning("execution(** com.example.PianoPerforman.perform(..))")
```

匹配返回类型为**任意类型，com.example包下的PianoPerforman类的perform方法，参数类型为..任意类型。

**疑问**:是能针对抽象类或者接口定义切点么？

**注意：**切点定义要仔细检查包路径，名称等，是经常容易报错的地方。

#### 连接点

插入切点的地方，可以简单的认为就是目标业务方法。

##### AOP的配置

* xml

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  <beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xmlns:context="http://www.springframework.org/schema/context"
  xmlns:aop="http://www.springframework.org/schema/aop"
  xsi:schemaLocation="http://www.springframework.org/schema/beans
  http://www.springframework.org/schema/beans/spring-beans.xsd
  http://www.springframework.org/schema/aop
  http://www.springframework.org/schema/aop/spring-aop.xsd
  http://www.springframework.org/schema/context
  http://www.springframework.org/schema/context/spring-context.xsd">
  <context:component-scan base-package="org.example"/>
  //启用切面自动代理
  <aop:aspectj-autoproxy/>
  <bean id="pianoPerforman" class="com.example.PianoPerforman"/>
    //定义切面bean，bean上要有Aspect注解
  <bean class="com.example.Audience"/>
  
  </beans>
  ```

​      要在xml中仿照bean添加aop的命名空间相关配置项。

* java配置类

  ```java
  @Configuration
  @ComponentScan(basePackages = "com.example")
  @EnableAspectJAutoProxy
  public class Config{
  
      //声明这是一个切面
      @Bean
      public Audience audience(){
          return new Audience();
      }
  }
  ```

  