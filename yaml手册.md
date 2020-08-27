# yaml手册

## yaml是啥

> ```txt
> YAML: YAML Ain't Markup Language
> YAML is a human friendly data serialization standard for all programming languages.
> ```

[yaml官方网站](https://yaml.org/)

yaml是一个数据的标记语言，相比于xml，有以下优势：

* 可读性高
* 存储数据密度高
* 编写工作量小
* 便于编程语言使用，数据结构更丰富。

xml是一种比较笨重，人类难以阅读的数据标记语言，yaml文件就是为解决这个问题而生的。相比于json，json牺牲了部分的可读性，来换取程序处理的便利性。

## 语法

### 数组

数组的每个元素以“- ”标示。元素要有缩进。

```yaml
student：
	- aa
	- bb
	- cc
```

### 键值对

属性和值以： 分割。

```yaml
content：HTML/text
```

## java解析yaml文件

java可以使用snakeyaml库对yaml文件进行解析。在pom中加入依赖，同时加入资源配置项，将yaml文件进行编译至目标文件：

```xml
    <dependency>
      <groupId>org.yaml</groupId>
      <artifactId>snakeyaml</artifactId>
      <version>1.26</version>
    </dependency>

      <resources>
           <resource>
          <directory>resource</directory>
          <includes>
            <include>**/*.xml</include>
            <include>**/*.yml</include>  
            <include>**/*.properties</include>
          </includes>
        </resource>
      </resources>
```

snakeyaml将yaml文件解析成嵌套的map，键是属性，值是对应的属性值。将数组解析成list，将标量（数字，字符等）解析成对应的基本类型。


```java
Yaml yaml = new Yaml();
File file = new File("resource/config.yml");
FileInputStream fileInputStream = new FileInputStream(file);
Map map = yaml.loadAs(fileInputStream, Map.class);
```

获得map对象后就可以根据具体的内容进行解析。