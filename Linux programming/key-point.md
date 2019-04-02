# Linux 重点

每一个知识点都进行了评估，前面代表重要程度（考试概率），后面代表掌握的难易程度。 度量是 S, M, H。 

参照了体系结构中的评估方法（



##### 1.  linux 作者 (S, S)

Linux Torvalds

##### 2.Linux 发行版有哪些 (S, S)

Red Hat, Debain, SuSe, Mandrake, Redflag, Ubuntu。。。

##### 3. MBR 和 GPT 解析（单独拿出文件） (S, H)

关键是支持大小等不一样

##### 4. 文件系统和VFS的概念.   (H,H)

文件系统包含了一系列文件和他们的属性的集合，提供了一个对于文件的命名空间。 

严格地说，文件系统是一套实现了[数据](https://zh.wikipedia.org/wiki/%E6%95%B0%E6%8D%AE)的存储、分级组织、访问和获取等操作的[抽象数据类型](https://zh.wikipedia.org/wiki/%E6%8A%BD%E8%B1%A1%E6%95%B8%E6%93%9A%E9%A1%9E%E5%9E%8B)（Abstract data type）。

文件系统软件来负责将这些块组织为文件和目录，并记录哪些块被分配给了哪个文件，以及哪些块没有被使用。

VFS  对各个文件系统做出了统一的接口，对外提供本操作系统的文件库函数和系统调用等。  这个在后面单独讲。

##### 5. Linux 磁盘分区  (M,H)

`/boot`  分区

`/` 分区

##### 6. boot loader 引导程序（S，H）

加载和启动 Linux 内核

1. 可以 向 linux 内核传递参数
2. 可以选择性的加载初始化 root 硬盘
3. 也可以加载其他的操作系统

GRUB 存储在 boot loader 中的操作系统。

尤其注意安装双系统的时候 后安装的操作系统必须提供能够加载之前操作系统的引导程序才可能形成正确的双系统。

##### 7.  虚拟终端（S，M）

一台电脑只有一个console，但是可以划分出7个不同的虚拟终端。

 虚拟终端是 console 模拟出来的。

注： 关于此问题下的另一个可能概念 shell , shell 是核外软件模拟出来的，通过shell 的方式建立的终端应该不算是 虚拟终端。 所以 ssh 可以开十分多个。

##### 8. 基本命令（M，M）

`ls -l` 

文件类别， 权限（3种）, 链接数，拥有者，拥有者组，大小，最后修改时间，名称



`chomd <who operator what> filename`

Who:  u,g,o,a

Operator: +,-,==

What: r,x,w

或者采用数字方式： x = 1, w = 2, r = 3  对三种角色设置权限



`su` 切换用户，好像这个会很经常考

`passwd` 修改密码





##### 9. 文件类型 （M，H）

文件结构包含字节流、记录序列（Record Sequence）、记录树（Record Tree），Linux下文件为字节流。Linux中所有的目录均包含在一个统一的、虚拟的统一文件系统（Unified File System）中。物理设备被抽象为文件，挂载到指定的挂载点。没有Windows下的盘符的概念



- 普通文件（-）：纯文本文件、二进制文件、数据格式文件
- 字符设备文件（c, character）：与设备进行交互的文件。按字符进行I/O。如：终端文件（ttyN）
- 块设备文件（b, block）：同字符设备文件，但按块进行I/O。如：硬盘
- 套接字文件（s, socket）：表示一个socket连接。可以通过这个文件来与连接的对方（peer）进行通信。
- 管道文件/FIFO文件（p, pipe)：用于进程间通信。一个进程可以从这个文件中读取另一个进程此前写入的数据
- 符号链接文件（l, link）
- 目录文件（d, directory）



##### 10. 进程的概念（S，S）

进程是一个正在执行的程序实例。由执行程序、它的当前值、状态信息以及通过操作系
统管理此进程执行情况的资源组成。



##### 11. Linux 层次图（M，H）

就不在这里放了



##### 12. 重定向和管道 （H，H）非常可能考

已经单独写了一个文件说明



##### 13. 环境变量 (S,M)

- env：显示所有环境变量
- echo $VAR_NAME：显示某个变量的值
- set：显示本地定义的变量
- export：将用户变量（只在当前shell可见变量）输出为环境变量
- 常用环境变量
  - HOME：当前用户的家目录
  - PATH：可执行文件的搜索路径
  - TERM：终端的类型
  - UID：当前用户的UID
  - PWD：当前工作目录
  - PS1：主提示符
  - PS2：副提示符（换行）
  - IFS：输入区分隔符



##### 14. shell 是什么 （H，M）

**用户和操作系统之间的接口，作为核外程序而存在。** （这句话好像很常考，ppt上有两个图生动形象的说明这点）



##### 15. shell 例子 (S,M)

ash, bash, sh, csh, tcsh, ksh 。。。



##### 16.  shell 的双重角色（M，M）

命令提示符（调用者）  +     独立程序解释语言

1. 命令解释程序：打印提示符；得到命令行；解析命令；查找文件；准备参数；执行命令
2. 独立的程序设计语言解释器。



##### 17.  shell 脚本执行方式（H，M）

让 shell 来做的就不需要权限，自己运行的就要权限

1. `sh/bash/csh/some_bash script_file` **打开一个subshell**去读取、执行，脚本不需要有"**执行权限**"

2. `chmod +x script_file` **打开一个subshell**去读取、执行，需要有"**执行权限**"

   `./scirpt_file`

3. `source script_file`或`. script_file` 在**当前shell内**去读取、[执行a.sh](http://xn--a-g64b923i.sh/)，而a.sh不需要有"**执行权限**"



##### 18.  shell 中引号的用法和一些转义，参数扩展 （H，H）

* 单引号内的所有字符都保持它本身字符的意思，而不 会被bash进行解释，例如，\$ 就是 \$本身而不再是bash的变量引用符；\就是\本身而不再是bash的转义字符。

* 除了$、``（不是单引号）和\外，双引号内的所有字符将保持字符本身的含义而不被bash解释。
* 算数扩展： $(()) 进行算数运算,否则相加是字符串拼接



##### 19. shell 编程能力（H，H） 一定会考

* `read` 语法： read 变量名  直接写入变量名内
* boolean expression，`test` 或者 `[]` 语法
* `-eq`, `-ne`, `gt`,`ge`,`lt`,`le` 等表达式条件判断
* If 后加 fi,  case 后加 esac ，所有在 c 中需要大括号的这里用反字符转
* case ** in;   choice) ;;   choice) ;;  *);;
* for in 语法
* while do done 语法
* util do done 语法
* select 语法，自动生成菜单
* 函数用大括号的形式



##### 20.  编译流程 和 GCC 参数 （S，M）

###### 编译流程： 

源文件(.c/.cpp)–预处理–>纯C代码–编译(cc)–>汇编程序(.s)–汇编(as)–>目标文件(.o)–链接(ld)-(.a文件)->可执行文件

###### GCC 参数（只用于编译和链接）

- -E：只进行预处理
- -S：只进行预处理、编译
- -c：预处理、编译、汇编
- -o [output_file]：指定输出文件名
- -g：产生符号文件（可用于调试工具）
- -On：优化等价，n可以取0,1,2,3
- -Wall：显示所有警告信息
- -Idir：指定额外的头文件搜索路径
- -Ldir：指定额外的库文件搜索路径
- -lname：指定链接时搜索的库文件（name要去掉lib，如要链接pthread，pthread的静态库名为libpthread.a，则参数写成-lpthread）
- -D**MACROT**[=DEFN]：定义宏



##### 21. 静态库和动态库（M,M）

静态库：是指编译链接时，把库文件的代码全部加入到可执行文件中，因此生成的文件比较大，但在运行时也就不再需要库文件了。其后缀名一般为”.a”。

动态库：与之相反，在编译链接时并没有把库文件的代码加入到可执行文件中，而是在程序执行时由运行时链接文件加载库，这样可以节省系统的开销。动态库一般后缀名为”.so”，gcc/g++在编译时默认使用动态库。无论静态库，还是动态库，都是由.o文件创建的。



##### 22. 硬链接和软连接的区别（H，M）

- 软连接
  - 是确确实实存在的一个文件，有自己的inode号
  - 文件中存放被链接的文件的路径
  - 可以跨越文件系统
  - 对应系统调用symlink
- 硬链接
  - 与被链接的文件共享同一个inode，dentry不同
  - 不能跨越文件系统
  - 对应系统调用link



##### 23. 能够读懂 makefile (M，H)  可能会考

1. make会在当前目录下找名字叫“Makefile”或“makefile”的文件。
2. 如果找到，它会找文件中的第一个目标文件（target）。
3. 如果文件不存在，或是所依赖的后面的 .o 文件的文件修改时间要比这个文件新，那么，他就会执行后面所定义的命令来生成这个文件。
4. 如果edit所依赖的.o文件也存在，那么make会在当前文件中找目标为.o文件的依赖性，如果找到则再根据那一个规则生成.o文件。



##### 24.  虚拟文件系统 （H，H） 

虚拟： 只在内存中

组件：

* 超级块： 一个超级块对应一个文件系统
* i-node 对象： 索引节点。一个实际存在的文件实体只有一个inode。inode对象全系统共用。
* 文件对象： 文件对象。一个打开了的文件对应一个file。file中有指向dentry的指针。文件对象是进程私有的（会以copy-on-write的方式与子进程共享）。
* dentry 对象： 目录项。一个目录项对应一个dentry，就是ls -a列出来的每一项就是一个dentry。dentry中有指向inode的指针。多个dentry可以对应同一个inode。dentry对象全系统共用。



##### 25. 系统调用和库函数的区别 （H，M）

都以C函数的形式出现

系统调用：Linux内核的对外接口; 用户程序和内核之间唯一的接口; 提供最小接口

库函数：依赖于系统调用; 提供较复杂功能。例：标准I/O库



系统调用中没有实现标准的 缓存， 但是标准的IO实现了这一点，是有缓存的。



##### 26.  系统调用函数 （H，H） 每一个函数会再单独列一个优先级

* `open`, `close`, `creat`  肯定不会重点考  （S，S）
*  `dup`   `dup2`  要用到 （H,M） 很可能要写重定向. (H, M )
*  `read`  `write`  绝对会考 …  （H, M）
*  `Iseek` 优先级相对低  （M , H ）
*  `fcntl` 这个太难了，只会一个简单的把 （S，H）
* `ioctl` 更难…  不会考  （S, M ）



##### 27. 标准 IO 库  （H，H） 每个函数单独列优先级

* `fopen`, `fclose`  （S,S）
* `getc`, `fgetc`, `getchar` ,`putc`, `fputc`, `putchar`   (M,M)
* `fgets`, `gets` ,`fputs`, `puts`(M,M)
* `fread`, `fread` (M,M)
* `scanf`, `fscanf` , `sscanf`,`printf`, `fprintf` , `sprintf`   (M ,S)



##### 28.  文件夹操作 API   （M，H） 比较复杂，（最新消息，不考）

* `int stat(const char *filename, struct stat *buf);`

  `int fstat(int filedes, struct stat *buf);`

  `int lstat(const char *file_name, struct stat *buf);`

  （H， H）



* `int chdir(const char *path)`

  `char *getcwd(char *buf, size_t size);`

  `DIR *opendir(const char *name);`

  `struct dirent *readdir(DIR *dir)`

    (M, H)

##### 29   内核的定义 （M，S）

操作系统是一系列程序的集合，其中最重要的部分构成了内核，

Linux内核的能力: 内存管理，文件系统，进程管理，多线程支持，抢占式，多处理支持等。



##### 30. 内核驱动模块 （S， M）

1. 许多常见驱动的源代码集成在内核源码里
2.  也有第三方开发的驱动，可以单独编译成模块.ko
3.  编译需要内核头文件的支持



##### 31. 模块加载相关命令 （M， M）

底层命令

* insmod
*  rmmod

高层命令

*  modprobe
*  modprobe  -r  (有依赖功能)

模块的依赖
自动按需加载
自动按需卸载

* moddep
*  lsmod
*  modinfo



##### 32. 一些注意点（M，M）

- 不能用C库
- 没有内存保护
- 小内核栈
- 要考虑并发



##### 33. 遗漏点： 和重点命令实现相关的API （H，M）



###### 文件权限

**chmod()会依参数mode 权限来更改参数path 指定文件的权限。**

`int chmod(const char *path, mode_t mode);`



###### 软连接和硬链接

**硬链接建立**

`int link(const char *oldpath, const char *newpath);`

**去除链接（包括两种）**

`int unlink(const char *pathname);`

**软链接建立**

`int symlink(const char *oldpath, const char *newpath);`

**将参数path的符号连接内容存到参数buf所指的内存空间**

`int readlink(const char *path, char *buf, size_t bufsiz);`



###### 重定向

`int dup2(int odlfd, int newfd);`

`int dup(int oldfd);`



