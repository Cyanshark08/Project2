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
		puts("\t1. Quadratic Expression");
		puts("\t2. Pseudorandom");
		puts("\t3. Rational number");
		puts("\t4. Statistician");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\tX. Exit");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\tOption : ");

		input = Input::inputChar("", "1234X");
		break;
	case EMenuState::Quadratic:
		puts("");
		puts("\tQuadratic Menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t\tD. Display the expression");
		puts("\t\tA. Set coefficient(a)");
		puts("\t\tB. Set coefficient(b)");
		puts("\t\tC. Set coefficient(c)");
		puts("\t\tE. Get evaluation(x)");
		puts("\t\tN. Get the number of real roots");
		puts("\t\tR. Get real root(s)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t\t0. Return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\t\tOption : ");

		input = Input::inputChar("", "DABCENR0");
		break;
	case EMenuState::Rational:
		puts("");
		puts("\tRational Number Menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t\tA. Enter values of rational number R1");
		puts("\t\tB. Display R1");
		puts("\t\tC. Enter values for  rational number R2");
		puts("\t\tD. Display R2");
		puts("\t\tE. Multiplication of 2 rational numbers(R1 * R2)");
		puts("\t\tF. Division of 2 rational numbers(R1 / R2)");
		puts("\t\tG. Addition of 2 rational numbers(R1 + R2)");
		puts("\t\tH. Subtraction 2 rational numbers(R1 - R2)");
		puts("\t\tI. (R1 == R2)");
		puts("\t\tJ. (R1 < R2)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t\t0. Return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\t\tOption : ");

		input = Input::inputChar("", "ABCDEFGHIJ0");
		break;
	case EMenuState::PseudoRandom:
		puts("");
		puts("\tPseudorandom Menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t\tA. Get seed");
		puts("\t\tB. Set seed");
		puts("\t\tC. Get multiplier");
		puts("\t\tD. Set multiplier");
		puts("\t\tE. Get modulus");
		puts("\t\tF. Set modulus");
		puts("\t\tG. Get increment");
		puts("\t\tH. Set increment");
		puts("\t\tI. Get next number");
		puts("\t\tJ. Get indirect next number");
		puts("\t\tK. Run experiment with different values(mutliplier, increment, and modulus)");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t\t0. Return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\t\tOption : ");

		input = Input::inputChar("", "ABCDEFGHIJK0");
		break;
	case EMenuState::Statistician:
		puts("");
		puts("\tStatistician Menu");
		puts(("\t" + std::string(110, 205)).c_str());
		puts("\t\tA. Insert a number into the sequence");
		puts("\t\tB. Find length");
		puts("\t\tC. Find first number");
		puts("\t\tD. Find last number");
		puts("\t\tE. Find sum");
		puts("\t\tF. Find mean");
		puts("\t\tG. Find smallest number (minimum)");
		puts("\t\tH. Find largest number (maximum)");
		puts("\t\tI. Display the sequence");
		puts("\t\tJ. Clear the sequence");
		puts(("\t" + std::string(110, 196)).c_str());
		puts("\t\t0. Return");
		puts(("\t" + std::string(110, 205)).c_str());
		printf("\t\tOption : ");

		input = Input::inputChar("", "ABCDEFGHIJ0");
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
		case '4':
			m_MenuState = EMenuState::Statistician;
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
				printf("%s", e.Message().c_str());
				m_MenuState = EMenuState::Main;
				std::system("pause");
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
				printf("%s", e.Message().c_str());
				m_MenuState = EMenuState::Main;
				std::system("pause");
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
		case 'A': // Get seed
			printf("\n\tSeed: %d", m_RandomNumber.getSeed());
			break;
		case 'B': // Set seed
			m_RandomNumber.setSeed(Input::inputInteger("\n\tEnter new seed: "));
			printf("\n\tSeed set successfully.");
			break;
		case 'C': // Get multiplier
			printf("\n\tMultiplier: %d", m_RandomNumber.getMultiplier());
			break;
		case 'D': // Set multiplier
			m_RandomNumber.setMultiplier(Input::inputInteger("\n\tEnter new multiplier: "));
			printf("\n\tMultiplier set successfully.");
			break;
		case 'E': // Get modulus
			printf("\n\tModulus: %d", m_RandomNumber.getModulus());
			break;
		case 'F': // Set modulus
			try
			{
				m_RandomNumber.setModulus(Input::inputInteger("\n\tEnter new modulus: "));
				printf("\n\tModulus set successfully.");
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'G': // Get increment
			printf("\n\tIncrement: %d", m_RandomNumber.getIncrement());
			break;
		case 'H': // Set increment
			m_RandomNumber.setIncrement(Input::inputInteger("\n\tEnter new increment: "));
			printf("\n\tIncrement set successfully.");
			break;
		case 'I': // Get next number
			printf("\n\tNext number: %d", m_RandomNumber.getNextNumber());
			break;
		case 'J': // Get indirect next number
			printf("\n\tIndirect next number: %d", m_RandomNumber.getIndirectNextNumber());
			break;
		case 'K': // Run experiment
		{
			printf("\n\tRunning experiment with different values...");

			// Test with different parameters
			PseudoRandom exp1(123, 75, 74, 65537);
			printf("\n\tExperiment 1 (123,75,74,65537): ");
			for (int i = 0; i < 5; i++)
			{
				printf("%d ", exp1.getNextNumber());
			}

			PseudoRandom exp2(456, 1664525, 1013904223, 4294967296);
			printf("\n\tExperiment 2 (456,1664525,1013904223,4294967296): ");
			for (int i = 0; i < 5; i++)
			{
				printf("%d ", exp2.getNextNumber());
			}
			break;
		}
		case '0':
			m_RandomNumber.Clear();
			m_MenuState = EMenuState::Main;
			break;
		}
		break;
	case EMenuState::Statistician:
		switch (p_Input)
		{
		case 'A': // Insert number
		{
			double num = Input::inputDouble("\n\tEnter a number to insert: ");
			m_Sequence.insertNumber(num);
			printf("\n\tNumber %.2f inserted successfully.", num);
			break;
		}
		case 'B': // Find length
			printf("\n\tLength: %d", m_Sequence.findLength());
			break;
		case 'C': // Find first
			try
			{
				printf("\n\tFirst number: %.2f", m_Sequence.findFirst());
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'D': // Find last
			try
			{
				printf("\n\tLast number: %.2f", m_Sequence.findLast());
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'E': // Find sum
			printf("\n\tSum: %.2f", m_Sequence.findSum());
			break;
		case 'F': // Find mean
			try
			{
				printf("\n\tMean: %.2f", m_Sequence.findMean());
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'G': // Find minimum
			try
			{
				printf("\n\tMinimum: %.2f", m_Sequence.findMinimum());
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'H': // Find maximum
			try
			{
				printf("\n\tMaximum: %.2f", m_Sequence.findMaximum());
			}
			catch (const ExceptionInterface &e)
			{
				printf("%s", e.Message().c_str());
			}
			break;
		case 'I': // Display sequence
			printf("\n\tSequence: %s", m_Sequence.displaySequence().c_str());
			break;
		case 'J': // Clear sequence
			m_Sequence.Clear();
			printf("\n\tSequence cleared.");
			break;
		case '0':
			m_Sequence.Clear();
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
