##open函数详解
###介绍
open函数用来打开或创建一个文件，如果成功则返回一个文件描述符fd。
**定义**
```
#include <fcntl.h>      // 用于 open 函数  
#include <sys/types.h>  // 用于 mode_t，pid_t和 size_t 类型 
#include <sys/stat.h>   // 用于文件权限常量

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```
**函数参数**
* pathname：打开文件的路径名。
* flags：用来选择打开文件的方式。
* mode：用来设置创建文件的权限（rwx），当flags中带有O_CREAT时才有效。

**返回值**
* 成功时，返回一个非负整数，即文件描述符。
* 失败时，返回 -1，并设置 errno 变量以指示错误原因。

**flags参数详解**
* O_RDONLY：以只读方式打开文件。
* O_WRONLY：以只写方式打开文件。
* O_RDWR：以读写方式打开文件。

以上三种标志不可同时使用，但可与以下标志利用OR(|)运算符组合。
* O_APPEND：以追加模式打开文件。即每次写文件时都会先将当前文件偏移量设置到文件末尾，但是读文件时不影响。
* O_CREAT：如果指定文件不存在则创建。
* O_EXCL：如果要创建的文件已存在，则出错，返回 -1 并且修改 errno 的值。须搭配O_CREAT参数一起使用，这是一个用于防止意外覆盖的安全机制。
* O_TRUNC：表示截断，如果文件存在，且以只写、读写方式打开，则将其长度截断为 0，即清空内容。
* O_NOCTTY：如果打开的文件是终端设备，则不将此设备设置为进程的控制终端。
* O_NONBLOCK：如果打开的是一个管道/块文件/字符文件，则把文件的打开和后继 I/O设置为非阻塞模式。

以下三个常量同样是选用的，它们用于同步输入输出。
* O_DSYNC：等待物理 I/O 后再写入。在不影响读取新写入的数据的前提下，不等待文件属性更新。
* O_RSYNC ：等待所有写入同一区域的写操作完成后再读取。
* O_SYNC：等待文件属性的更新和物理 I/O 结束后再写入。





###范例

```
/*
    创建命令行参数输入名字的文件
    存储用户输入的学生姓名年龄和成绩
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct Student
{
    char name[25];
    int age;
    double score;
} stu = {"司徒寇", 25, 59.99};

int main(int argc, char *argv[]) // 程序的入口点，接受命令行参数。
{
    if (argc < 2)
    {
        printf("请命令行输入文件名!\n");
        exit(-1); // 结束当前进程
    }

    int fd;
    fd = open(argv[1], O_WRONLY); // 写入模式
    if (-1 == fd)                 // 文件不存在
    {
        printf("打开%s失败:%m\n", argv[1]); // %m->失败原因
        printf("尝试创建文件!\n");
        fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
        if (-1 == fd)
        {
            printf("创建%s失败!失败原因:%m\n", argv[1]);
            exit(-1);
        }
        printf("创建文件成功!\n");
    }
    printf("打开文件成功!\n");
    printf("%s - %d - %g\n", stu.name, stu.age, stu.score);

#if 0
	write(fd,(const char*)&stu,sizeof(stu));
#else
    write(fd, stu.name, sizeof(stu.name));
    write(fd, (const char *)&(stu.age), sizeof(stu.age));
    write(fd, (const char *)&(stu.score), sizeof(stu.score));
#endif
    printf("over!\n");
    close(fd);
}
```

**在终端执行以下操作：**

![](https://img2024.cnblogs.com/blog/3504708/202408/3504708-20240817173133624-924972349.png)
第一次执行结果：
![](https://img2024.cnblogs.com/blog/3504708/202408/3504708-20240817173231979-1829151741.png)
第二次执行结果：
![](https://img2024.cnblogs.com/blog/3504708/202408/3504708-20240817173322647-1023372513.png)
