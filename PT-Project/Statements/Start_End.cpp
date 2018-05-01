#include "Start_End.h"
#include <sstream>
#include <iostream>
using namespace std;

Start_End::Start_End(Point Lcorner, int s )// if s=0 draw end, if s=1 draw start //
{
	LeftCorner = Lcorner;
	St_En = s;
	UpdateStatementText();
	Conn= NULL;	//No connectors yet
	In.x = LeftCorner.x + UI.EllipseWidth /2;
	In.y = LeftCorner.y;

	Out.x = In.x;
	Out.y = LeftCorner.y + UI.EllipseH;	

	D_load = false;
}

void Start_End::Draw(Output* pOut) const
{
	pOut->DrawEllipse(LeftCorner,UI.EllipseWidth,UI.EllipseH,Text,Selected);
}



void Start_End::PrintInfo(Output*Pout) 
{
	ostringstream S;
	S<<"ID = "<<ID<<", Comment: "<< C;  // BUG #5 C was the connector here
 	if (St_En == 0)
		S << " End statement !";
	else 
		S<<"Start statement!";
	Pout->PrintMessage(S.str());
}

void Start_End::UpdateStatementText()
{
	if(St_En==1)
		Text="Start";
	else if(St_En == 0)
		Text="End";
}



void Start_End::setConn(Connector*x)
{ Conn = x; }
void Start_End::getConn(Connector **&arr, int &size)
{ 
	size = 1;
	arr = new Connector*[size];
	arr[0] = Conn;
}
Point Start_End::getIn()
{ return In; }
void Start_End::getOut(Point * &P, int &size)
{ 
	size = 1;
	P = new Point[size];
	P[0] = Out; 
}


void Start_End::Save(ofstream &OutFile)
{
	if (St_En == 1)
		OutFile << "STRT" << "   " << ID << "   " << LeftCorner.x + UI.EllipseWidth / 2 << "   " << LeftCorner.y + UI.EllipseH / 2 << "   " << GetComment() << endl;
	else
		OutFile << "END" << "   " << ID << "   " << LeftCorner.x + UI.EllipseWidth / 2 << "   " << LeftCorner.y + UI.EllipseH / 2 << "   " << GetComment() << endl;
}

void Start_End::Load(ifstream & InFile)
{
	//LOAD
	int I, x, y;
	string S;
	if (D_load)
	{
		St_En = 1;
		UpdateStatementText();
		InFile >> I >> x >> y >> S;
		SetID(I); Comment(S);
		LeftCorner.x = x - UI.EllipseWidth / 2;
		LeftCorner.y = y - UI.EllipseH / 2;

	}
	else
	{
		St_En = 0;
		UpdateStatementText();
		InFile >> I >> x >> y >> S;
		SetID(I); Comment(S);
		LeftCorner.x = x - UI.EllipseWidth / 2;
		LeftCorner.y = y - UI.EllipseH / 2;

	}

	//Inlet & Outlet
	Conn = NULL;	//No connectors yet
	In.x = LeftCorner.x + UI.EllipseWidth / 2;
	In.y = LeftCorner.y;

	Out.x = In.x;
	Out.y = LeftCorner.y + UI.EllipseH;



}