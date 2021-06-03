# swagger

## maven依赖
```xml
<!-- Swagger2 Begin -->
<dependency>
 <groupId>io.springfox</groupId>
 <artifactId>springfox-swagger2</artifactId>
 <version>2.9.2</version>
</dependency>
<dependency>
 <groupId>io.springfox</groupId>
 <artifactId>springfox-swagger-ui</artifactId>
 <version>2.9.2</version>
</dependency>
<!-- Swagger2 End -->
```

## 配置swagger



创建一个名为 Swagger2Configuration 的 Java 配置类，代码如下：

```java
@Configuration
@EnableSwagger2 //启用 Swagger2
public class Swagger2Configuration {
    @Bean
    public Docket createRestApi() {
        return new Docket(DocumentationType.SWAGGER_2)
                .apiInfo(apiInfo())
                .select()
                .apis(RequestHandlerSelectors.basePackage("your.controller.package"))
                .paths(PathSelectors.any())
                .build();
    }

    private ApiInfo apiInfo() {
        return new ApiInfoBuilder()
                .title("MyShop API 文档") //接口名称
                .description("MyShop API 网关接口，http://www.funtl.com") //接口服务描述
                .termsOfServiceUrl("http://www.funtl.com")  //接口服务地址
                .version("1.0.0")
                .build();
    }

}
```

注意：basePackage("com.funtl.myshop.service") 为 Controller 包路径，不然生成的文档扫描不到接口。

## 访问swagger
http://localhost:8001/swagger-ui.html#/

## 配置注解

Swagger 常用注解说明
Swagger 通过注解表明该接口会生成文档，包括接口名、请求方法、参数、返回信息的等等。

常用注解
@Api：修饰整个类，描述 Controller 的作用
@ApiOperation：描述一个类的一个方法，或者说一个接口
@ApiParam：单个参数描述
@ApiModel：用对象来接收参数
@ApiProperty：用对象接收参数时，描述对象的一个字段
@ApiResponse：HTTP 响应其中 1 个描述
@ApiResponses：HTTP 响应整体描述
@ApiIgnore：使用该注解忽略这个API
@ApiError：发生错误返回的信息
@ApiImplicitParam：一个请求参数
@ApiImplicitParams：多个请求参数

@ApiModel
使用场景：在实体类上边使用，标记类时swagger的解析类。
概述：提供有关swagger模型的其它信息，类将在操作中用作类型时自动内省。

@ApiModelProperty
使用场景：使用在被 @ApiModel 注解的模型类的属性上。表示对model属性的说明或者数据操作更改 。
概述：添加和操作模型属性的数据。

