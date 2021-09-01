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

## 1 安装

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

## 2 提交

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
git commit --amend # 修改上一个提交的信息
```

## 3 分支

### 3.1 git branch

分支是git的核心特性。

```shell
# 创建分支
git branch bugFix 
git checkout bugFix 
git checkout -b bugFix  # 创建并切换分支

# 查询分支
git branch
git branch -v # 显示详细信息
```

### 3.2 git merge
2.1 merge

将两个分支融合成一个新的提交点，这个提交点有双亲。

   ```shell
   $ git merge test
   Merge made by the 'recursive' strategy.
    a.txt | 0
    1 file changed, 0 insertions(+), 0 deletions(-)
    create mode 100644 a.txt
   ```

2.2 冲突处理

当两个分支同时改动一个文件，merge时，会产生冲突。

```shell
$ git merge test
自动合并 a.txt
冲突（内容）：合并冲突于 a.txt
自动合并失败，修正冲突然后提交修正的结果。

$ git status
位于分支 master
您的分支领先 'origin/master' 共 10 个提交。
  （使用 "git push" 来发布您的本地提交）

您有尚未合并的路径。
  （解决冲突并运行 "git commit"）
  （使用 "git merge --abort" 终止合并）

未合并的路径：
  （使用 "git add <文件>..." 标记解决方案）

	双方修改：   a.txt

修改尚未加入提交（使用 "git add" 和/或 "git commit -a"）

$ cat a.txt
<<<<<<< HEAD
line1 add by master
=======

line2 add by branch test.
>>>>>>> test
```

说明：

以=======为分界，<<<<<<< HEAD为你当前所在分支，>>>>>>> test为要合并分支的相应内容。根据实际情况，合并代码，去除<<<<< ===== >>>>>这些标记，然后提交代码，冲突处理完毕。

```shell
$ vi a.txt

# 代码合并如下
$ cat a.txt 
line1 add by master
line2 add by branch test.

$ git add . && git commit -a

# 终止merge
# 无法处理好冲突时，可以终止merge
$ git merge --abort
```



### 3.3 git rebase
   rebase不会引入新的提交点，使开发历史更线性。
   rebase 意为以某个commit为基准，把当前分支合并上去。
   git rebase -i（交互模式） HEAD^ -- 整理上一个提交
   pick 取
   omit 舍弃

设当前分支为bugFix
git rebase master 

## 4 tag

相比于随意移动的分支，标签是一个固定的版本锚，标识了某个固定的位置，常用于标记稳定的发行版本。

```shell
# -a 创建
$ git tag -a "v1.0" cd95b7 -m "stable version"
# -d 删除
$ git tag -d test
```

## 5 git ref
git引用，HEAD 指向当前分支头部：
   ^ ，向前移动一格
   ~n，向前移动n格

```shell
# 强制master分支指向head的前3个提交点。
git branch -f master HEAD~3 --
cat .git/HEAD
```

## 6 log
git log，查看提交历史。


## 7 reset 
反悔1，git reset 通过将分支回撤几个提交来取消更改。

```shell
# 回退到上一个提交点。
git reset HEAD^1 

# 取消index区的a.txt文件，相应于undo add
git reset HEAD a.txt

# 从版本区检出某个文件，会覆盖工作区
git checkout -- Rakefile

```

reset有三种模式：

* soft

只改变版本区。

```shell
git reset --soft HEAD～
```

上述命令运行后，工作区和暂存区并未改变。

* mixed

mixed是reset的默认模式，在soft的基础上，继续回退暂存区，让暂存区和版本区一致，相当于undo add。

* hard

在mixed的基础上，继续回退工作区。这是一个**危险**的动作，因为会覆盖你已经修改的文件。如果你未曾提交过此数据的话，意味着这次覆盖是不可恢复的。

## 8 revert

反悔2，reset是自己玩，revert可以分享给别人。
git revert 会通过引入一个新的提交点的方式回退至指定点。
git revert 之后可以推送至远程仓库，分享“回退”。

## 9 git remote

git可以让本地和远程分支保持联系，并共享变更。

```shell
# 跟踪远程master分支(最新的默认分支是main)
git remote add -t master -m master origin https://github.com/peeyee/algorithm.git

# 跟踪远程分支
git branch --set-upstream-to=origin/main_hebi main_hebi

# 删除远程分支
git push origin --delete serverfix
```

### 9.1 git clone

git clone <url>
拷贝远程的代码。远程分支的命名规格:<remote>/<local>.

### 9.2 git fetch
git fetch <url>获取与远程仓库的差异代码。

**注意**
git fetch 是单纯的下载操作，并不会改变你本地仓库的状态。它不会更新你的 master 分支，也不会修改你磁盘上的件。

### 9.3 git pull
拉取并融合远程仓库的分支
git pull == git fetch && git merge
git pull --rebase,可以先获取并合并远程的改动，并提交本地分支的commit

### 9.4 git push
提交当前分支的改动至远程分支。



## 10 其他

* cherry-pick

* git describe
  用法： git describe <ref>某个提交的引用或者hash值 ，用于查找当前分支最近的标签，以及和它的差距。
  输出格式：<tag>_<numCommits>_g<hash>



## 中文设置

```shell
# 显示中文
git config --global core.quotepath false   
# 图形界面编码 
git config --global gui.encoding utf-8  
# 提交信息编码
git config --global i18n.commit.encoding utf-8 
# 输出 log 编码
git config --global i18n.logoutputencoding utf-8  
```


# 设置gitignore
可以通过设置gitignore来忽略一些文件。比如一些临时文件，通常是～开头的。

vi .gitignore

```shell
# 忽略以下文件
.~* # word的临时文件
/target # target目录
/**/target # 所有的target目录
*.[oa] # 以o或者a结尾的文件
```

配置语法：
以斜杠“/”开头表示目录；
以星号“*”通配多个字符；
以问号“?”通配单个字符；
以方括号“[]”包含单个字符的匹配列表；
以叹号“!”表示不忽略(跟踪)匹配到的文件或目录；

# github

github是一个internet的代码仓库，提供代码托管和多人项目协作。可以通过

[hello-world](https://guides.github.com/activities/hello-world/)项目来熟悉github的相关操作。

