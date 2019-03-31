#include <fcntl.h>
#include<stdio.h>
#include <zconf.h>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

int main()
{
    /**
     *  读入缓冲定义
     */

    char buf[1024];
    char w_buf[] = {'a','s'};

    /**
     *   int open(const char *, int, ...)
//     *   1. 文件名   2. 打开方式   3. 权限
//     *   返回： 文件描述符（是针对进程的）
//     */
//
    int fd = open("../data", O_RDWR, S_IRUSR);

    /**
     *   lseek(int fildes, off_t offset, int whence);
     */

    off_t cur = lseek(fd, 2, SEEK_SET);

    /**
     *  ssize_t	read(int, void *, size_t)
     *  1. 文件描述符   2. 读入位置   3. 目标读入大小
     *  返回值， 实际读入大小。  出现异常就是 返回 -1
     */
    long r_count = read(fd, buf, 1024);

    /**
     *  ssize_t	 write(int __fd, const void * __buf, size_t __nbyte)
     *  1. 文件描述符     2. 写入的内容    3.   写入的大小（自己控制，不会自己停止）
     *  返回值： 实际写入的大小
     */
    long w_count = write(fd, w_buf, 2);


    int dup_fd;
    /**
     *  dup 出的文件描述符 会是完全相同的，所有的操作都会进行共享
     */
    dup_fd = dup(fd);

    /**
     *  和 dup 操作的区别是可以指定，先关闭后重新打开
     */
    int dp = dup2(fd, dup_fd);

    /**
     *  fcntl 感觉比较复杂，应该不会直接去考
     *  int fcntl(int fd, int cmd);
     *  fd: 文件描述符
     *  cmd:{
     *  F_DUPFD: 复制文件描述符
     *  F_GETFD:
     *  F_SETFD：
     *  F_GETFL
     *  F_SETFL:
     *  其他都是文件锁相关内容比较多
     *  }
     */
    int fc = fcntl(fd, F_GETFD);

    /**
     *  这是一个系统调用， 实现起来也比较麻烦，感觉也不会直接去考
     *  int	ioctl(int, unsigned long, ...);
     */


    /**
     *  下面系统库函数 API 部分
     *  getChar() 需求重载 stdin
     */
    FILE* file = fopen("../data","r+");

    int temp;
    while ((temp = getc(file)) != EOF) {
        if (putc(temp, stdout) == EOF)
        {
            break;
        }
    }

    char s[1024];
    while(fgets (s, 1024, file) !=NULL ) {
        if(s[0] == '\n'){
            cout << "???" << endl;
        }
        fputs(s, stdout);
    }

    char f_buf[1024];


    while (1)
    {
        memset(buf, 0, sizeof(buf));
        size_t rc = fread(f_buf, sizeof(char), sizeof(buf), file);
        if (rc <= 0)
            break;
        fwrite(f_buf, 1, rc,  stdout);
    }



    int a;
    scanf("%d", &a);
    sscanf("12123","%d", &a);

    ftell(file);

    fpos_t position = 1;
    fgetpos(file, &position);

    fflush(file);

    int n = fileno(file);

    FILE* another = fdopen(n, "w");

    /**
     *  产生临时文件
     */
    FILE* tmp_file = tmpfile();

    /**
     *  一系列文件夹操作测试
     */
    DIR* dir = opendir("CMAKeFiles");

    cout << mkdir("test", S_IRWXU) << endl;

    char global_pwd[1024];

    cout << getcwd(global_pwd, sizeof(global_pwd)) << " " << global_pwd << endl;

    cout <<  chdir("test") << endl;

    cout << getcwd(global_pwd, sizeof(global_pwd)) << " " << global_pwd << endl;

    cout <<  fchdir(dir->__dd_fd) << endl;

    cout << getcwd(global_pwd, sizeof(global_pwd)) << " " << global_pwd << endl;

    chdir("..");

    cout << rmdir("test") << endl;

    /**
     *  三个 API， 几类对象一定要弄清
     */
    dir = opendir("CMAKeFiles");
    struct dirent *entry;
    while ( (entry = readdir(dir)) != NULL ) {
        struct stat info{};
        lstat(entry->d_name, &info);
        if ( S_ISDIR(info.st_mode) ){
            cout << "dir";
        }
        else{
            cout << "not";
        }
    }

    /**
     *  后面的文件锁操作还是  fcntl 里面的
     *
     */

    /**
     *  Linux 文件中的锁
     *  首先是共享锁和排他锁之间的关系，只有共享锁可以相互进行共享
     *  劝告锁，不能主动阻拦，需要去检查判断。
     *  强制锁，被锁住的文件在其他文件访问时会被强制阻拦
     *  记录锁， 用于锁住文件的某个部分。
     *
     *  Linux 锁用的API 还是 fcntl 和 flock
     */



    fclose(file);


    /**
     *  关闭文件， 正常是0，  异常是-1
     */
    int sig = close(fd);

 }


