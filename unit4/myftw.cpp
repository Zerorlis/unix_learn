#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "../myerror.h"
using namespace std;

enum { FTW_F, FTW_D, FTW_DNR, FTW_NS };

typedef int Myfunc(const char*, const struct stat*, int);

Myfunc myfunc;
int myftw(char*, Myfunc*);
long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
int dopath(Myfunc*);
int main(int argc, char* argv[]) {
    int ret;
    if (argc != 2) err_quit("usage: ftw <statring-pathname>");
    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0) ntot = 1;
    cout << "regular files = " << setw(20) << nreg << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nreg * 100.0 / ntot << endl;
    cout << "directory     = " << setw(20) << ndir << " ," << setprecision(5)
         << setiosflags(ios::fixed) << ndir * 100.0 / ntot << endl;
    cout << "block special = " << setw(20) << nblk << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nblk * 100.0 / ntot << endl;
    cout << "char special  = " << setw(20) << nchr << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nchr * 100.0 / ntot << endl;
    cout << "FIFOs         = " << setw(20) << nfifo << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nfifo * 100.0 / ntot << endl;
    cout << "symbolic links= " << setw(20) << nslink << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nslink * 100.0 / ntot << endl;
    cout << "sockets       = " << setw(20) << nsock << " ," << setprecision(5)
         << setiosflags(ios::fixed) << nsock * 100.0 / ntot << endl;
    return ret;
}

static char* fullpath;         // 用于存放访问的地址
static size_t pathlen = 1024;  //地址的长度

int myftw(char* pathname, Myfunc* func) {
    // 主要是调用下一个函数库，但是这个函数分配地址。
    if ((fullpath = (char*)malloc(pathlen)) == NULL) err_sys("malloc failed");
    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = (char*)realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    strcpy(fullpath, pathname);
    return dopath(func);
}

int dopath(Myfunc* func) {
    int ret;  // func 的返回值，func返回值不是0的时候会出现一些问题
    struct stat statbuf;
    if (lstat(fullpath, &statbuf) < 0)  //不能访问的文件夹
        return (func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) ==
        0)  // 不是一个文件夹，也就是普通的文件，直接返回，这是个递归的函数
        return (func(fullpath, &statbuf, FTW_F));
    if ((ret = func(fullpath, &statbuf, FTW_D)) !=
        0)  // 处理目录，先把目录的计数加1;
        return ret;
    // 后面这部分开始递归目录里面的文件了。
    int n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen) {
        pathlen *= 2;
        if ((fullpath = (char*)realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n] = '\0';  //在最后面加上字符串;
    DIR* dp;
    struct dirent* dirp;
    if ((dp = opendir(fullpath)) == NULL) {
        return (func(fullpath, &statbuf, FTW_DNR));
    }
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(fullpath + n, dirp->d_name);
        if ((ret = dopath(func)) !=
            0)  // 递归，函数的返回值为0,有问题返回值不是0;这时候就马上就马上递归上去有问题。
            break;
    }
    fullpath[n - 1] = '\0';  //把上面的添加上去的地址去掉
    if (closedir(dp) < 0) err_ret("can't close directory;");
    return (ret);
}

int myfunc(const char* pathname, const struct stat* statp, int flag) {
    switch (flag) {
        case FTW_F:
            switch (statp->st_mode & S_IFMT) {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    err_dump("for S_IFDIR for %s", pathname);
                    break;
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can't read directory %s", pathname);
            break;
        case FTW_NS:
            err_ret("stat error for %s", pathname);
            break;
        default:
            err_dump("unknown flag %d for pathname %s", flag, pathname);
    }
    return 0;
}

