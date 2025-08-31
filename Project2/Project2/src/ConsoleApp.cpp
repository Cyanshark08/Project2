#include "ConsoleApp.h"
#include <cstdio>
#include <cstdint>

ConsoleApp::ConsoleApp()
	: m_AppState(EAppState::Running),
	m_MenuState(EMenuState::Menu)
{}

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
	switch (m_MenuState)
	{
	case EMenuState::Menu:
		printf("");
		break;
	case EMenuState::Quadratic:
		printf("");
		break;
	case EMenuState::Rational:
		printf("");
		break;
	case EMenuState::PseudoRandom:
		printf("");
		break;
	}
}

void ConsoleApp::Clean()
{

}

EAppState ConsoleApp::GetAppState() const
{
	return m_AppState;
}

ConsoleApp::~ConsoleApp()
{
	this->Clean();
}
