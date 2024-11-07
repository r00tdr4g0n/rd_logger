#pragma once

#include "logger.h"

#ifdef RDLOGGER_EXPORTS
#define RD_LOGGER_API __declspec(dllexport)	
#else
#define RD_LOGGER_API __declspec(dllimport)	
#endif

#ifdef __cplusplus
extern "C" {
#endif

	RD_LOGGER_API void Logging(TCHAR*);

#ifdef __cplusplus
}
#endif