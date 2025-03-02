# Linux
## 常用命令
### cd:切换工作目录
```sh
cd /home/user/Documents  # 切换到绝对路径目录
cd ..                    # 切换到上一级目录
cd ~                     # 切换到当前用户的主目录
```
### pwd:显示工作目录
```sh
pwd
# 输出: /home/user/Documents
```
### tree:列出树状文件目录结构  
### ls:列出目录内容
```sh
ls              # 列出当前目录内容
ls -l           # 列出详细信息（如权限、大小、修改日期）
ls -a           # 显示所有文件，包括隐藏文件（以 . 开头的文件）
```
### cp:复制
```sh
cp file1.txt file2.txt      # 将 file1.txt 复制到 file2.txt
# 123 abc -> 123 123
cp -r dir1 dir2             # 递归地复制目录 dir1 到 dir2
```
### mv:移动或重命名
```sh
mv file1.txt dir/           # 将 file1.txt 移动到 dir 目录
mv oldname.txt newname.txt  # 重命名文件 oldname.txt 为 newname.txt
```
### rm:删除
```sh
rm file1.txt file2.txt       # 删除 file1.txt file2.txt
rm -r dir                    # 删除目录及其内容
rm -f file2.txt              # 强制删除文件，不显示警告
```
### cat:查看
```sh
cat file1.txt        # 显示 file1.txt 的内容
cat file1.txt file2.txt  # 连接多个文件并显示它们的内容
```
### mkdir:新建文件夹
```sh
mkdir newdirectory   # 新建名为newdirectory的文件夹 
```
### touch:新建文件
```sh
touch main.c         # 新建main.c文件
``` 
### head/tail: 查看文件的开始/结尾部分
```sh
head file1.txt       # 显示 file1.txt 的前10行
tail file1.txt       # 显示 file1.txt 的最后10行
tail -n 20 file1.txt # 显示 file1.txt 的最后20行
```
### less/more: 分页显示文件内容
```sh
less file1.txt   # 分页显示 file1.txt 内容 q退出
more file1.txt   # 以单页模式显示 file1.txt 内容 使用'⬇'翻页
```
### eog/display:查看图片
```sh
eog/display image.png     # 打开 image.png 图片
```
### vim:编辑文件
```sh
vim file1.txt         # 使用 vim 打开 file1.txt 进行编辑
vim +20 file1.txt     # 打开 file1.txt 并定位到第20行
```
```sh
In vim:
:wq  # 保存并退出
:w   # 保存但不退出
:q!  # 强制退出而不保存
```
### find:查找文件
```sh
find . -name "*.txt"     # 查找当前目录及其子目录下所有扩展名为 .txt 的文件
find ~/notebook/ -type d # 查找 /home/user 下的所有目录
/home/tapir_elithril/notebook/
/home/tapir_elithril/notebook/.github
/home/tapir_elithril/notebook/.github/.DS_Store
/home/tapir_elithril/notebook/.github/workflows
/home/tapir_elithril/notebook/docs
...
```
### chmod:修改文件权限
```sh
chmod 755 file1.sh        # 设置 file1.sh 文件为可执行，并设置权限为 rwxr-xr-x
# 二进制表示法r=4,w=2,x=1
chmod +x file1.sh         # 给 file1.sh 文件添加可执行权限
chmod -R 755 /path/to/dir # 递归地为目录及其所有子文件设置权限
```
### grep:搜索文件中的内容
```sh
grep "hello" file1.txt         # 查找 file1.txt 中包含 "hello" 的行
grep -r "hello" /home/user     # 在 /home/user 目录下递归查找 "hello"
```
### sort:排序文件内容
```sh
sort file1.txt        # 对 file1.txt 中的行进行字典顺序排序
sort -r file1.txt     # 反向排序
sort -n file1.txt     # 按数字大小排序
```
### tar:打包和解包文件
```sh
tar -cvf archive.tar file1.txt file2.txt  # 将file1.txt file2.txt压缩为archive.tar
tar -xvf archive.tar                      # 解压 archive.tar
tar -czvf archive.tar.gz dir/             # 创建压缩的 tar.gz 归档
tar -xzvf archive.tar.gz                  # 解压 tar.gz 归档文件
```
### kill:终止进程
```sh
kill 1234                # 终止进程号为 1234 的进程
kill -9 1234             # 强制终止进程号为 1234 的进程（SIGKILL）
```