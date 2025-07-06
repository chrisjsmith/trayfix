#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winreg.h>
#include <winuser.h>

#define MAX_KEY_LENGTH 255

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    HKEY hkNotifyIconSettings, hkCurrentIcon;
    LRESULT r;
    DWORD dwIndex, sz, isPromoted;
    TCHAR wcKeyName[MAX_KEY_LENGTH];

    dwIndex = 0;
    isPromoted = 1;
    sz = sizeof(wcKeyName);

    r = RegOpenKeyExW(HKEY_CURRENT_USER, TEXT("Control Panel\\NotifyIconSettings"), 0, KEY_ENUMERATE_SUB_KEYS, &hkNotifyIconSettings);

    for(;;)
    {
        sz = MAX_KEY_LENGTH;
        r = RegEnumKeyExW(
            hkNotifyIconSettings, 
            dwIndex, 
            wcKeyName, 
            &sz, NULL, NULL, NULL, NULL);
        if (r == ERROR_NO_MORE_ITEMS)
            break;

        RegOpenKeyExW(hkNotifyIconSettings, &wcKeyName, 0, KEY_ALL_ACCESS, &hkCurrentIcon);
        RegSetValueExW(hkCurrentIcon, TEXT("IsPromoted"), 0, REG_DWORD, (const BYTE *)&isPromoted, sizeof(isPromoted));
        RegCloseKey(hkCurrentIcon);
        dwIndex++;
    }
    RegCloseKey(hkNotifyIconSettings);
    return 0;
}