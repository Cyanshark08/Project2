/*
* Collaborators:
*  - Andrew Nguyen
*  - Jaime Gutierrez
*  - Landon Mendoza
* 
* Date: 9/6/2025
* 
* Project: 
*  - Quadratic Expression class with implemented methods expressing the quadratic expression
*  - Pseudorandom class with implemented methods that uses the linear congruence method to produce a random number
*  - Rational class with implemented methods to formulate two rational numbers
*  - Statistician class with implemented methods to perform calculatiosn on a sequence of values
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