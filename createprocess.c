#include <stdio.h>
#include <windows.h>

int main(){

    // khoi tao startup structure info va process structure info de khai bao cac thong tin cho process va nhan du lieu tra ve
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi = {0};

    // khai bao string appname, kieu LPCSTR

    const char *appname = "C:\\Windows\\System32\\notepad.exe";

    // Create process la kieu BOOL, check neu true thi tao thanh cong process va in ra thong tin process, neu false thi in ra error bang ham GetLastError support cho ham CreateProcess
    
    if(CreateProcess(appname, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
        printf("Process created successfully\n ProcessId: %lu\n ThreadId: %lu\n", pi.dwProcessId, pi.dwThreadId);

        // close handle:
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("%lu", GetLastError());
        return 1;
    }

    return 0;
}