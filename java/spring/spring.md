# Spring

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