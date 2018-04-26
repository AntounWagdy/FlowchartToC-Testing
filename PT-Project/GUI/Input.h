#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include<sstream>
#include<gtest\gtest.h>
#include<gmock\gmock.h>

class Output;
class Input		//The application manager should have a pointer to this class
{
protected:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	virtual void GetPointClicked(Point &P) const;//Gets coordinate where user clicks
	
	virtual double GetValue(Output* pO) const;	// Reads a double value from the user 

	virtual string GetString(Output* pO) const ; //Returns a string entered by the user

	virtual ActionType GetUserAction() const; //Reads the user click and maps it to an action

	virtual ~Input();
};

#endif