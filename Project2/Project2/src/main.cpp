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
		BENCHMARK_TEST(smth::func(i));
	}
	BenchmarkHandler::EndBenchmark();

}

void smth::func(size_t i)
{
	float f = std::sqrtf(i);
}
