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

	void ManageApp();

	void DisplayMenu();

	void Clean();
	
	EAppState GetAppState() const;

	~ConsoleApp();

private:
	EAppState m_AppState;
	EMenuState m_MenuState;
};

