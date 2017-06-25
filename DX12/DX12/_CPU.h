#ifndef _CPU_H_
#define _CPU_H_

// Linking
#pragma comment(lib, "pdh.lib")

// Includes
#include <pdh.h>

class _CPU
{
public:
	_CPU();
	_CPU(const _CPU&);
	~_CPU();

	void Init();
	void Shutdown();
	void Update();
	int GetCpuPercentage();

private:
	bool canReadCpu;
	HQUERY queryHandle;
	HCOUNTER counterHandle;
	unsigned long lastSampleTime;
	long cpuUsage;
};
#endif