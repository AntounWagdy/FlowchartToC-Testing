#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include<fstream>
#include<map>
#include<gtest\gtest.h>

class Connector;

//Base class for all Statements
class Statement
{
protected:
	static int static_ID;
	int ID;			//Each Statement has an ID
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	bool Selected;	//true if the statement is selected on the folwchart
	string C;

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

public:
	FRIEND_TEST(StatementEdgeCoverage, Constructor);
	Statement();

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	virtual void setConn(Connector* x) = 0;
	virtual void getConn(Connector**&arr,int & size) = 0; //Return Array of pointers to connectors with its size
	virtual Point getIn() = 0; //Get Inlet Point
	virtual void getOut(Point *&P,int &size) = 0; //Get Outlet Point


	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual int Run(map<string,double>&)=0;	//Execute the statement in the simulation mode
	
	virtual void PrintInfo(Output* pOut) = 0;	//print all Statement info on the status bar
	//(to be tested ba3den)
	void Comment(string);
	string GetComment();

	virtual Point getCorner() = 0; //Get left Corner Point
	virtual Point width_height() = 0; //Return Width and height of the statement

	int getID(){ return this->ID; }
	void SetID(int y) { ID = y; }


	//Validations 
	bool IsValid(string s); //Valid variable name
};
#endif