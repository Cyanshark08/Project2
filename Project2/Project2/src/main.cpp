#include "BenchmarkHandler.h"
#include <string>
#include <cmath>

#define BENCHMARK true

namespace smth
{
	void func(size_t i);
}

int main()
{
	BenchmarkHandler::BeginBenchmark("Benchmark");
	for (size_t i = 0; i < 1000; i++)
	{
		BenchmarkHandler::BeginBenchmark("Func");
		std::sqrt(i);
		BenchmarkHandler::EndBenchmark();
	}
	//
	BenchmarkHandler::EndBenchmark();

	__debugbreak();
}

void smth::func(size_t i)
{
	float f = std::sqrtf(i);
}
