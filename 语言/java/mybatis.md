1. 参数对应

   在接口中设置多个参数的，可以按照param1，param2等等的顺序进行引用。

2. mybatis-config相关配置

```xml
<properties resource="db.properties" />
    <settings>
        <setting name="logImpl" value="LOG4J" />
        <!--将sql语句输出到控制台-->
       <setting name="logImpl" value="STDOUT_LOGGING" />
    </settings>

```

3. resultMap

select语句返回数据库的字段名和entity的字段名通常是不一样的，可以通过resultMap来设置对应关系。

```xml
<resultMap type="org.pinming.entity.DataCheckResultsEntity" id="dataCheckResultsMap">
    <result property="checkId" column="check_id"/>
    <result property="ruleId" column="rule_id"/>
    <result property="checkTime" column="check_time"/>
    <result property="resultValue" column="result_value"/>
    <result property="resultType" column="result_type"/>
</resultMap>
```