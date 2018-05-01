#pragma once

#include "Statement.h"

class Start_End: public Statement 
{
private:
	Connector *Conn;
	Point In;
	Point Out;
	Point LeftCorner;
	int St_En;
	bool D_load;
	virtual void UpdateStatementText();

public:
	FRIEND_TEST(StartEndEdgeCoverage, FirstConstructor);
	FRIEND_TEST(StartEndEdgeCoverage, SettersAndGetters);
	FRIEND_TEST(StartEndEdgeCoverage, load);

	Start_End(Point,int);
	Start_End(){}

	virtual void Draw(Output* pOut) const;
	int getKind(){ return St_En; }


	virtual void setConn(Connector*);
	virtual void getConn(Connector **&arr, int &size);
	virtual Point getIn();
	virtual void getOut(Point * &P, int &size);

	virtual void PrintInfo(Output*);

	virtual Point getCorner(){ return this->LeftCorner; }
	virtual Point width_height(){ return Point(UI.EllipseWidth, UI.EllipseH); }

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	
	
	virtual void Load(ifstream & In);
	virtual int Run(map<string, double> &m){ return 1; }
	void SetLoad(bool b) { D_load = b;}
};