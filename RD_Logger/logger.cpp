#include "pch.h"
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include "logger.h"
#include <Windows.h>

Logger* Logger::m_logger = nullptr;
HANDLE g_hMutex;

Logger::Logger()
	: m_isExistFile(false)
	, m_fileName{0, }
{
	time_t now = time(NULL);
	tm local;
	localtime_s(&local, &now);
	_stprintf_s(m_fileName, _T("RD_%04d%02d%02d.log"),
		local.tm_year + 1900,
		local.tm_mon + 1,
		local.tm_mday);
}

Logger* Logger::GetInstance()
{
	if (m_logger == nullptr) {
		m_logger = new Logger();
	}

	return m_logger;
}

TCHAR* Logger::GetCurrTime()
{
	static TCHAR strTime[128];

	memset(strTime, 0, sizeof(strTime));

	SYSTEMTIME st;
	GetLocalTime(&st);

	_stprintf_s(strTime, sizeof(strTime) / sizeof(TCHAR), _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds);

	return strTime;
}

void Logger::Logging(TCHAR* a_str)
{
#define LOGSIZE 1024

	if (!a_str) return;

	int offset = 0;
	DWORD dwWaitResult = 0;
	TCHAR log[LOGSIZE] = { 0, };
	FILE* pf = nullptr;
	
	if (g_hMutex) {
		dwWaitResult = WaitForSingleObject(g_hMutex, INFINITE);

		if (dwWaitResult == WAIT_OBJECT_0) {
			if (_tfopen_s(&pf, m_fileName, _T("a")) || !pf) {
				return;
			}

			offset += _stprintf_s(log + offset, LOGSIZE - offset, _T("["));
			offset += _stprintf_s(log + offset, LOGSIZE - offset, _T("%s"), GetCurrTime());
			offset += _stprintf_s(log + offset, LOGSIZE - offset, _T("] "));
			offset += _stprintf_s(log + offset, LOGSIZE - offset, _T("%s\n"), a_str);

			_ftprintf_s(pf, _T("%s"), log);

			fclose(pf);

			pf = nullptr;
		}

		ReleaseMutex(g_hMutex);
	}

}