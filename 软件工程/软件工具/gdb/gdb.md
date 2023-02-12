# gdb

gdb， gun project debugger, 用于调试c/c++的工具。

# eample1

通过 example1.cpp 来学习使用gdb来调试。

```cpp
#include <iostream>
int main(){
   int j = 3;
   int k = 7;
   j += k;
   k = j * 2;
   std::cout << "Hello there" << std::endl;
}
```

首先编译example1.cpp：

```shell
g++ -g example1.cpp -o example1
```

**-g**选项可以生成供gdb调试的信息。

## 1 运行gdb

syntax

```shell
    gdb [program] 
```

使用gdb启动example1。

```shell
gdb example1
```

## 2  help信息

可以使用help罗列支持的模块，并使用

```
help <clasename>
```

来查询具体命令，比如我们查询如何设置断点，那么输入gdb breakpoints。

```textile
(gdb) help breakpoints
Making program stop at certain points.

List of commands:

awatch -- Set a watchpoint for an expression
break -- Set breakpoint at specified line or function
```

## 3 简单调试

首先我们跑下example1。

### run

run用于运行程序。

输出：

```textile
(gdb) run
Starting program: /data/example1 
Hello there
[Inferior 1 (process 13590) exited normally]
```

 程序打印出hello信息，并且是正常退出的。

### break

接着设置断点，可以通过函数名或者行号设置断点。这里我们通过停在main, 然后跑起来。

```shell
(gdb) break mainq
Breakpoint 1 at 0x4007e1
(gdb) run
Starting program: /data/example1 

Breakpoint 1, main () at example1.cpp:3
3          int j = 3;1
```

### next

接着我们需要继续往下跑，使用next命令。next执行当前行，并停留在下一行，即单步调试。

### list

那么我们跑到哪了呢，通过list查看上下文信息。

```textile
(gdb) list
1       #include <iostream>
2       int main(){
3          int j = 3;
4          int k = 7;
5          j += k;
6          k = j * 2;
7          std::cout << "Hello there" << std::endl;
8       }
```

由此我们跑到了第4行。

### print

现在我们想看下变量j的值，可以使用print，

```textile
(gdb) print j
$1 = 3
```

print也可以进行一些表达式计算。

```shell
(gdb) print j * j
$2 = 9
```

至此example1.cpp简单调试已经结束，使用`quit` 退出gdb吧。

```textile
(gdb) quit
A debugging session is active.

        Inferior 1 [process 27139] will be killed.

Quit anyway? (y or n) y
```

# eample2

此节使用example2.cpp，我们需要找调试并定位程序crash的原因。

```cpp
#include <iostream>

void crash(int *);
int * f1(int *);
int * f2(int *);

int main(){
   int i = 3;
   f1(&i);
}

int * f1(int * x){
   int * j = f2(x);
   crash(j);
   return j;
}

int * f2(int * x){
   return 0;
}

void crash(int * i){
   * i = 1;
}

```

example2依次调用3个函数，其中一个函数返回了空指针，导致程序segment fault。

```shell
Program received signal SIGSEGV, Segmentation fault.
0x00000000004006b8 in crash (i=0x0) at example2.cpp:24
24         * i = 1;
```

### up/down

查看函数调用栈。

* down

down -- Select and print stack frame called by this one，找被当前函数调用的函数。

* up

up -- Select and print stack frame that called this one，找调用当前函数的函数

```shell
(gdb) up
#1  0x0000000000400688 in main () at example2.cpp:11
11         crash(p);
(gdb) up
#1  0x0000000000400697 in f1 (x=0x7fffffffe4ac) at example2.cpp:14
14         crash(j);
(gdb) up
#2  0x0000000000400668 in main () at example2.cpp:9
9          f1(&i);
```

### display

如果想一直跟踪一个值可以使用display。取消跟踪使用undisplay。undisplay <i>，i为跟踪变量的id。



## watch

如果想追踪一个变量其值何时改变。可以使用watch，gdb会在变量发生变化时通知，并stop。

## info

info用于查看一些信息，比如断点。

```shell
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
3       hw watchpoint  keep y                      i

```

## delete

删除断点

delete [id]

id为对应断点的编号，如果不加id，则会提示是否删除所有断点。

8 附录

* 
