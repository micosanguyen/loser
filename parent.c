#include <stdio.h>
#include <windows.h>

int main(){

    // thiet lap security attribute cho process con
    SECURITY_ATTRIBUTES sa = {sizeof(sa), NULL, TRUE};

    // goi ham CreateFile de tao file va lay handle tuong tac voi file
    HANDLE hFile = CreateFile("output.txt", FILE_APPEND_DATA, FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE){
        printf("Failed to create file, ERROR: %d\n", GetLastError());
        return 1;
    }

    // su dung handle lay duoc de write vao file 
    DWORD write;
    WriteFile(hFile, "Parent\n", 8, &write, NULL);

    // convert handle to string so we can pass to the child process
    char handleStr[20];

    // convert du lieu va luu vao 1 buffer
    sprintf(handleStr, " %llu", (unsigned long long)hFile);

    printf("fileHandle: %s", handleStr);

    // khai bao struct startup info va process info de khoi tao process con
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi ={0};

    // convert du lieu cmdLine va luu vao buffer
    char cmdLine[150];
    sprintf(cmdLine, "C:\\Users\\Administrator\\Desktop\\Project_C\\child.exe\\%s", handleStr);

    //C:\Users\Administrator\Desktop\Project_C\child.exe

    // create child process
    if(!CreateProcess(NULL, cmdLine, &sa, &sa, TRUE, 0, NULL, NULL, &si, &pi)){
        printf("Error: %d\n", GetLastError());
        return 1;
    }

    Sleep(50);
    printf("Parent: Create child process with PID: %d\n", pi.dwProcessId);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hFile);
}