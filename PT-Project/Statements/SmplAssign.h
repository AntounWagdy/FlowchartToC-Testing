#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"
#include<gtest\gtest.h>

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	FRIEND_TEST(smplAssignEdgeCoverage, firstConstructor);
	FRIEND_TEST(smplAssignEdgeCoverage, UpdateStatementText);
	FRIEND_TEST(smplAssignEdgeCoverage, SettersAndGetters);
	FRIEND_TEST(smplAssignEdgeCoverage, Load);

	SmplAssign(Point Lcorner, string LeftHS="", double RightHS=0);
	SmplAssign(){}

	void setLHS(const string &L);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;
	
	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);

	virtual void PrintInfo(Output*);
	
	virtual Point getCorner(){ return this->LeftCorner; }
	virtual Point width_height(){ return Point(UI.ASSGN_WDTH, UI.ASSGN_HI); }

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	void Load(ifstream&In);
	virtual int Run(map<string, double>&);
};

#endif