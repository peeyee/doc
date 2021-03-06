

## 1 c++程序编译流程

```c++
// 1-预处理
g++ -E test_code.cpp -o test_code.i
// 2-编译
g++ -S test_code.i -o test_code.s //生成汇编代码
// 3-汇编
g++ -c test_code.s -o test_code.o //生成机器码
//4-链接
g++ test_code.o -o test_code //链接库文件，生成可执行的机器代码。
g++ test_code.o -static -o test_codeS //静态编译，文件更大，执行更快
```

静态编译会加库文件一起编译到目标文件中，而不是在运行时动态加载。

可以用man g++ 查看详细的g++用法。


### 8.5 函数模板

1. 模板的定义

```c++
template<[class|typename] T>
T swap(T & a, T & b);
```

其中template<...>定义了参数化类型T.意思是我用T来代表某种类型，可以是基本变量，也可以是数组，结构体，类。 C98及以上版本开始使用关键字typename。

2. 模板的用途

简化代码的编写，如果某一类函数使用相同的代码，而只是入参类型不同。则可以使用函数模板，大大减少代码量，提高效率。尤其是在数学函数中尤为明显。

3. 模板的局限性

函数模板并不是完全的通用，因为有些操作，如赋值=对于数组是无效的。

4. 函数模板的重载

函数模板也可以重载，只要特征标不同。

```c++
template<typename T>  //swap a
T swap(T & a, T & b);
template<typename T>  //swap b
T swap(T & a, T & b,int n);
```

5. 显示具体化

针对函数模板对于某些参数类型不适用的问题，可以具体化一种模板。如：

```c++
template<> 
astruct swap<astruct>(astruct & a, astruct & b);
```

语法也很好理解，将T替代为某种具体的类型如结构体astruct，并且template<typaname T>简化为template<>。

不过感觉是实例化了模板，是个鸡肋的功能，还不如直接写个swap_job的函数来的简洁明了。

## 9内存模型和名称空间

### 9.1 存储作用域

变量为分为自动变量和静态变量量大类，自动变量在函数执行期间自动创建和销毁，而静态变量在程序执行期间一直存在。自动变量在内存的**栈**区域，静态变量在内存的**堆**区域。

| 存储描述 | 持续性 |  作用域  | 链接性 |      声明      |
| :------: | :----: | :------: | :----: | :------------: |
|   自动   |  自动  |   块内   |   无   |    块内声明    |
| 局部静态 |  静态  |   块内   |   无   | 块内static声明 |
| 文件静态 |  静态  |  文件内  |  内部  |  文件内static  |
| 全局静态 |  静态  | 整个程序 |  外部  |  函数外部声明  |

全局静态的变量也叫全局变量。在其他文件中使用全局变量时，需要使用extern关键字进行引用声明。

**注意**

在c++中，使用**单定义原则**，所有变量只定义一次。定义definition，与声明declaration相对，定义对变量分配存储空间，可以进行初始化。

#### 全局变量的用途

全局变量通常用于一些需要被全局使用的数据。比如一年的月份，而且通常不修改，建议加上const关键字。

#### 静态变量的用途

当需要定义一些在本文件全局使用的变量，又不用担心污染其他程序文件时，就可以使用static，来声明文件级的静态变量，简称静态变量。

#### 局部静态变量

局部静态变量声明在函数/块内部，不会随着函数的调用结束而销毁，通常用于全局计数的作用。如记录函数被调用了多少次等功能。

### 9.3 名称空间

大型程序通过名称空间来处理命名冲突。

#### 9.3.1 引用命名空间

1. ::

```c++
std::cout
```

代码级的引用。

2. using声明

```c++
using std::cout;
```

限定声明域中的某个成员，如在main内部等。

3. using namespace编译指令

```c++
using namespace std;
```

引用一个命名空间中的所有内容。为了易用性，**编译器只允许使用一个命名空间**。否则，试想一下，使用两个以上的命名空间，很容易在编译器出现一大堆名称冲突。

## 10类与对象

oop语言相比过程式 的语言，抽象级别更高，更容易编写大型的复杂程序。

### OOP语言的思想
* 封装

数据隐藏在类的内部，外部无法访问和操作，更加安全。

* 继承

将通用的代码抽象提炼至父类，子类通过继承而获得父类的代码，是一种重用代码的机制。继承回答一个is a的关系。

* 多态

子类可以重写父类的方法，使得不同的子类表现出不同的性状。

* 抽象与实现分离

接口暴露在外，是对外部的交互标准。实现对外隐藏。

在C++中，类是模板，包含头文件声明，和定义文件，类的声明放在头文件.h中。

```c++
//A.h
class A
{
    private:
   	int a;
        int b;
    public:
       int getA();
       int getB();    
}

//A.cpp
A a;
A::getA()
{
    return a.a;
}

A::getB()
{
    return a.b;
}

```

### 构造与析构函数

构造函数

无返回类型，与类同名，可以有参。如果定义了有参的构造函数，编译器将不会生成无参的构造函数。

```c++
class A
{
    private:
    	int a;
        int b;
    public:
       int getA();
       int getB();
      A();
      A(int a,int b);
     ~A();
}

```

析构函数

析构函数与类同名，前加～，没有返回值，没有入参，处理一些善后工作，通常是释放软硬件资源，包括连接，内存等。对象的生命周期结束时，编译器自动调用析构函数。

对象赋值

**注意：**

像 stock2 = stock1 这样的赋值语句，c++是进行拷贝复制的，而不是引用复制。也就是说stock2和stock1一样，占用了一份该对象所需的存储空间。

```c++
stock1 = Stock1;
Stock stock2 = stock1;
cout << "stock1.name address: " << &(stock1.name) << endl;
cout << "stock2.name address: " << &(stock2.name) << endl;
```

**类型转换**

需要时，使用(typename)来进行类型转换。

```
TypeA a = (TypeA) typeB;
```



## 11运算符重载

### 语法

通过重载，可以使语法更为简洁和直观。比如类之间是没有+加法的。但是现实中其实有广义的加法的，比如将两个地区相加成为一个更大的地区。

```c++
returnType operatorop(argument-list)
Area operator+(Area a)
```

其中op用具体的字符替代，运算符重载本质上是一个成员函数的调用，左侧是调用对象，右侧是参数。

```c++
//成员函数形式
Area a;
Area b;
Area c = a.add(b);
//重载形式
Area c = a + b;
```

可以看到，重载模式更为简洁，更符合人类的思维模式。

### 限制

运算符重载有一些限制。

1. 重载符左侧需是用户自定义的对象。
2. 不能新增不存在的运算符，如**。
3. 不能重载系统的部分运算符和关键字。

```c++
sizeof：sizeof运算符。
.：成员运算符。
. *：成员指针运算符。
::：作用域解析运算符。
?:：条件运算符。
typeid：一个RTTI运算符。
const_cast：强制类型转换运算符。
dynamic_cast：强制类型转换运算符。
reinterpret_cast：强制类型转换运算符。
static_cast：强制类型转换运算符。
```

### 友元函数

对于 Area+1000 这种类型的运算，我们可以通过重载运算符来定义其计算。但是如果 1000+area 这种形式的，重载就无能为力了。因为1000不是一个Area的对象，友元函数可以弥补这种缺陷。

* 语法

在类声明中，定义

```c++
friend Area operator+(double size, Area a)
```

在类定义中

```c++
Area operator+(double dsize, Area a)
{
    Area tmp;
    tmp.size = dsize + a.size;
    return tmp;
}
```

友元函数不是类的成员函数，故在定义时不要加上::域限定符。

