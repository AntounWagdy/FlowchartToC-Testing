#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"

#include "Statement.h"
#include<gtest\gtest.h>

class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	bool Selected;
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	int def;
public:
	FRIEND_TEST(ConnectorEdgeCoverage, Constructor);
	FRIEND_TEST(ConnectorEdgeCoverage, SettersAndGetters);

	Connector(Statement* Src, Statement* Dst,bool);
	
	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	virtual void Draw(Output* pOut);

	virtual void PrintInfo(Output*);
	
	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
};

#endif