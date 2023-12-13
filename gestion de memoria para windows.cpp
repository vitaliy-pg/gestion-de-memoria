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

    pBuf = MapViewOfFile(
            hMapFile,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            SIZE);

    if (pBuf == NULL) {
        perror("MapViewOfFile");
        CloseHandle(hMapFile);
        exit(EXIT_FAILURE);
    }

    strcpy((char*)pBuf, "Hello, child process!");

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
            "child.exe", // Nombre del programa hijo (asegúrate de compilar el programa hijo como "child.exe")
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        perror("CreateProcess");
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Child reads: %s\n", (char*)pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
