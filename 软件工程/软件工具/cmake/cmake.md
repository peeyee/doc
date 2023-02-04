# cmake

cmake是一款跨平台的编译，测试，打包工具。可以生成makefile，worksapces。

https://cmake.org/

# 安装cmake

```shell
wget https://github.com/Kitware/CMake/releases/download/v3.26.0-rc1/cmake-3.26.0-rc1-linux-x86_64.sh
sh cmake-3.26.0-rc1-linux-x86_64.sh
```

# 使用cmake

## hello world项目编译

编写一个简单的c++ 程序helloworld.cpp。

```shell
#include<iostream>
int main(){
    using namespace std;
    cout << "hello world!" << endl;
    return 0;
}
```

### 编写CMakeLists

`CMakeLists.txt`指定编译参数， 至少需要3个项目：

- [`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required "cmake_minimum_required")

- [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project "project")

- [`add_executable(name source)`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable "add_executable")

```shell
project(helloworld)
cmake_minimum_required(VERSION 3.24)
add_executable(hello helloworld.cpp)
```

CMakeLists.txt在cpp同级目录。

```shell
[root@localhost helloworld]# ls
build  CMakeLists.txt  helloworld.cpp
```

### 编译

* cmake

为了保证源码目录干净，一般创建一个build目录，而不是在项目源码编译。

```shell
cd build
cmake ../
```

cmake完成后，会生成一个makefile，及其他文件。

* make

使用make进行编译。make执行后，当前目录生成CMakeLists.txt中指定的可执行文件hello。

```shell
[root@localhost build]# make
[ 50%] Building CXX object CMakeFiles/hello.dir/helloworld.cpp.o
[100%] Linking CXX executable hello
[100%] Built target hello

[root@localhost build]# ./hello
hello world!
```

# hello world工程化

现在我们需要让hello world工程化：使用更为有序的目录结构，添加文档等等。

* 添加src目录，存放源码

* 添加doc目录，存放文档

* 添加COPYRIGHT，设置版权

* 添加README

* 创建bin目录，存放可执行文件

## bin目录配置

将可执行文件放入bin目录。

```shell
[root@localhost helloworld]# tree
.
├── build
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── helloworld.cpp
# Cmake配置
```

工程和src分别添加CMakeLists.txt

```shell
[root@localhost helloworld]# cat CMakeLists.txt
project(helloworld)
add_subdirectory(src bin)
[root@localhost helloworld]# cat src/CMakeLists.txt 
add_executable(hello helloworld.cpp)
```

**ADD_SUBDIRECTORY**(source_dir [binary_dir] [EXCLUDE_FROM_ALL])

- 这个指令用于向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置

- EXCLUDE_FROM_ALL函数是将写的目录从编译中排除，如程序中的example

- ADD_SUBDIRECTORY(src bin)
  
  将 src 子目录加入工程并指定编译输出(包含编译中间结果)路径为bin 目录
  
  如果不进行 bin 目录的指定，那么编译结果(包括中间结果)都将存放在build/src 目录

## 安装helloworld

目标程序结构

```shell
[root@localhost helloworld]# tree
.
├── build
├── CMakeLists.txt
├── COPYRIGHT
├── doc
│   └── hello.txt
├── runHello.sh
└── src
    ├── CMakeLists.txt
    └── helloworld.cpp
```

1. install

install 指令用于安装程序至指定位置，可以安装库、文件、脚本等。

一种是打包时的指定 目录安装。

- 简单的可以这样指定目录：make install DESTDIR=/tmp/test
- 稍微复杂一点可以这样指定目录：./configure –prefix=/usr

另可以通过变量CMAKE_INSTALL_PREFIX指定安装目录，默认是/usr/local。

2. 修改CMakeLists.txt

```shell
[root@localhost helloworld]# cat CMakeLists.txt 
project(helloworld)
add_subdirectory(src bin)
install(FILES doc COPYRIGHT README share/doc/helloworld)
install(PROGRAMS runhello.sh DESTINATION /usr/bin)
install(DIRECTORY doc/ share/doc/helloworld/doc)
```

其中install FILES把相关文档安装到/usr/local/share/doc下。如果DESTINATION不存在会自动创建。

install PROGRAMS把脚本安装到/usr/bin。

install DIRECTORY用于拷贝目录内容。

请注意：

dir1与dir1/有很大区别。

dir1拷贝整个目录内容（包含dir1)，而dir1/是拷贝dir1目录下的内容。

3. 执行安装

```shell
cd build
cmake ../
make
make install
```

## 共享库安装

共享库分为两种：

* 静态库

编译时会和程序一起组合成可独立执行的文件。库名称一般以.a结尾。

* 动态库

单独编译，引用动态库的程序运行时无法单独运行，必须要引用该文件。库名称一般以.so结尾。

### 编译共享库

使用hello.cpp 编译生成动态库文件hello.so。

```shell
[root@localhost helloworld2]# tree
.
├── build
├── CMakeLists.txt
└── lib
    ├── CMakeLists.txt
    ├── hello.cpp
    └── hello.h

2 directories, 4 files
[root@localhost helloworld2]# cat CMakeLists.txt 
project(helloworld)
add_subdirectory(lib bin)
cmake_minimum_required(VERSION 3.26)
[root@localhost helloworld2]# cat lib/CMakeLists.txt 
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
```

SHARED表示生成动态共享库，STATIC生成静态共享库。

### 同时生成静/动态共享库

尝试以下几种方式:

* v1

```shell
[root@localhost lib]# cat CMakeLists.txt
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello STATIC ${LIBHELLO_SRC})
```

很遗憾这种方式只能生成一个libhello.so动态库。

* v2

```shell
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
```

这种方式的会生成libhello.so， libhello_static.a两个文件，但一般我们希望只是后缀不同。

* v3

```shell
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
SET_TARGET_PROPERTIES(hello PROPERTIES OUTPUT_NAME "hello")
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
```

这种方式是推荐的，会生成相应的libhello.so, libhello.a文件。

### 安装共享库

为了后续的共享使用，我们需要把hello.so安装到动态共享库的默认位置，一般为/usr/lib。

在lib/CMakeLists.txt添加install内容：

```shell
INSTALL(FILES hello.h DESTINATION include/hello)
INSTALL(TARGETS hello hello_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
```

其中我们将头文件安装至相对路径include下（/usr/local/include)。并使用TARGETS来讲对应的库安装至lib(/usr/local/lib)。动态库使用关键字LIBRARY, 静态库ARCHIVE。

但是参考

[Why does Red Hat not include /usr/local/lib in the default library search path? ](https://access.redhat.com/solutions/3020411)

cmake默认的安装路径/usr/local/lib|lib64其实是不在默认的动态库搜索路径中的。所以我们需要修改下：

```shell
cmake -D CMAKE_INSTALL_PREFIX=/usr ../
make
make install
```

## 使用外部库文件

本节我们将使用上一节的libhello.so编译一个main程序。整体工程如下

```shell
.
├── build
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── main.cpp
```

main.cpp

```shell
#include<hello.h>
int main(){
   hello();
   return 0;
}
```

make是会报错`致命错误：hello.h：没有那个文件或目录`。需要在cmake文件中添加:

```txt
INCLUDE_DIRECTORIES(/usr/include/hello)
```

继续编译，在make时会报错：`main.cpp:(.text+0x5)：对‘hello()’未定义的引用`

需要在src/CMakeLists.txt中添加要链接的库:

```textile
TARGET_LINK_LIBRARIES(hello libhello.so)
```

完整的src/CMakeLists.txt

```textile
add_executable(hello main.cpp)
INCLUDE_DIRECTORIES(/usr/include/hello)
TARGET_LINK_LIBRARIES(hello libhello.so)
```

# CMakeLists.txt 语法

* set

set可以指定编译变量，如设定c++标准。

```shell
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

* install

安装文件。分以下几种：

| 类型    | 关键字       |
| ----- | --------- |
| 文本文件  | FILES     |
| 非目标程序 | PROGRAMS  |
| 目录    | DIRECTORY |
| 二进制文件 | TARGETS   |
