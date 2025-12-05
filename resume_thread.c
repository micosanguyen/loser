#include <stdio.h>
#include <windows.h>

int main(){
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi = {0};

    if(CreateProcess("C:\\Windows\\System32\\notepad.exe", 
        NULL, 
        NULL, 
        NULL, 
        FALSE, 
        CREATE_SUSPENDED, 
        NULL, 
        NULL, 
        &si, &pi)){
        
        printf("%lu\n", pi.dwProcessId);
        printf("%lu\n", pi.dwThreadId);
        printf("%lu\n", pi.hProcess);
        printf("%lu\n", pi.hThread);

        getchar();

        ResumeThread(pi.hThread);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Error: %lu\n", GetLastError());
        return 1;
    }

    return 0;
}