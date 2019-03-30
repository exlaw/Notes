#include <fcntl.h>
#include<stdio.h>
#include <zconf.h>
#include <iostream>
#include <sys/ioctl.h>

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
     *   1. 文件名   2. 打开方式   3. 权限
     *   返回： 文件描述符（是针对进程的）
     */

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

    cout << endl <<chdir("CMakeFiles");

    fclose(file);



    /**
     *  关闭文件， 正常是0，  异常是-1
     */
    int sig = close(fd);

 }


