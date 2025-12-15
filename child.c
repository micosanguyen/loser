#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Child: no handle receive:\n");
        return 1;
    }

HANDLE hFile = (HANDLE)_strtoui64(argv[1], NULL, 10);

if(hFile == INVALID_HANDLE_VALUE){
    printf("Child: Invalid handle received\n");
    return 1;
}

DWORD bytewrite;
const char *message = "Hello from child!\n";

WriteFile(hFile, message, strlen(message), &bytewrite, NULL);

printf("Child: wrote");
CloseHandle(hFile);

return 0;
}