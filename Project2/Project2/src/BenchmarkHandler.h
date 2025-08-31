// Landon's BenchmarkHandler

#pragma once
#include <chrono>
#include <stack>
#include <string>
#include <unordered_map>
#include "ExceptionInterface.h"

#define BENCHMARK true

#if BENCHMARK == true
	#ifndef BENCHMARK_TEST(foo)
	#define BENCHMARK_TEST(foo) BenchmarkHandler::BeginBenchmark(#foo);\
								foo;\
								BenchmarkHandler::EndBenchmark()
	#endif

	#ifndef BENCHMARK_TEST_PRES(foo, precision)
	#define BENCHMARK_TEST_PRES(foo, precision) BenchmarkHandler::BeginBenchmark(#foo);\
												foo;\
												BenchmarkHandler::EndBenchmark(precision)
	#endif


#else
	#ifndef BENCHMARK_TEST(foo)
	#define BENCHMARK_TEST(foo) foo
	#endif

	#ifndef BENCHMARK_TEST_PRES(foo, precision)
	#define BENCHMARK_TEST_PRES(foo, precision) foo
	#endif
#endif

// TODO: Implememt Process Counter

enum class EProcessType
{
	// Empty Process (is not tracking any time & does not have an ID)
	NullProcess,

	// Valid Process (is tracking time & has an ID)
	ValidProcess
};

class Process
{
public:
	struct ProcessInfo
	{
		float ProcessDuration;
		std::string ProcessName;
		uint32_t ProcessID;
	};
public:

	/*
	* 
	* 
	* @return Null/Process/Invalid Process
	*/
	Process();

	/*
	* 
	* @param
	* 
	* @return
	*/
	Process(uint32_t m_ProcessID);

	/*
	* 
	* @param 
	* @param 
	* 
	* @return
	*/
	Process(uint32_t m_ProcessID, const std::string& p_ProcessName);

	ProcessInfo GetProcesseInfo() const;
	bool HasEnded() const;
	bool HasName() const;
	float GetDuration() const;
	std::string GetName() const;
	uint32_t GetID() const;
	bool IsValid() const;
	EProcessType GetProcessType() const;
	

	/*
	* 
	* @return The total Duration the Process Ran for in Seconds
	*/
	float EndProcess();


private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_InitialTimePoint;
	bool m_ProcessEnded;
	ProcessInfo m_ProcessInfo;
	EProcessType m_ProcessType;
};

enum class EBenchmarkSetting
{
	//Benchmark All Processes
	Any,

	//Benchmark Specific Processes (by name)
	Specific,
};

class BenchmarkHandler
{
public:

	//Allow programmers to benchmark only specific processes by Name
	static void InitializeSettings(EBenchmarkSetting p_Setting, std::string Arg...);

	static void BeginBenchmark();
	static void BeginBenchmark(const std::string& p_ProcessName);

	static void EndBenchmark();
	static void EndBenchmark(uint8_t p_LogPrecision);



public:
	// Benchmark Exceptions

private:
	static void LogProcess_File(uint8_t p_LogPrecision);

private:
	constexpr static const char* s_LoggingFile = "Benchmark_Logs.txt";
	constexpr static const char* s_LogHistoryFile = "Benchmark_LogHistory.txt";
	constexpr static const uint8_t s_DefaultLogPrecision = 7;

	static std::stack<Process> s_ProcessStack;
	static uint32_t s_ProcessCounter;

	constexpr static const bool s_AllowRepeatedBenchmarks = true;
	static std::unordered_map<std::string, size_t> s_ProcessInstances;

	constexpr static const EBenchmarkSetting m_Setting = EBenchmarkSetting::Any;

};

