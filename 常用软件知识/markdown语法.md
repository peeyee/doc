[toc]

# 一级标题

## 二级标题

### 三级标题

#1-#6代表标题级别。注意#后需要跟空格。在**视图->源代码模式**可以查看具体的编写方法。

# 块元素

## 块引用

> 块引用

## 有序列表

* 1
* 2
* 3

## 无序列表

1. a
2. b
3. c

## 任务栏

可勾选，多选。

- [x] 任务1
- [ ] 任务2

## 代码段

```shell

 apt-get install typora
    
```

## 表格

| First Header | Second Header |
| :----------- | ------------- |
| sdfs         |               |
| ssfd         |               |
| sdfds        |               |

## 水平线

***

---

## 脚注

You can create footnotes like this[^fn1] and this[^fn2]. [^fn1]: Here is the **text** of the first ***\*footnote\****. [^fn2]: Here is the **text** of the second **\*\*footnote\*\***.



## 使用字面量

使用\\反斜杠+符号的方式可以使用字面量。



## 跨度元素

### 链接

Markdown支持两种样式的链接：内联和引用。

在两种样式中，链接文本均由[方括号]分隔。

### 外部链接

要创建链接，请在链接文本的右方括号后立即使用一组常规括号，[] ()。在括号内，将您想要链接指向的URL以及链接的可选标题放在引号中。例如：

> This is [an example](http://example.com/ "Title") inline link. [This link](http://example.net/) has no title attribute.
>
> [This link](http://example.net/) has no title attribute.
>
> [百度一下](https://www.baidu.com)

按住Ctrl，点击链接进行跳转。

### 书签

跳转至文章内的部分锚点。使用[](#block-elements)的语法跳转。

> 跳转到[**块元素**](#块元素)

### 便捷链接

> [Google][]
>
> [Google]: http://google.com/



### 图片

图片与链接的语法类似，需要在前面加！。【】内添加图片的alt描述。（）内添加图片的路径。

> 这是![百度的图片](https://www.baidu.com/img/PCfb_5bf082d29588c07f842ccde3f97243ea.png)



# 高级用法

## 公式

当你需要在编辑器中插入数学公式时，可以使用两个美元符 $$ 包裹 TeX 或 LaTeX 格式的数学公式来实现。提交后，问答和文章页会根据需要加载 Mathjax 对数学公式进行渲染。如：

```
$$
\mathbf{V}_1 \times \mathbf{V}_2 =  \begin{vmatrix} 
\mathbf{i} & \mathbf{j} & \mathbf{k} \\
\frac{\partial X}{\partial u} &  \frac{\partial Y}{\partial u} & 0 \\
\frac{\partial X}{\partial v} &  \frac{\partial Y}{\partial v} & 0 \\
\end{vmatrix}
${step1}{\style{visibility:hidden}{(x+1)(x+1)}}
$$
```

$$
\mathbf{V}_1 \times \mathbf{V}_2 =  \begin{vmatrix} 
\mathbf{i} & \mathbf{j} & \mathbf{k} \\
\frac{\partial X}{\partial u} &  \frac{\partial Y}{\partial u} & 0 \\
\frac{\partial X}{\partial v} &  \frac{\partial Y}{\partial v} & 0 \\
\end{vmatrix}
${step1}{\style{visibility:hidden}{(x+1)(x+1)}}
$$

## 流程图
