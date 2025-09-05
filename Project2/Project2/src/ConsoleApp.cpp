#include "ConsoleApp.h"
#include <cstdio>
#include <cstdint>
#include "BenchmarkHandler.h"
#include "Input.h"

ConsoleApp::ConsoleApp()
	: m_AppState(EAppState::Running),
	m_MenuState(EMenuState::Main)
{
	BenchmarkHandler::InitializeSettings(EBenchmarkSetting::Specific, "Benchmark", "Ben", NULL);
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
		puts("\tCMPR131 Chapter 2 - ADT Assignments by ____ (9 / 1 / 2025)");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t1 > Quadratic Expression");
		puts("\t2 > Pseudorandom");
		puts("\t3 > Rational number");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\tX.Exit");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\tOption : ");

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
		printf("\tOption : ");

		input = Input::inputChar("", "DABCENR0");
		break;
	case EMenuState::Rational:
		puts("");
		puts("\t3 > Rational Number menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\tA.enter values of rational number R1");
		puts("\tB.display R1");
		puts("\tC.enter values for  rational number R2");
		puts("\tD.display R2");
		puts("\tE.multiplication of 2 rational numbers(R1 * R2)");
		puts("\tF.division of 2 rational numbers(R1 / R2)");
		puts("\tG.addition of 2 rational numbers(R1 + R2)");
		puts("\tH.subtraction 2 rational numbers(R1 - R2)");
		puts("\tI. (R1 == R2)");
		puts("\tJ. (R1 < R2)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t0. return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\tOption : ");

		input = Input::inputChar("", "ABCDEFGHIJ0");
		break;
	case EMenuState::PseudoRandom:
		puts("");
		puts("\t2 > Pseudorandom menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\tA.get seed");
		puts("\tB.set seed");
		puts("\tC.get multiplier");
		puts("\tD.set multiplier");
		puts("\tE.get modulus");
		puts("\tF.set modulus");
		puts("\tG.get increment");
		puts("\tH.set increment");
		puts("\tI.get next number");
		puts("\tJ.get indirect next number");
		puts("\tK.run experiment with different values(mutliplier, increment, and modulus)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t0. return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\tOption : ");

		input = Input::inputChar("", "ABCDEFGHIJK0");
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
			printf("\n\t%s", m_QuadraticExpression.to_string().c_str());
			break;
		case 'A':
			m_QuadraticExpression.SetAt(EQuadraticCoeff::A, (float)Input::inputDouble("\n\t"));
			break;
		case 'B':
			m_QuadraticExpression.SetAt(EQuadraticCoeff::B, (float)Input::inputDouble("\n\t"));
			break;
		case 'C':
			BenchmarkHandler::BeginBenchmark();
			m_QuadraticExpression.SetAt(EQuadraticCoeff::C, (float)Input::inputDouble("\n\t"));
			BenchmarkHandler::EndBenchmark();
			break;
		case 'E':
		{
			BenchmarkHandler::BeginBenchmark("Benchmark");
			auto temp = (float)Input::inputDouble("");
			printf("\n\tf(%.3f) = %.3f", temp, m_QuadraticExpression.EvaluateAt(temp));
			BenchmarkHandler::EndBenchmark();
		}
			break;
		case 'N':
			BenchmarkHandler::BeginBenchmark("Ben");
			printf("\n\tNumber of Roots : %d", m_QuadraticExpression.GetNumOfRoots());
			BenchmarkHandler::EndBenchmark();
			break;
		case 'R':
			if(m_QuadraticExpression.GetNumOfRoots() > 1)
				printf("\n\tRoots : x = %.3f, x = %.3f", m_QuadraticExpression.GetRoots().rootOne, m_QuadraticExpression.GetRoots().rootTwo);
			else if (m_QuadraticExpression.GetNumOfRoots() == 0)
				printf("\n\tNo Real Roots!");
			else
				printf("\n\tRoot : x = %.3f", m_QuadraticExpression.GetRoots().rootOne);
			break;
		case '0':
			m_QuadraticExpression.Clear();
			m_MenuState = EMenuState::Main;
			break;
		}
		break;
	case EMenuState::Rational:
		switch (p_Input)
		{
		case '0':
			m_RationalNumber1.Clear();
			m_RationalNumber2.Clear();
			m_MenuState = EMenuState::Main;
			break;

		case 'A': // get values for rational number 1
			try
			{
				int n = Input::inputInteger("\n\tEnter the value for the numerator: ");
				int d = Input::inputInteger("\n\tEnter the value for the denominator: ");
				m_RationalNumber1 = Rational(n, d);
			}
			catch (const ExceptionInterface &e)
			{
				return;
			}
			printf("\n\tSuccessfully set the numerator and denominator.\n");
			break;

		case 'B': // display rational number 1
			printf("\n\tRational number R1: %s\n", m_RationalNumber1.to_string().c_str());
			break;

		case 'C': // get values for rational number 2
			try
			{
				int n = Input::inputInteger("\n\tEnter the value for the numerator: ");
				int d = Input::inputInteger("\n\tEnter the value for the denominator: ");
				m_RationalNumber2 = Rational(n, d);
			}
			catch (const ExceptionInterface &e)
			{
				return;
			}
			std::cout << "\n\tSuccessfully set the numerator and denominator.\n";
			break;

		case 'D': // display rational number 2
			printf("\n\tRational Number R2: %s\n", m_RationalNumber2.to_string().c_str());
			break;

		case 'E': // multiplication
			printf("\n\tR1 * R2: %s\n", (m_RationalNumber1 * m_RationalNumber2).to_string().c_str());
			break;

		case 'F': // division
			printf("\n\tR1 / R2: %s\n", (m_RationalNumber1 / m_RationalNumber2).to_string().c_str());
			break;

		case 'G': // addition
			printf("\n\tR1 + R2: %s\n", (m_RationalNumber1 + m_RationalNumber2).to_string().c_str());
			break;

		case 'H': // subtraction
			printf("\n\tR1 - R2: %s\n", (m_RationalNumber1 - m_RationalNumber2).to_string().c_str());
			break;

		case 'I': // equal operator
			if (m_RationalNumber1 == m_RationalNumber2)
				printf("\n\tR1 == R2: True\n");
			else
				printf("\n\tR1 == R2: False\n");
			break;

		case 'J': // less than operator
			if (m_RationalNumber1 < m_RationalNumber2)
				printf("\n\tR1 < R2: True\n");
			else
				printf("\n\tR1 < R2: False\n");
			break;
		}

		break;
	case EMenuState::PseudoRandom:
		switch (p_Input)
		{
		case '0':
			m_RandomNumber.Clear();
			m_MenuState = EMenuState::Main;
			break;
		}
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
