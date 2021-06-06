# log4j2

一款日志记录器，相对于log4j 1.x有了性能和功能的极大提升。

## maven 依赖

主要是两个包，log4j-api-2.5.jar，log4j-core-2.5.jar

```xml
<dependencies>
		<dependency>
			<groupId>org.apache.logging.log4j</groupId>
			<artifactId>log4j-api</artifactId>
			<version>2.5</version>
		</dependency>
		<dependency>
			<groupId>org.apache.logging.log4j</groupId>
			<artifactId>log4j-core</artifactId>
			<version>2.5</version>
		</dependency>
</dependencies>
```
## demo代码

```java
public static void main(String[] args) {
		Logger logger = LogManager.getLogger(LogManager.ROOT_LOGGER_NAME);
		logger.trace("trace level");
		logger.debug("debug level");
		logger.info("info level");
		logger.warn("warn level");
		logger.error("error level");
		logger.fatal("fatal level");
}
```

运行后输出
ERROR StatusLogger No log4j2 configuration file found. Using default configuration: logging only errors to the console.
20:37:11.965 [main] ERROR  - error level
20:37:11.965 [main] FATAL  - fatal level

## 配置log4j2

添加log4j2.xml，添加到resources目录即可

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Configuration status="WARN">
    <Appenders>
        <Console name="Console" target="SYSTEM_OUT">
            <PatternLayout pattern="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
        </Console>
    </Appenders>
    <Loggers>
        <Root level="error">
            <AppenderRef ref="Console" />
        </Root>
    </Loggers>
</Configuration>
```

### level

日志级别，从低到高依次为：trace < debug < info < warn < error < fatal。

trace 最详细，fatal最简略，如果设置为warn，则低于warn的信息都不会输出。一般开发环境设置debug，生产环境设置info。

### Appender

日志输出目的地，这里配置了一个输出至控制台Console的Appender。

```xml
<Configuration status="WARN" monitorInterval="300">
    <Appenders>
        <Console name="Console" target="SYSTEM_OUT">
            <PatternLayout pattern="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
        </Console>
    </Appenders>
    <Loggers>
    	<Logger name="mylog" level="trace" additivity="false">
	    <AppenderRef ref="Console" />
	    </Logger>
        <Root level="error">
            <AppenderRef ref="Console" />
        </Root>
    </Loggers>
</Configuration>
```

Console节点中的PatternLayout定义了输出日志时的格式：

* %d{HH:mm:ss.SSS}
  
   表示输出到毫秒的时间
   
* %t
   输出当前线程名称

*  %-5level 
   输出日志级别，-5表示左对齐并且固定输出5个字符，如果不足在右边补0。

* %logger 
   输出logger名称，一般都在代码中设置为class的类名。

* %msg 
   日志文本

* %n 
   换行

其他常用的占位符有：

* %F
  输出所在的类文件名，如Client.java
  
* %L 
  输出行号
  
* %M 
  输出所在方法名
  
* %l 
  输出语句所在的行数, 包括类名、方法名、文件名、行数
### Logger

日志记录器，如下代码，设置一个名为mylog的日志记录器，在loggers配置项中读取到logger.name = "mylog"的记录，并应用相应配置项。

	public static void main(String[] args) {
		Logger logger = LogManager.getLogger("mylog");
		logger.trace("trace level");
		logger.debug("debug level");
		logger.info("info level");
		logger.warn("warn level");
		logger.error("error level");
		logger.fatal("fatal level");
	}


```xml

```

再次执行测试代码，这一次log4j2很高兴的找到了名称为mylog的配置，于是使用新配置把level改为trace，全部的信息都输出了。
additivity="false"表示在该logger中输出的日志不会再延伸到父层logger。这里如果改为true，则会延伸到Root Logger，遵循Root Logger的配置也输出一次。

注意根节点增加了一个monitorInterval属性，含义是每隔300秒重新读取配置文件，可以不重启应用的情况下修改配置，还是很好用的功能。
### 自定义Appender
修改配置文件，添加一个文件类型的Appender，并且把mylog的AppenderRef改为新加的Appender。

```xml
<Configuration status="WARN" monitorInterval="300">
	<Appenders>
		<Console name="Console" target="SYSTEM_OUT">
			<PatternLayout pattern="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
		</Console>
		<File name="MyFile" fileName="D:/logs/app.log">
			<PatternLayout pattern="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
		</File>
	</Appenders>
	<Loggers>
		<Logger name="mylog" level="trace" additivity="true">
			<AppenderRef ref="MyFile" />
		</Logger>
		<Root level="error">
			<AppenderRef ref="Console" />
		</Root>
	</Loggers>
</Configuration>
```
执行并查看控制台和D:/logs/app.log的输出结果。
### 配置最佳实践
下面配置一个按时间和文件大小滚动的RollingRandomAccessFile Appender，名字真是够长，但不光只是名字长，相比RollingFileAppender有很大的性能提升，官网宣称是20-200%。

Rolling的意思是当满足一定条件后，就重命名原日志文件用于备份，并从新生成一个新的日志文件。例如需求是每天生成一个日志文件，但是如果一天内的日志文件体积已经超过1G，就从新生成，两个条件满足一个即可。这在log4j 1.x原生功能中无法实现，在log4j2中就很简单了。

看下面的配置
```xml
<Configuration status="WARN" monitorInterval="300">
	<properties>
		<property name="LOG_HOME">D:/logs</property>
		<property name="FILE_NAME">mylog</property>
	</properties>
    
	<Appenders>
		<Console name="Console" target="SYSTEM_OUT">
			<PatternLayout pattern="%d{HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
		</Console>
		<RollingRandomAccessFile name="MyFile"
			fileName="${LOG_HOME}/${FILE_NAME}.log"
			filePattern="${LOG_HOME}/$${date:yyyy-MM}/${FILE_NAME}-%d{yyyy-MM-dd HH-mm}-%i.log">
			<PatternLayout
				pattern="%d{yyyy-MM-dd HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n" />
			<Policies>
				<TimeBasedTriggeringPolicy interval="1" />
				<SizeBasedTriggeringPolicy size="10 MB" />
			</Policies>
			<DefaultRolloverStrategy max="20" />
		</RollingRandomAccessFile>
	</Appenders>

	<Loggers>
		<Logger name="mylog" level="trace" additivity="false">
			<AppenderRef ref="MyFile" />
		</Logger>
		<Root level="error">
			<AppenderRef ref="Console" />
        </Root>
	</Loggers>
</Configuration>
```
properties：定义了两个常量方便复用与修改。
RollingRandomAccessFile的属性：
fileName：  指定当前日志文件的位置和文件名称
filePattern：  指定当发生Rolling时，文件的转移和重命名规则
SizeBasedTriggeringPolicy：  指定当文件体积大于size指定的值时，触发Rolling
DefaultRolloverStrategy：  指定最多保存的文件个数
TimeBasedTriggeringPolicy：  这个配置需要和filePattern结合使用，注意filePattern中配置的文件重命名规则是${FILE_NAME}-%d{yyyy-MM-dd HH-mm}-%i，最小的时间粒度是mm，即分钟，TimeBasedTriggeringPolicy指定的size是1，结合起来就是每1分钟生成一个新文件。如果改成%d{yyyy-MM-dd HH}，最小粒度为小时，则每一个小时生成一个文件。
修改测试代码，模拟文件体积超过10M和时间超过1分钟来验证结果

	public static void main(String[] args) {
		Logger logger = LogManager.getLogger("mylog");
		for(int i = 0; i < 50000; i++) {
			logger.trace("trace level");
			logger.debug("debug level");
			logger.info("info level");
			logger.warn("warn level");
			logger.error("error level");
			logger.fatal("fatal level");
		}
		try {
			Thread.sleep(1000 * 61);
		} catch (InterruptedException e) {}
		logger.trace("trace level");
		logger.debug("debug level");
		logger.info("info level");
		logger.warn("warn level");
		logger.error("error level");
		logger.fatal("fatal level");
	}
## 自定义配置文件位置
log4j2默认在classpath下查找配置文件，可以修改配置文件的位置。在非web项目中：

```java
public static void main(String[] args) throws IOException {
	File file = new File("D:/log4j2.xml");
	BufferedInputStream in = new BufferedInputStream(new FileInputStream(file));
	final ConfigurationSource source = new ConfigurationSource(in);
	Configurator.initialize(null, source);
	
	Logger logger = LogManager.getLogger("mylog");
}
```
如果是web项目，在web.xml中添加

```xml
<context-param>
		<param-name>log4jConfiguration</param-name>
		<param-value>/WEB-INF/conf/log4j2.xml</param-value>
</context-param>

<listener>
		<listener-class>org.apache.logging.log4j.web.Log4jServletContextListener</listener-class>
</listener>
```



