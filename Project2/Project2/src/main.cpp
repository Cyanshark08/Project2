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
		BENCHMARK_TEST(smth::func(100));
}

void smth::func(size_t i)
{
	BenchmarkHandler::BeginBenchmark("Func");
	if (i != 0)
		func(--i);
	else
		return;
	BenchmarkHandler::EndBenchmark();
}
