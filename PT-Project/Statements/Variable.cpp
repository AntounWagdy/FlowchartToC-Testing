#include"Variable.h"


Variable::Variable(Point Lcorner, string LeftHS, string RightHS)
{
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Variable::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void Variable::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}


void Variable::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}


//This function should be called when LHS or RHS changes
void Variable::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS;
		Text = T.str();
	}

}


void Variable::PrintInfo(Output*Pout)
{
	ostringstream S;
	S << "ID = " << ID << ", Comment: " << C;
	Pout->PrintMessage(S.str());
}




void Variable::setConn(Connector*x)
{ pConn = x; }


void Variable::getConn(Connector **&arr, int &size)
{
	size = 1; 
	arr = new Connector*[size];
	arr[0] = pConn;
}


Point Variable::getIn()
{ return Inlet; }

void Variable::getOut(Point * &P, int &size)
{
	size = 1;
	P = new Point[size];
	P[0] = Outlet;
}


void Variable::Save(ofstream &OutFile)
{
	OutFile << "VARIABLE" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "   " << this->RHS << "     " << GetComment() << endl;
}



void Variable::Load(ifstream& In)
{
	int I;
	string C, L, R;
	In >> I >> LeftCorner.x >> LeftCorner.y >> L >> R >> C;
	Comment(C);
	SetID(I);
	setLHS(L); setRHS(R);


	//Inlet & Outlet

	//UpdateStatementText();

	pConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}


int Variable::Run(map<string, double> &Vars)
{
	if (RHS==""||LHS=="") 
		return 3;
	else if (Vars.find(RHS) == Vars.end())
		return 0;
	else
	{
		Vars[LHS] = Vars[RHS];
		return 1;
	}

}

