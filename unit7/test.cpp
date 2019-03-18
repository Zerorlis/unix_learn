#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
    char buf[] = "hello,world";
    cout << "1,";
    write(STDOUT_FILENO, buf, sizeof(buf));
    cout << "2";
}
