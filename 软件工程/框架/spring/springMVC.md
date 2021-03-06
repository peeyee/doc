# SpringMVC

springMVC是在Spring框架的基础上，构建web应用的框架。



@controller 表明类是一个控制器，控制请求的响应方式。

## MVC的设计思想

M: model，即数据，有一定组织形式的数据。数据包含着我们业务的各种信息。

V:  View，视图，展现给用户的页面。

C：controller，控制器。根据用户的请求来相应的处理model。

在mvc中，早期的web 是 model+ Controller的形式，controller，通常是jsp，包含了业务处理逻辑和视图渲染。后来将jsp的功能进行了拆分，把处理逻辑和视图渲染两个功能分为2个独立的组件。这样就更容易应对变化，视图变动了，不用改动整个处理逻辑，处理逻辑层的代码重用性会提高。这给了我们一种启示：

​      **内部高聚合**，组合在一起的功能，一定是关联性高的，不能进一步拆分的。如果关系不紧密的东西组合在一起，在应对需求变化的时候不可避免地增加了改动的复杂性。

