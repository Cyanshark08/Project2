#include "ConsoleApp.h"
#include <cstdio>
#include <cstdint>
#include "BenchmarkHandler.h"
#include "Input.h"

ConsoleApp::ConsoleApp()
	: m_AppState(EAppState::Running),
	m_MenuState(EMenuState::Main)
{
	BenchmarkHandler::InitializeSettings(EBenchmarkSetting::Any);
}

void ConsoleApp::ManageApp()
{
	switch (m_AppState)
	{
	case EAppState::Running:
		DisplayMenu();
		break;
	case EAppState::Closed:
		this->Clean();
		break;
	}

}

void ConsoleApp::DisplayMenu()
{
	char input = '\0';

	switch (m_MenuState)
	{
	case EMenuState::Main:
		puts("");
		puts("\tCMPR131 Chapter 2 - ADT Assignments by ____ (9 / 1 / 2023)");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t1 > Quadratic Expression");
		puts("\t2 > Pseudorandom");
		puts("\t3 > Rational number");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\tX.Exit");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\tOption : ");

		input = Input::inputChar("", "123X");
		break;
	case EMenuState::Quadratic:
		puts("");
		puts("\t1 > Quadratic Menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\tD.display the expression");
		puts("\tA.set coefficient(a)");
		puts("\tB.set coefficient(b)");
		puts("\tC.set coefficient(c)");
		puts("\tE.get evaluation(x)");
		puts("\tN.get the number of real roots");
		puts("\tR.get real root(s)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t0. return");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\tOption :");

		input = Input::inputChar("", "DABCENR0");
		break;
	case EMenuState::Rational:
		printf("");
		break;
	case EMenuState::PseudoRandom:
		printf("");
		break;
	}

	HandleInput(input);
	std::system("pause");
	std::system("cls");
}

void ConsoleApp::HandleInput(char p_Input)
{
	switch (m_MenuState)
	{
	case EMenuState::Main:
		switch (p_Input)
		{
		case '1':
			m_MenuState = EMenuState::Quadratic;
			break;
		case '2':
			m_MenuState = EMenuState::PseudoRandom;
			break;
		case '3':
			m_MenuState = EMenuState::Rational;
			break;
		case 'X':
			m_AppState = EAppState::Closed;
			break;
		}
		break;
	case EMenuState::Quadratic:
		switch (p_Input)
		{
		case 'D':
			printf("%s", m_QuadraticExpression.to_string());
			break;
		}
		break;
	case EMenuState::Rational:
	
		break;
	case EMenuState::PseudoRandom:
	
		break;
	}
}

void ConsoleApp::Clean()
{
	BenchmarkHandler::Terminate();
}

EAppState ConsoleApp::GetAppState() const
{
	return m_AppState;
}

ConsoleApp::~ConsoleApp()
{
	this->Clean();
}
