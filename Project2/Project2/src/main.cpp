#include "ConsoleApp.h"

#define BENCHMARK true

namespace smth
{
	void func(size_t i);
}

int main()
{
	ConsoleApp app;

	do
	{
		app.ManageApp();
	} while (app.GetAppState() != EAppState::Closed);
}