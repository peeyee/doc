# jdk动态代理

## 应用场景

代理目标方法，实现对目标方法的增强，而不需要像静态代理那样针对特定的对象创建代理。

## 使用方式

```java
package com.pipa.designpattern.proxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Date;

/**
 * @author peter
 * @date 2021/1/3
 */
public class DynamicProxy implements InvocationHandler {

    private Object target;

    public Object getProxy(Object target) {
        this.target = target;
        Class clazz = target.getClass();
        return Proxy.newProxyInstance(clazz.getClassLoader(),clazz.getInterfaces(),this);
    }

    @Override
    /**
     * @param: target,要代理的对象
     * 　　　　　method,要代理的目标方法
     * 　　　　　args: 方法的参数
     */
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        before();
        Object obj = method.invoke(target,args);
        after();
        return obj;
    }

    private void after() {
        System.out.println(new Date()+"开始参观.");
    }

    private void before() {
        System.out.println(new Date()+"结束参观.");
    }
}

```

动态代理需实现InvocationHandler的接口，并对外提供一个获取代理的方法。

* 特点

对目标对象，只要求实现一个接口就行。

##　原理

jdk的动态代理，是根据代理对象，生成了一个$Proxy0对象，并将接口对应的方法实现为代理对象的invoke方法。