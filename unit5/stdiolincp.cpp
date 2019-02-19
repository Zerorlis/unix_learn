/* 这个文件测试行读取，gets和fgets，前者危险一点点*/
#include <cstdio>
#include <iostream>
const static int MAXLINE = 1024;
using namespace std;
int main() {
    char buf[MAXLINE];
    while ((fgets(buf, MAXLINE, stdin)) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            cout << "put error";
        }
    }
    if (ferror(stdin)) {
        cout << "get error";
    }
    return 0;
}
