# git手册

git是Linus Torvalds编写的一个代码版本管理工具，最初用于支持linux内核开发。他具有以下特点：

* 快速
* 设计简单
* 分布式
* 支持数以千计的分支
* 能有效地支持大型项目：比如Linux内核开发
* 大多数操作本地化

和其他版本管理工具不同，git是以快照的方式存储文件的。这意味着，如果文件发生了数次变化，那么git会存储它的每个版本的快照。

## git的结构

git分为3个区域，工作区，暂存区，版本区。

* 工作区

working area，是进行代码编辑的地方。

* 暂存区

临时保存预计提交的代码，是个过渡区。

* 版本区

是保存已提交代码的地方。

## 安装

```shell
$ sudo apt install git-all
$ git --version
```

### 配置git

```shell
git config --global core.editor=vi
git config --global user.name=peter
git config --global user.email=yeyoung0909@163.com
# 列出配置
git config --list
```

### 初始化目录

```shell
git init
```

对目录进行初始化，使得git托管这里面的数据。

## 提交代码

1. git add

```shell
git add .
```

add命令用于将工作区的变动增加到暂存区。

2. git status

```shell
git status
```

status命令用于查看仓库中的三个区的文件变更情况。

3. git ignore

有些临时文件，或者非代码文件是不需要进行代码管理的。在仓库的根目录下，通过设置.gitignore文件来过滤。

```shell
$ cat .gitignore
*.[oa]
*~
**/*.out # **表示任意多个目录，*表示通配任意文件名
```

4. git commit

```shell
git commit -a -m "a commit" 

```



1. 
2. git commit
  git commit --amend
3. git branch
  git branch bugFix --创建分支
  git checkout bugFix -- 切换到bugFix分支
4. git merge
  融合，将两个分支融合成一个新的提交点。这个提交点有两个双亲。



4.git rebase
rebase不会引入新的提交点，使开发历史更线性。
rebase 意为以某个commit为基准，把当前分支合并上去。
git rebase -i（交互模式） HEAD^ -- 整理上一个提交
pick 取
omit 舍弃

设当前分支为bugFix
git rebase master 

5 git 引用
HEAD 指向当前分支头部
^ 向上移动一格
~n,向前移动n格

git branch -f master HEAD~3 --强制master分支指向head的前3个提交点。


cat .git/HEAD


6 git log
查看提交历史


7. git reset -- 反悔1
git reset 通过将分支回撤几个提交来取消更改。
git reset HEAD^1 -- 将当前分支回退到上一个提交点。

8. git revert -- 反悔2，reset是自己玩，revert可以分享给别人。
git revert 会通过引入一个新的提交点的方式回退至指定点。
git revert 之后可以推送至远程仓库，分享“回退”。


9 git cherry-pick
用于整理提交记录。
git cherry-pick 提交号


10 git tag
标签，相比于随意移动的分支，是一个比较固定的版本锚，标识了某个固定的位置。常用于标记固定的版本。
git tag <tag_name> <commit>

11.git describe
用法： git describe <ref>某个提交的引用或者hash值 ，用于查找当前分支最近的标签，以及和它的差距。
输出格式：<tag>_<numCommits>_g<hash>

================================

====git 远程提交======

1.git clone
git clone <url>
拷贝远程的代码。远程分支的命名规格:<remote>/<local>.


2.git fetch
git fetch http://|git:// xxx.获取与远程仓库的差异代码。

*****注意*********
git fetch 不会做的事
git fetch 并不会改变你本地仓库的状态。它不会更新你的 master 分支，也不会修改你磁盘上的文件。

理解这一点很重要，因为许多开发人员误以为执行了 git fetch 以后，他们本地仓库就与远程仓库同步了。它可能已经将进行这一操作所需的所有数据都下载了下来，
但是并没有修改你本地的文件。

所以, 你可以将 git fetch 的理解为单纯的下载操作

3.git pull
拉取并融合远程仓库的分支

git pull == git fetch && git merge
git pull --rebase,可以先获取并合并远程的改动，并提交本地分支的commit

4.git push
-









# 中文乱码设置

git config --global core.quotepath false   # core.quotepath设为false的话，就不会对0x80以上的字符进行quote。中文显示正常。

git config --global gui.encoding utf-8  图形界面编码

git config --global i18n.commit.encoding utf-8  提交信息编码

git config --global i18n.logoutputencoding utf-8  输出 log 编码

1git status
查看当前分支工作区的情况，包括与远程分支的差异情况。
git status
位于分支 数据仓库
您的分支与上游分支 'origin/数据仓库' 一致。

无文件要提交，干净的工作区


# 设置gitignore
可以通过设置gitignore来忽略一些文件。比如一些临时文件，通常是～开头的。

vi .gitignore

# 忽略word的临时文件
.~*

配置语法：
以斜杠“/”开头表示目录；
以星号“*”通配多个字符；
以问号“?”通配单个字符
以方括号“[]”包含单个字符的匹配列表；
以叹号“!”表示不忽略(跟踪)匹配到的文件或目录；
