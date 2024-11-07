#pragma once

class Logger {
private:
	static Logger* m_logger;
	bool m_isExistFile;
	TCHAR m_fileName[MAX_PATH];

	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:
	static Logger* GetInstance();
	TCHAR* GetCurrTime();
	void Logging(TCHAR*);
};

#ifdef __cplusplus
extern "C" {
#endif

	//Logger GetLogger();

#ifdef __cplusplus
}
#endif