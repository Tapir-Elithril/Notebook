# Git
## Introduction
Git 是一个分布式版本控制系统，用于跟踪文件的变化，常用于软件开发中管理代码，主要功能包括版本控制、协作开发和代码备份  
## Github & Gitlab
Github:基于 Git 的代码托管平台，提供远程仓库存储和协作开发功能，主要功能包括远程代码托管、协作开发、代码审查、自动化、社区和开源项目托管  
Gitlab:基于 Git 的 DevOps 平台，除了代码托管外，还提供完整的 DevOps 工具链，适合企业级 DevOps 流程、私有化部署、团队协作  
    DevOps:Development(开发)and Operation(运维)  
## Concepts
1.Repository:仓库是 Git 存储项目的地方，包含项目的所有文件和历史记录。仓库可以是本地的，也可以是远程的（如 GitHub、GitLab 等）  
2.Commit:提交是 Git 中的基本操作，用于保存文件的当前状态。每次提交都会生成一个唯一的哈希值，记录文件的更改信息、作者和时间戳  
3.Branch:分支是项目的独立开发线。默认分支通常称为 main 或 master。开发者可以创建新分支来开发新功能或修复问题，而不会影响主分支  
4.Merge:合并是将一个分支的更改整合到另一个分支的操作。例如，将功能分支合并到主分支  
5.Pull:拉取是从远程仓库获取最新更改并合并到本地分支的操作  
6.Push:推送是将本地分支的更改上传到远程仓库的操作  
7.Clone:克隆是从远程仓库复制整个项目到本地的操作  
8.Staging Area:暂存区是提交前的中间区域，开发者可以选择哪些更改需要提交  
## 命令
### Repository creation
```bash
git init  
git add README.md  
git commit -m "<update_info>"
git branch -M <branch_name>  
git remote add origin <website.git>
git push -u origin main
```
### Repository contribution
```bash
git add .
git commit -m "<update_info>"  
git push origin <branch_name>  
```
### Status
```bash
git status #查看目录与暂存区状态
git log #查看历史
git log --oneline #查看简约历史
git log -p #查看详细历史
git log --graph #查看提交历史分支图
git show <commit_hash> #查看某次提交详细信息
git blame <file> #查看某一文件是谁提交的修改
```
### Branch
``` bash
git branch #查看本地分支
git branch -a #查看所有分支
git branch -r #查看远程分支
git branch -d <branch_name> #删除本地分支
git branch -D <branch_name> #强制删除本地分支（即使未合并）
git push origin --delete <branch_name> #删除远程分支
git fetch --all #获取所有远程分支的更新
git merge --no-ff <branch> #合并分支并保留记录
git checkout -b <branch_name> #创建分支并切换
git checkout master #回到master分支
git diff <branch_name> master #显示某分支与主分支的差别
```
### Remote 远程仓库
```bash
git remote -v #查看地址
git remote show origin #查看详细信息
git fetch origin #获取更新（不合并）
git pull --rebase #拉取更新并变基（避免合并提交）
git remote prune origin #清理本地已删除的远程分支
```
### Clone
```bash
git clone -b <branch_name><repo_url> #克隆某url的某分支
git checkout -b <branch_name> origin/<branch_name> #关联分支
```
### Clear
```bash
git rm --cached <file> #将已add未commit的文件退回未add状态
git checkout -- <file> #撤销已修改文件的修改
git reset soft --HEAD^ #撤销commit但不更改文件
git reset hard --HEAD^ #撤销commit且将文件退回上一版本
git push -f #强制推送，覆盖commit
```
### Reset
```bash
git checkout -- <file>	#撤销工作区的修改
git reset HEAD <file>	#将文件从暂存区撤回到工作区
git revert <commit_hash>	#创建一个新的提交来撤销某次提交
git stash	#将当前修改暂存起来
git stash pop	#恢复最近一次暂存的修改
git stash list	#查看所有暂存的修改
git stash drop	#删除最近一次暂存的修改
```
### Submodule
```bash
git submodule add <repo_url>	#添加子模块
git submodule init	#初始化子模块
git submodule update	#更新子模块
git submodule foreach <cmd>	#对每个子模块执行命令
```
### Config
```bash
git config --list	#查看 Git 配置
git config --global user.name "name"	#设置全局用户名
git config --global user.email "email"	#设置全局邮箱
git config --global alias.<alias> <command>	#设置命令别名
git config --global core.editor "vim"	#设置默认编辑器
```

参考 https://note.tonycrane.cc/cs/tools/git/