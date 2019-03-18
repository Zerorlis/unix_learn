#include <stdlib.h>
#include <iostream>
#include "../myerror.h"
using namespace std;
static void myexit1(void);
static void myexit2(void);

int main(void) {
    if (atexit(myexit2) != 0) {
        err_sys("can't register my_exit2");
    }

    if (atexit(myexit1) != 0) {
        err_sys("can't register my_exit2");
    }

    if (atexit(myexit1) != 0) {
        err_sys("can't register my_exit2");
    }

    cout << "main is done\n";
    return 0;
}

static void myexit1(void) { cout << "first exit handler \n"; }

static void myexit2(void) { cout << "second exit handler \n"; }

