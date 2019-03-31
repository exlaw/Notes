# 关于重定向操作和管道

## 重定向

 **重定向操作在底层的本质上就是调用了 dup2() 函数， 把进程的文件描述符进行拷贝和覆盖。**



#### 一般情况下，每个 Unix/Linux 命令运行时都会打开三个文件：

标准输入文件(stdin)：stdin的文件描述符为0，Unix程序默认从stdin读取数据。
标准输出文件(stdout)：stdout 的文件描述符为1，Unix程序默认向stdout输出数据。
标准错误文件(stderr)：stderr的文件描述符为2，Unix程序会向stderr流中写入错误信息。



1. 默认情况下，command > file 将 stdout 重定向到 file，command< file 将stdin 重定向到 file。
2. 如果希望 stderr 重定向到 file，可以这样写：command 2 > file
3. 如果希望 stderr 追加到 file 文件末尾，可以这样写：command 2 >> file   ;2 表示标准错误文件(stderr)。
4. 如果希望将 stdout 和 stderr 合并后重定向到 file，可以这样写：command > file 2>&1  或command >> file 2>&1,为什么需要将标准错误重定向到标准输出的原因，那就归结为标准错误没有缓冲区，而stdout有。
5. 如果希望对 stdin 和 stdout 都重定向，可以这样写：command < file1 >file2  ;command 命令将stdin重定向到 file1,将stdout重定向到file2。



**牢记本质上就是 一些列 顺序执行的 dup2 命令**



## 管道

**管道操作的本质是把上一个操作的标注输出作为本操作的标注输入**

**上一个操作的标注输出指的是上一个命令在一系列重定向操作之后的仍然会输出到 标准输出的 文件描述符**



嗯，基本的思想就是上面这样了，非常简单。

有一个十分重要的命令是 xargs



**xargs 的出现的原因是很多命令并不是从标准输入读入的，而是使用命令行参数的形式**

**xargs 就是可以把 标准输入的内容变成命令行参数**



**xargs 读入标准输入，以空格或者换行作为分隔 区分参数。 然后放到后面的命令中**

**因为很多命令都是支持同时批量输入参数的，如果是不支持的，也可以设置每次输入进几个参数**