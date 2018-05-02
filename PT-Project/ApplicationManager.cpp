#include "ApplicationManager.h"
#include<cmath>

///////////////////////////////////////////// Actions Include////////////////////////////
#include "Actions\AddSmplAssign.h"
#include"Actions\Add_Conn.h"
#include"Actions\Add_Start_End.h"
#include"Actions\AddCond.h"
#include"Actions\AddReadWrite.h"
#include"Actions\AddVariable.h"
#include"Actions\Comment.h"
#include"Actions\Delete.h"
#include"Actions\Load.h"
#include"Actions\Run.h"
#include"Actions\Save.h"
#include"Actions\Validate.h"
//////////////////////////////////////////////////////////////////////////////


#include "GUI\Input.h"
#include "GUI\Output.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output();
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;

	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType){
		case ADD_SMPL_ASSIGN:
			pAct = new AddSmplAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddCond(this);
			break;

		case SELECT:
			break;

		case EXIT:
			return;

		case STATUS: //If user clicked in status Bar 
			return;

		case No_Action: //free click
			return;
		
		case ADD_Single_OP:
			break;
		
		case ADD_One_Variable:
			pAct = new AddVariable(this);
			break;
		case ADD_CONNECTOR:
			pAct = new Add_Conn(this);
			break;
		case EDIT_STAT:
			break;
		case EDIT_CONN:
			break;
		case MULTI_SELECT:
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case MOVE:
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new Load(this);
			break;
		case DSN_MODE:
			pOut->CreateDesignToolBar();
			break;
		case SIM_MODE:
			pOut->CreateSimulationToolBar();
			break;
		case ADD_ellipse_start:
			pAct = new Add_Start_End(this,1);
			break;
		case ADD_ellipse_END:
			pAct = new Add_Start_End(this, 0);
			break;
		case ADD_Read:
			pAct = new AddReadWrite(this, true);
			break;
		case ADD_Write:
			pAct = new AddReadWrite(this, false);
			break;
		case COPY:
			break;
		case CUT:
			break;
		case COMMENT:
			pAct = new Comment(this);
			break;
		case RUN:
			pAct = new Validate(this);
			pAct->Execute();
			if (((Validate*)pAct)->getVaild())
			{
				delete pAct;
				pAct = new Run_Action(this);
			}
			else { // BUG 6
				delete pAct;
				pAct = NULL;
			}
			break;
		case DEBUG:
			break;
		case VALID:
			pAct = new Validate(this);
			break;
		case Generate:
			break;
		}

	//Execute the created action
	if(pAct != NULL){
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	for (int i = 0; i < StatCount;i++) 
	{
		if (dynamic_cast<Conditional*>(StatList[i])) // Conditional Statement
		{
			if (P.x >= StatList[i]->getCorner().x && (P.x <= StatList[i]->getCorner().x + (1.4*StatList[i]->width_height().x)*sqrt(2)) && (P.y >= StatList[i]->getCorner().y) && (P.y <= StatList[i]->getCorner().y + (1.4*StatList[i]->width_height().y)*sqrt(2)))
			return StatList[i];
		}
		else if ((P.x >= StatList[i]->getCorner().x) && (P.x <= StatList[i]->getCorner().x + StatList[i]->width_height().x) && (P.y >= StatList[i]->getCorner().y) && (P.y <= StatList[i]->getCorner().y + StatList[i]->width_height().y))
			return StatList[i];
	}
	return NULL;
}

//==================================================================================//
//						Connectors Management Functions								//
//==================================================================================//

void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}



//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++)
		delete ConnList[i];

	delete pIn;
	delete pOut;	
}

bool ApplicationManager::IsPointBetween(Point q, Point w, Point e) const
{
	if (q.x >= min(w.x,e.x)&&q.x <= max(w.x,e.x)&&q.y >= min(w.y,e.y)&&q.y <= max(w.y,e.y))
		return true;
	else return false;

}


Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->getStartPoint().y > ConnList[i]->getEndPoint().y)
		{
			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10), Point(ConnList[i]->getStartPoint().x + 100, ConnList[i]->getStartPoint().y +10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x + 100, ConnList[i]->getStartPoint().y +10), Point(ConnList[i]->getStartPoint().x+100, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x+100, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
		else if (ConnList[i]->getStartPoint().y < ConnList[i]->getEndPoint().y)
		{

			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y+10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getStartPoint().y + 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getStartPoint().y + 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y-5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
		else if (ConnList[i]->getStartPoint().y == ConnList[i]->getEndPoint().y)
		{
			if (IsPointBetween(P, ConnList[i]->getStartPoint(), Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getStartPoint().x, ConnList[i]->getStartPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10))
				|| IsPointBetween(P, Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 10), Point(ConnList[i]->getEndPoint().x, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x - 5, ConnList[i]->getEndPoint().y - 5))
				|| IsPointBetween(P, ConnList[i]->getEndPoint(), Point(ConnList[i]->getEndPoint().x + 5, ConnList[i]->getEndPoint().y - 5))
				)
				return ConnList[i];
		}
	}
	return NULL;
}




void ApplicationManager::DeleteConnector(Connector *C)
{
	Connector**arr; int n;
	C->getSrcStat()->getConn(arr, n);
	if (n == 1)
		C->getSrcStat()->setConn(NULL); 
	else if (n == 2)
	{
		if (arr[0] == C) 
			((Conditional*)(C->getSrcStat()))->setFConn(NULL);
		else
			((Conditional*)(C->getSrcStat()))->setSConn(NULL);
	}


	for (int i = 0; i < ConnCount;i++)
		if (ConnList[i] == C)
		{
			delete ConnList[i];
			ConnList[i] = ConnList[ConnCount - 1];
			ConnList[ConnCount - 1] = NULL;
			ConnCount--;
			break;
		}
}
void ApplicationManager::DeleteStatement(Statement *S)
{
	for (int i = 0; i < StatCount; i++)
		if (StatList[i] == S)
		{
			delete StatList[i];
			StatList[i] = StatList[StatCount - 1];
			StatList[StatCount- 1] = NULL;
			StatCount--;
			break;
		}
}



void ApplicationManager::Loading(ifstream &In)
{
	int I, L;
	map<int, int>m;
	
//	In >> I; //BUG #01

	if (In.is_open())
	{
		In >> I;
		string Type;
		for (int i = 0; i<I; i++)
		{
			In >> Type;

			if (Type == "STRT")
			{
				Statement*S = new Start_End();
				AddStatement(S);
				(dynamic_cast<Start_End*>(S))->SetLoad(true);
				S->Load(In);
			}
			else if (Type == "END")
			{
				Statement*S = new Start_End();
				AddStatement(S);
				(dynamic_cast<Start_End*>(S))->SetLoad(false);
				S->Load(In);
			}
			else if (Type == "VARIABLE")
			{
				Statement*S = new Variable();
				AddStatement(S);
				S->Load(In);
			}
			else if (Type == "SmplAssign")
			{
				Statement*S = new SmplAssign();
				AddStatement(S);
				S->Load(In);
			}
			else if (Type == "READ")
			{
				Statement*S = new ReadWrite();
				AddStatement(S);
				(dynamic_cast<ReadWrite*>(S))->SetR_Load(true);
				S->Load(In);
			}
			else if (Type == "WRITE")
			{
				Statement*S = new ReadWrite();
				AddStatement(S);
				(dynamic_cast<ReadWrite*>(S))->SetR_Load(false);
				S->Load(In);
			}
			else if (Type == "COND")
			{
				Statement*S = new Conditional();
				AddStatement(S);
				S->Load(In);
			}
		}
		In >> L;

		int I1, I2, I3;
		Statement*S = NULL;
		Statement*D = NULL;
		for (int t = 0; t < L; t++)
		{
			In >> I1 >> I2 >> I3;
			if (I3 == 0 || I3 == 1)
			{
				for (int i = 0; i < StatCount; i++)
				{
					if (StatList[i]->getID() == I1)
						S = StatList[i];
				}
				for (int j = 0; j < StatCount; j++)
				{
					if (StatList[j]->getID() == I2)
						D = StatList[j];
				}
				Connector*C = new Connector(S, D, false);
				AddConnector(C);

			}
			else 
				m[I1] = I2;
		}

		map<int, int>::iterator it;
		for ( it = m.begin(); it !=m.end(); it++)
		{
			for (int i = 0; i < StatCount; i++)
			{
				if (StatList[i]->getID() ==it->first )
					S = StatList[i];
			}
			for (int j = 0; j < StatCount; j++)
			{
				if (StatList[j]->getID() ==it->second )
					D = StatList[j];
			}
			Connector*C = new Connector(S, D, false);
			AddConnector(C);
		}
	}
}