#include <sys/stat.h>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main(int args, char* argv[]) {
    if (args != 3) {
        cout << "usage chmod 777 file";
        return 0;
    }
    struct stat filestatus;

    if (stat(argv[2], &filestatus) < 0) {
        cout << "stat error, do you have the directory permission?";
        return 0;
    }
    mode_t file_mode = 0;

    if (!(strlen(argv[1]) == 3 || strlen(argv[1]) == 4)) {
        cout << "usage:chmod xxx file";
        return 0;
    }
    if (strlen(argv[1]) == 4) {
        int s = argv[1][0] - '0';
        if (s < 0 || s > 7) {
            cout << "usage:chmod xxx file";
            return 0;
        }
        // special mask
        if ((s - 4) >= 0) {
            file_mode |= S_ISUID;
            s -= 4;
        }
        if ((s - 2) >= 0) {
            file_mode |= S_ISGID;
            s -= 2;
        }
        if ((s - 1) >= 0) {
            file_mode |= S_ISVTX;
            s -= 1;
        }
    }
    char* last_three;
    if (strlen(argv[1]) == 4) {
        last_three = argv[1] + 1;
    } else {
        last_three = argv[1];
    }
    for (int i = 0; i < 3; i++) {
        int s = last_three[i] - '0';

        if (s < 0 || s > 7) {
            cout << "usage:chmod xxx file";
            return 0;
        }
        if ((s - 4) >= 0) {
            switch (i) {
                case 0:
                    file_mode |= S_IRUSR;
                    break;
                case 1:
                    file_mode |= S_IRGRP;
                    break;
                case 2:
                    file_mode |= S_IROTH;
                    break;
            }
            s -= 4;
        }
        if ((s - 2) >= 0) {
            switch (i) {
                case 0:
                    file_mode |= S_IWUSR;
                    break;
                case 1:
                    file_mode |= S_IWGRP;
                    break;
                case 2:
                    file_mode |= S_IWOTH;
                    break;
            }
            s -= 2;
        }
        if ((s - 1) >= 0) {
            switch (i) {
                case 0:
                    file_mode |= S_IXUSR;
                    break;
                case 1:
                    file_mode |= S_IXGRP;
                    break;
                case 2:
                    file_mode |= S_IXOTH;
                    break;
            }
            s -= 1;
        }
        if (chmod(argv[2], file_mode) < 0) {
            cout << "chmod error;";
            return 0;
        }
    }
}

