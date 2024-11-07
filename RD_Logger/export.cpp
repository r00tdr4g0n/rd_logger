#include "pch.h"
#include "export.h"
#include <tchar.h>

Logger* g_logger;

void Logging(TCHAR* a_log)
{
	if (g_logger) {
		g_logger->Logging(a_log);
	}
}