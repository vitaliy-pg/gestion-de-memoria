//wuatatata
//hahadasdjahsdkaj
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

int main() {

    HANDLE hMapFile;
    LPVOID pBuf;
    hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            SIZE,
            NULL);

    if (hMapFile == NULL) {
        perror("CreateFileMapping");
        exit(EXIT_FAILURE);
    }