#pragma once
#include "PseudoRandom.h"
#include "Quadratic.h"
#include "Rational.h"

enum class EAppState
{
	Running,
	Closed
};

enum class EMenuState
{
	Main,
	Quadratic,
	Rational,
	PseudoRandom
};

class ConsoleApp
{
public:
	ConsoleApp();

	void ManageApp();

	void Clean();
	
	EAppState GetAppState() const;

	~ConsoleApp();

private:
	void DisplayMenu();

	void HandleInput(char p_Input);

private:
	EAppState m_AppState;
	EMenuState m_MenuState;

	Quadratic m_QuadraticExpression;
	PseudoRandom m_RandomNumber;
	Rational m_RationalNumber;
};

