#include <stdio.h>
#include <windows.h>

void threadfunction(){
    printf("New thread ID: %lu\n", GetCurrentThreadId());

    MessageBox(NULL, "Thread is created", "ThreadBox", MB_OK);

}

int main(){
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadfunction, 0, 0, 0);

    WaitForSingleObject(hThread, -1);

    CloseHandle(hThread);

    return 0;

}