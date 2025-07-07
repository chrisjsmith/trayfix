#define _UNICODE

#include <windows.h>
#include <winreg.h>

#define MAX_KEY_LENGTH 255

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    HKEY hkNotifyIconSettings, hkCurrentIcon;
    DWORD dwIndex, dwSize, dwIsPromoted;
    WCHAR wcKeyName[MAX_KEY_LENGTH];

    dwIndex = 0;
    dwIsPromoted = 1;
    dwSize = sizeof(wcKeyName);

    RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\NotifyIconSettings", 0, KEY_ENUMERATE_SUB_KEYS, &hkNotifyIconSettings);

    for(;;)
    {
        dwSize = MAX_KEY_LENGTH;
        if (RegEnumKeyExW(hkNotifyIconSettings, dwIndex, wcKeyName, &dwSize, NULL, NULL, NULL, NULL))
            break;
        RegOpenKeyExW(hkNotifyIconSettings, (LPCWSTR)&wcKeyName, 0, KEY_ALL_ACCESS, &hkCurrentIcon);
        RegSetValueExW(hkCurrentIcon, L"IsPromoted", 0, REG_DWORD, (const BYTE *)&dwIsPromoted, sizeof(dwIsPromoted));
        RegCloseKey(hkCurrentIcon);
        dwIndex++;
    }
    RegCloseKey(hkNotifyIconSettings);
    return 0;
}