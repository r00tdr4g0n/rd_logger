#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

typedef void (*PLOGGING)(TCHAR*);

int main()
{
	HMODULE hDll = LoadLibraryW(L"RD_Logger.dll");
	if (!hDll) {
		_tprintf(L"Failed to load dll");
		return 1;
	}

	PLOGGING Logging = (PLOGGING)GetProcAddress(hDll, "Logging");
	if (!Logging) {
		_tprintf(L"Failed to get address");
		return 1;
	}

	TCHAR log[MAX_PATH] = { 0, };

	for (int i = 0; i < 100; i++) {
		memset(log, 0, sizeof(log));
		_stprintf_s(log, _T("test %02d"), i);
		Logging(log);
	}

	return 0;
}