#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        if (fputc(c, stdout) == EOF) {
            cout << "put error";
        }
    }
    if (ferror(stdin)) {
        cout << "get error";
    }
    return 0;
}
