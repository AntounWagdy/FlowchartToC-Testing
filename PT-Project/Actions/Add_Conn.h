#include"..\Statements\Connector.h"

#include"Action.h"
#include<gtest\gtest.h>

class Add_Conn :public Action
{
	Statement* S;
	Statement* D;
public:
	FRIEND_TEST(ActionEdgeCoverage, AddConn_ReadParameters_TEST1);
	FRIEND_TEST(ActionEdgeCoverage, AddConn_ReadParameters_TEST2);
	FRIEND_TEST(ActionEdgeCoverage, AddConn_Execute_TEST2);

	Add_Conn(ApplicationManager* pAppManager) : Action(pAppManager){}

	virtual void ReadActionParameters();
	virtual void Execute();

};