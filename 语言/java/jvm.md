# jvm

## jvm structure

jvm仿照冯诺依曼计算机的体系结构，把内存划分成几块区域， 用于处理单独的功能。

* 运行时数据区

有的区域和线程的生命周期相同，有的和jvm的生命周期相同。

* pc寄存器区

程序计数器，记录了非native线程执行程序的当前地址。

* 栈区

stack area，每个线程都有独立`private`的栈，栈中存储着栈帧，frame。与栈相关的错误有：StackOverflowError，栈溢出。OutOfMemoryError: 内存溢出。

* 堆

heap，是线程共享的数据区。堆是对象和数组的所在区域，堆中的对象由gc（garbage collector垃圾收集器）负责管理，堆的大小可以动态的扩展和收缩。

如果程序使用的内存超过可分配的，则抛出OutOfMemoryError。

* 方法区

这个区也是线程共享的，类似于操作系统的存储，存放的是编译好的字节码。它存储了运行时常量池，属性，方法代码。会在heap中实现方法区，如果方法区的大小不足，也会引起OutOfMemoryError。

* 运行时常量区

Run-Time Constant Pool，存放着class文件中constant_pool表中的数据，既有标量数据，也有引用数据。随class的创建而创建，如果不能申请到足够的内存，也会引起OutOfMemoryError。

## 类库

jvm提供一些必要的类库，如 java.lang.reflect 反射包相关的，Class，ClassLoader。Thread，线程相关的。Security，安全相关的，在java.security包中。

## 加载-链接-初始化

## jvm tools

* javac

  将java文件编译成class文件，即字节码文件。

* javap

将class文件显示成汇编语言。

```shell
javap -v -p Main.class > Main.s

Classfile /C:/Users/Administrator/IdeaProjects/Demo2/out/production/Demo2/com/pipa/Main.class
  Last modified 2021-3-27; size 611 bytes
  MD5 checksum 4d2333f2a74b1aa4cbaa2faec966e91f
  Compiled from "Main.java"
public class com.pipa.Main
  minor version: 0
  major version: 52
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #7.#25         // java/lang/Object."<init>":()V
   #2 = Fieldref           #26.#27        // java/lang/System.out:Ljava/io/PrintStream;
   #3 = Fieldref           #6.#28         // com/pipa/Main.i:I
   #4 = Methodref          #29.#30        // java/io/PrintStream.println:(I)V
   #5 = Fieldref           #6.#31         // com/pipa/Main.i2:I
   #6 = Class              #32            // com/pipa/Main
   #7 = Class              #33            // java/lang/Object
   #8 = Utf8               i
   #9 = Utf8               I
  #10 = Utf8               i2
  #11 = Utf8               <init>
  #12 = Utf8               ()V
  #13 = Utf8               Code
  #14 = Utf8               LineNumberTable
  #15 = Utf8               LocalVariableTable
  #16 = Utf8               this
  #17 = Utf8               Lcom/pipa/Main;
  #18 = Utf8               main
  #19 = Utf8               ([Ljava/lang/String;)V
  #20 = Utf8               args
  #21 = Utf8               [Ljava/lang/String;
  #22 = Utf8               <clinit>
  #23 = Utf8               SourceFile
  #24 = Utf8               Main.java
  #25 = NameAndType        #11:#12        // "<init>":()V
  #26 = Class              #34            // java/lang/System
  #27 = NameAndType        #35:#36        // out:Ljava/io/PrintStream;
  #28 = NameAndType        #8:#9          // i:I
  #29 = Class              #37            // java/io/PrintStream
  #30 = NameAndType        #38:#39        // println:(I)V
  #31 = NameAndType        #10:#9         // i2:I
  #32 = Utf8               com/pipa/Main
  #33 = Utf8               java/lang/Object
  #34 = Utf8               java/lang/System
  #35 = Utf8               out
  #36 = Utf8               Ljava/io/PrintStream;
  #37 = Utf8               java/io/PrintStream
  #38 = Utf8               println
  #39 = Utf8               (I)V
{
  private static int i;
    descriptor: I
    flags: ACC_PRIVATE, ACC_STATIC

  private static int i2;
    descriptor: I
    flags: ACC_PRIVATE, ACC_STATIC

  public com.pipa.Main();
    descriptor: ()V
    flags: ACC_PUBLIC
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return
      LineNumberTable:
        line 3: 0
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0       5     0  this   Lcom/pipa/Main;

  public static void main(java.lang.String[]);
    descriptor: ([Ljava/lang/String;)V
    flags: ACC_PUBLIC, ACC_STATIC
    Code:
      stack=2, locals=1, args_size=1
         0: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
         3: getstatic     #3                  // Field i:I
         6: invokevirtual #4                  // Method java/io/PrintStream.println:(I)V
         9: return
      LineNumberTable:
        line 8: 0
        line 10: 9
      LocalVariableTable:
        Start  Length  Slot  Name   Signature
            0      10     0  args   [Ljava/lang/String;

  static {};
    descriptor: ()V
    flags: ACC_STATIC
    Code:
      stack=1, locals=0, args_size=0
         0: iconst_1
         1: putstatic     #3                  // Field i:I
         4: iconst_1
         5: putstatic     #5                  // Field i2:I
         8: return
      LineNumberTable:
        line 5: 0
        line 6: 4
}
SourceFile: "Main.java"

```





