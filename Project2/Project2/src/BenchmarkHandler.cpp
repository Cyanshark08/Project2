#include "BenchmarkHandler.h"
#include <fstream>
#include <iomanip>
#include <sstream>

Process::Process(uint32_t m_ProcessID)
	: m_InitialTimePoint(std::chrono::high_resolution_clock::now()),
	m_ProcessInfo({ NULL, "", m_ProcessID }),
	m_ProcessEnded(false)
{}

Process::Process(uint32_t m_ProcessID, const std::string& p_ProcessName)
	: m_InitialTimePoint(std::chrono::high_resolution_clock::now()),
	m_ProcessInfo({ NULL, p_ProcessName, m_ProcessID }),
	m_ProcessEnded(false)
{}

Process::ProcessInfo Process::GetProcesseInfo() const
{
	return m_ProcessInfo;
}

bool Process::HasEnded() const
{
	return m_ProcessEnded;
}

float Process::GetDuration() const
{
	return m_ProcessInfo.ProcessDuration;
}

std::string Process::GetName() const
{
	return m_ProcessInfo.ProcessName;
}


uint32_t Process::GetID() const
{
	return m_ProcessInfo.ProcessID;
}

float Process::EndProcess()
{
	auto latestPoint = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = latestPoint - m_InitialTimePoint;
	m_ProcessInfo.ProcessDuration = duration.count();
	m_ProcessEnded = true;
	return m_ProcessInfo.ProcessDuration;
}

uint32_t BenchmarkHandler::s_ProcessCounter = 0;
std::stack<Process> BenchmarkHandler::s_ProcessStack;

void BenchmarkHandler::BeginBenchmark()
{
	
	if (s_ProcessCounter == 0);
	{
		std::remove(s_LoggingFile);

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

	s_ProcessCounter++;
	s_ProcessStack.emplace(s_ProcessCounter);
}

void BenchmarkHandler::BeginBenchmark(const std::string& p_ProcessName)
{
	if (s_ProcessCounter == 0);
	{
		std::remove(s_LoggingFile);

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

	s_ProcessCounter++;
	s_ProcessStack.emplace(s_ProcessCounter, p_ProcessName);
}

void BenchmarkHandler::EndBenchmark()
{
	s_ProcessStack.top().EndProcess();
	LogProcess_File(s_DefaultLogPrecision);
	s_ProcessStack.pop();
}

void BenchmarkHandler::EndBenchmark(uint8_t p_LogPrecision)
{
	s_ProcessStack.top().EndProcess();
	LogProcess_File(p_LogPrecision);
	s_ProcessStack.pop();
}

void BenchmarkHandler::LogProcess_File(uint8_t p_LogPrecision)
{
	std::ofstream loggingFile(s_LoggingFile);
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

	ss << "Process #" << s_ProcessStack.top().GetID() << " (" << s_ProcessStack.top().GetName() << ") At Process Stack Instance (" << s_ProcessStack.size() << ") Ended and lasted " << std::fixed << std::setprecision(p_LogPrecision) << s_ProcessStack.top().GetDuration() << "s";
	loggingFile << "Current Log\n\t"  << ss.str();
	logHistoryFile << "\n\t\t" << ss.str();


	loggingFile.close();
	logHistoryFile.close();
}
