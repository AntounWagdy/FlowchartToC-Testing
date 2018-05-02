#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:

	friend class TEST_FIXTURE; // to get windows in test to init input
	friend class TEST_FIXTURE_2; // to get windows in test to init input
	friend class TEST_FIXTURE_3; // to get windows in test to init input
	friend class TEST_FIXTURE_4; // to get windows in test to init input

	FRIEND_TEST(GUIEdgeCoverage, outputConstructor);

	Output();	

	window* CreateWind(int, int, int , int);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode

	void CreateStatusBar();

	virtual Input* CreateInput(); //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area

	// -- Statements Drawing Functions
	virtual void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);
	virtual void DrawCond(Point Center,int length, string Text, bool Selected = false);
	virtual void DrawConn(Point p1, Point p2, bool selected = false);
	virtual void DrawEllipse(Point Left,int ,int , string Text, bool Selected = false);

	virtual void DrawRead(Point left, int width, int height, string text, bool selected = false);
	virtual void DrawWrite(Point left, int width, int height, string text, bool selected = false);

		
	virtual void PrintMessage(string msg);	//Prints a message on Status bar
	
	~Output();
};

#endif