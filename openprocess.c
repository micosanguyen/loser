#include <windows.h>
#include <stdio.h>

int main(){
    // define gia tri tra ve cua ham OpenProcess
    DWORD processID;
    HANDLE hprocess;

    printf("Enter processID: ");
    scanf("%lu", &processID);

    // su dung ham openprocess, cung cap input va bien output tra ve
    hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    if(hprocess == NULL){
        printf("Failed to open process, Error: %lu\n", GetLastError());
        return 1;
    }

    // in ra gia tri handle
    printf("Success: %p", hprocess);

    CloseHandle(hprocess);
    return 0;
}