
## mybatis-config配置

```xml
<properties resource="db.properties" />
    <settings>
       <setting name="logImpl" value="LOG4J" />
       <!--将sql语句输出到控制台-->
       <setting name="logImpl" value="STDOUT_LOGGING" />
    </settings>
</properties>
```

## resultMap

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

## 传参

### 参数对应

在接口中设置多个参数的，可以按照param1，param2等等的顺序进行引用。

## like匹配

1. 使用like语法

   参数传入%param%的形式，需要在传参数时，手动加入%%。

2. 使用concat

   ```sql
   CONCAT('%',#{name},'%') 
   ```

使用concat来拼接字符串(mysql),如果是Oracle的话就是||。

# resultType

## hashmap

当返回的结果列的值是null时，mybatis不会将该列写入hashmap对象中