#pragma once

#include"Statement.h"
#include<gtest\gtest.h>

class Conditional :
	public Statement
{

private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS1;	//Right Handside (Value)
	string RHS2;   //Right Handside (Variable)
	string Op;
	double def;

	Connector *pConn[2];	//Conditional Stat. has Two Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet[2];	//A point a connection leaves this statement

	Point center;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	string Operator(string);
public:
	/*To make test access the data*/
	FRIEND_TEST(ConditionalEdgeCoverage, FirstConstructor);
	FRIEND_TEST(ConditionalEdgeCoverage, updateStatementText);
	FRIEND_TEST(ConditionalEdgeCoverage, Operator);
	FRIEND_TEST(ConditionalEdgeCoverage, OperatorS);
	FRIEND_TEST(ConditionalEdgeCoverage, settersANDgetters);
	FRIEND_TEST(ConditionalEdgeCoverage, Save);
	FRIEND_TEST(ConditionalEdgeCoverage, Load_TEST_1);
	FRIEND_TEST(ConditionalEdgeCoverage, Load_TEST_2);
	FRIEND_TEST(ConditionalEdgeCoverage, Run);

	Conditional(Point center, string LeftHS ,string op ,double RightHS1,string RightHS2,double);
	
	Conditional(){}
	void setLHS(const string &L);
	void setRHS(double R);
	void setRHS(string R);
	void setOp(string p);
	
	virtual void Draw(Output* pOut) const;

	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);


	virtual void PrintInfo(Output*);

	virtual Point getCorner();
	virtual Point width_height();

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	
	
	virtual void Load(ifstream &In);
	void Operator_S(string x);

	virtual int Run(map<string,double>&);
	
	void setFConn(Connector*x){ pConn[0] = x; }
	void setSConn(Connector*x){ pConn[1] = x; }

	void SetCenter(int x, int Temp, int U);
};
