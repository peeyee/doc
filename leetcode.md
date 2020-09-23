# leetcode

力扣（[LeetCode](https://baike.baidu.com/item/LeetCode/49851003)）是领扣网络旗下专注于程序员技术成长和企业技术人才服务的品牌。源自美国硅谷，力扣为全球程序员提供了专业的IT 技术职业化提升平台，有效帮助[程序员](https://baike.baidu.com/item/程序员/62748)实现快速进步和长期成长。

## leetcode账号

yeyoung0909@163.com/star0702

## idea刷leetcode

在plugin->market搜索leetcode，安装后重启，在右侧栏有相应的leetcode图标。并配置本地测试环境，

在TempFilePath中填入项目的source根目录.

codefilename: $!velocityTool.camelCaseName(${question.titleSlug})

codetemplate: 

${question.content}
package leetcode.editor.cn;
public class $!velocityTool.camelCaseName(${question.titleSlug}) {
    public static void main(String[] args) {
        Solution solution = new $!velocityTool.camelCaseName(${question.titleSlug})().new Solution();
    }
    ${question.code}
}

本地调试环境就配置完成了。

在提交代码时，需删除或注释main方法。

