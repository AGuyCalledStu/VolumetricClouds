#include "_CPU.h"



_CPU::_CPU()
{
}

_CPU::_CPU(const _CPU& other)
{
}

_CPU::~_CPU()
{
}

void _CPU::Init()
{
	PDH_STATUS status;

	// Init the flag indicating whether this object can read the system cpu usage or not
	canReadCpu = true;

	// Create a query object to poll cpu usage
	status = PdhOpenQuery(NULL, 0, &queryHandle);
	if (status != ERROR_SUCCESS)
	{
		canReadCpu = false;
	}

	// Set query object to poll all cpus in the system
	status = PdhAddCounter(queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &counterHandle);
	if (status != ERROR_SUCCESS)
	{
		canReadCpu = false;
	}

	lastSampleTime = GetTickCount();

	cpuUsage = 0;
}

void _CPU::Shutdown()
{
	if (canReadCpu)
	{
		PdhCloseQuery(queryHandle);
	}
}

void _CPU::Update()
{
	PDH_FMT_COUNTERVALUE value;

	if (canReadCpu)
	{
		if ((lastSampleTime + 1000) < GetTickCount())
		{
			lastSampleTime = GetTickCount();
			PdhCollectQueryData(queryHandle);
			PdhGetFormattedCounterValue(counterHandle, PDH_FMT_LONG, NULL, &value);
			cpuUsage = value.longValue;
		}
	}
}

int _CPU::GetCpuPercentage()
{
	int usage;

	if (canReadCpu)
	{
		usage = (int)cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}