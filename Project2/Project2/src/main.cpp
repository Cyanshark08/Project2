/*
* Collaborators:
*  - Andrew Nguyen
*  - Jaime Gutierrez
*  - Landon Mendoza
* 
* Date: 9/6/2025
* 
* Project: 
* 
*/


#include "ConsoleApp.h"

int main()
{
	ConsoleApp app;

	do
	{
		app.ManageApp();
	} while (app.GetAppState() != EAppState::Closed);
}