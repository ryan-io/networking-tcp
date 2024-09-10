#pragma once

class DebugClient {
public:
	void Log(const char* message);
	DebugClient();
	~DebugClient();
private:
	const int m_debugLevel;
};


