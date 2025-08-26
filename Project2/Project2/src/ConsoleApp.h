#pragma once

enum class EAppState
{
	Running,
	Closed
};

enum class EMenuState
{
	Menu,
	Quadratic,
	Rational,
	PseudoRandom
};

class ConsoleApp
{
public:
	ConsoleApp();

	void DisplayMenu();

	void Clean();

	~ConsoleApp();
};

