#pragma once

class DebugServer {
public:
	void Log(const char* msg);
private:
	int m_logLevel;
};