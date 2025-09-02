#include "BenchmarkHandler.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>

Process::Process()
	: m_InitialTimePoint(),
	m_ProcessInfo({ NULL, "", NULL, NULL}),
	m_ProcessEnded(false),
	m_ProcessType(EProcessType::NullProcess)
{}


Process::Process(uint32_t m_ProcessID)
	: m_InitialTimePoint(std::chrono::high_resolution_clock::now()),
	m_ProcessInfo({ NULL, "", m_ProcessID, NULL }),
	m_ProcessEnded(false),
	m_ProcessType(EProcessType::UnnamedProcess)
{}

Process::Process(uint32_t m_ProcessID, size_t p_Iteration, const std::string& p_ProcessName)
	: m_InitialTimePoint(std::chrono::high_resolution_clock::now()),
	m_ProcessInfo({ NULL, p_ProcessName, m_ProcessID, p_Iteration }),
	m_ProcessEnded(false),
	m_ProcessType(EProcessType::ValidProcess)
{}

Process::ProcessInfo Process::GetProcesseInfo() const
{
	return m_ProcessInfo;
}

bool Process::HasEnded() const
{
	return m_ProcessEnded;
}

bool Process::HasName() const
{
	return m_ProcessInfo.processName.length() != 0;
}

float Process::GetDuration() const
{
	return m_ProcessInfo.processDuration;
}

std::string Process::GetName() const
{
	return m_ProcessInfo.processName;
}


uint32_t Process::GetID() const
{
	return m_ProcessInfo.processID;
}

bool Process::IsReal() const
{
	return m_ProcessType != EProcessType::NullProcess;
}

bool Process::IsValid() const
{
	return m_ProcessType == EProcessType::ValidProcess;
}

bool Process::IsNull() const
{
	return m_ProcessType == EProcessType::NullProcess;
}

EProcessType Process::GetType() const
{
	return m_ProcessType;
}

EProcessType Process::GetProcessType() const
{
	return m_ProcessType;
}

size_t Process::GetIteration() const
{
	return m_ProcessInfo.processIteration;
}

float Process::EndProcess()
{
	auto latestPoint = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = latestPoint - m_InitialTimePoint;
	m_ProcessInfo.processDuration = duration.count();
	m_ProcessEnded = true;
	return m_ProcessInfo.processDuration;
}

uint32_t BenchmarkHandler::s_ProcessCounter = 0;
std::stack<Process> BenchmarkHandler::s_ProcessStack{};
std::unordered_map<std::string, ProcessGroupStats> BenchmarkHandler::s_ProcessGroups{};
EBenchmarkSetting BenchmarkHandler::m_Setting = EBenchmarkSetting::Any;
std::unordered_map<std::string, int> BenchmarkHandler::s_WhitelistedProcesses{};

void BenchmarkHandler::InitializeSettings(EBenchmarkSetting p_Setting, ...)
{
	if(p_Setting != EBenchmarkSetting::Any)
	{
		m_Setting = EBenchmarkSetting::Specific;

		va_list arg;
		va_start(arg, p_Setting);
		
		char* strBuffer = va_arg(arg, char*);
		while(strBuffer)
		{
			s_WhitelistedProcesses[strBuffer] = NULL;
			strBuffer = va_arg(arg, char*);
		} 
		
		va_end(arg);
	}
}

void BenchmarkHandler::BeginBenchmark()
{
	
	if (s_ProcessCounter == 0)
	{
		std::remove(s_LoggingFile);
		std::ofstream logFile_Write(s_LoggingFile);

		logFile_Write << "Current Log";

		logFile_Write.close();

		uint32_t logNum = 1;
		std::ifstream historyLog_Read(s_LogHistoryFile);
		std::string line;
		
		while (std::getline(historyLog_Read, line))
		{
			size_t pos = line.find("Log #");

			if (pos != std::string::npos)
				logNum = std::stoi(line.substr(pos + 5)) + 1;
		}

		historyLog_Read.close();

		std::ofstream historyLog_Write(s_LogHistoryFile, std::ios::app);

		historyLog_Write << "\n\tLog #" << logNum;

		historyLog_Write.close();
	}

	if (m_Setting == EBenchmarkSetting::Specific)
	{
		s_ProcessStack.emplace(Process());
		return;
	}

	s_ProcessCounter++;
	
	s_ProcessStack.emplace(s_ProcessCounter);
}

void BenchmarkHandler::BeginBenchmark(const std::string& p_ProcessName)
{
	if (s_ProcessCounter == 0)
	{
		std::remove(s_LoggingFile);
		std::ofstream logFile_Write(s_LoggingFile);

		logFile_Write << "Current Log";

		logFile_Write.close();

		uint32_t logNum = 1;
		std::ifstream historyLog_Read(s_LogHistoryFile);
		std::string line;

		while (std::getline(historyLog_Read, line))
		{
			size_t pos = line.find("Log #");

			if (pos != std::string::npos)
				logNum = std::stoi(line.substr(pos + 5)) + 1;
		}

		historyLog_Read.close();

		std::ofstream historyLog_Write(s_LogHistoryFile, std::ios::app);

		historyLog_Write << "\n\tLog #" << logNum;

		historyLog_Write.close();
	}
	
	if (m_Setting == EBenchmarkSetting::Specific && s_WhitelistedProcesses.find(p_ProcessName) == s_WhitelistedProcesses.end())
	{
		s_ProcessStack.emplace(Process());
		return;
	}

	if (s_ProcessGroups.find(p_ProcessName) != s_ProcessGroups.end() && s_AllowRepeatedBenchmarks)
		s_ProcessGroups[p_ProcessName].numberOfIterations++;
	else if (s_ProcessGroups.find(p_ProcessName) != s_ProcessGroups.end() && !s_AllowRepeatedBenchmarks)
	{
		s_ProcessStack.emplace(Process());
		return;
	}
	else
		s_ProcessGroups[p_ProcessName].numberOfIterations = 1;

	s_ProcessCounter++;
	s_ProcessStack.emplace(s_ProcessCounter, s_ProcessGroups[p_ProcessName].numberOfIterations, p_ProcessName);

}

void BenchmarkHandler::EndBenchmark()
{
	switch (s_ProcessStack.top().GetProcessType())
	{
	case EProcessType::ValidProcess:
		s_ProcessStack.top().EndProcess();
		LogProcess_File(s_DefaultLogPrecision);
		s_ProcessStack.pop();
		break;
	case EProcessType::UnnamedProcess:
		s_ProcessStack.top().EndProcess();
		LogProcess_File(s_DefaultLogPrecision);
		s_ProcessStack.pop();
		break;
	case EProcessType::NullProcess:
		s_ProcessStack.pop();
		break;
	}
}

void BenchmarkHandler::EndBenchmark(uint8_t p_LogPrecision)
{		
	switch (s_ProcessStack.top().GetProcessType())
	{
	case EProcessType::ValidProcess:
		s_ProcessStack.top().EndProcess();
		LogProcess_File(p_LogPrecision);
		s_ProcessStack.pop();
		break;
	case EProcessType::UnnamedProcess:
		s_ProcessStack.top().EndProcess();
		LogProcess_File(p_LogPrecision);
		s_ProcessStack.pop();
		break;
	case EProcessType::NullProcess:
		s_ProcessStack.pop();
		break;
	}
}

void BenchmarkHandler::Terminate()
{
}

void BenchmarkHandler::LogProcess_File(uint8_t p_LogPrecision)
{
	std::ofstream loggingFile(s_LoggingFile, std::ios::app);
	std::ofstream logHistoryFile(s_LogHistoryFile, std::ios::app);
	std::stringstream ss;

	if (loggingFile.fail())
	{
		printf("\n\tERROR: Failed to load Log file ");
		return;
	}

	if (logHistoryFile.fail())
	{
		printf("\n\tERROR: Failed to load Log History file ");
		return;
	}

	if (!s_ProcessStack.top().HasEnded())
	{
		printf("\n\tERROR: Tried to log running process");
		return;
	}

	ss << "Instance (" << s_ProcessStack.top().GetIteration() << ") : Exited Process 0x" << std::hex << s_ProcessStack.top().GetID() << " (\"" << s_ProcessStack.top().GetName() << "\") At Process Stack Layer 0x" << s_ProcessStack.size() << " : Process Lasted " << std::fixed << std::setprecision(p_LogPrecision) << s_ProcessStack.top().GetDuration() << "s";
	loggingFile << "\n\t"  << ss.str();
	logHistoryFile << "\n\t\t" << ss.str();


	loggingFile.close();
	logHistoryFile.close();
}

void BenchmarkHandler::LogProcessStats_File()
{
}
