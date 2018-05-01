#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Delete.h"
#include"../PT-Project/Statements/SmplAssign.h"
TEST_F(ActionEdgeCoverage,Delete_Execute_Test1) {	
	EXPECT_CALL(*out, PrintMessage("There is no Statements to Delete !"));
	Delete* a = new Delete(App);
	a->Execute();
}

TEST_F(ActionEdgeCoverage, Delete_Execute_Test2) {
	Delete* a = new Delete(App);
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("N")).WillOnce(Return("y"));
	App->AddStatement(new SmplAssign());
	App->AddStatement(new SmplAssign());

	App->AddConnector(new Connector(new SmplAssign(), new SmplAssign(), false));
	App->AddConnector(new Connector(new SmplAssign(), new SmplAssign(), false));
 
	in->setPoint(Point(500, 500));
	in->setPoint(Point(500, 500));
	EXPECT_CALL(*out, PrintMessage("Please Select a statement to delete")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Do you want to clear all the area? (Y/N) ")).Times(2);

	a->Execute();

	EXPECT_EQ(App->Statementcurrent(), 0);
	EXPECT_EQ(App->Connectorcurrent(), 0);
}


TEST_F(ActionEdgeCoverage, Delete_Execute_Test3) {
	Delete *a = new Delete(App);
	
	// Statement Exist => delete statement and its connectors out and in.
	SmplAssign* st1 = new SmplAssign(Point(500, 500));
	SmplAssign* st2 = new SmplAssign(Point(500, 600));
	SmplAssign* st3 = new SmplAssign(Point(500, 700));

	Connector *c1 = new Connector(st1, st2,false);
	Connector *c2 = new Connector(st2, st3, false);

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);

	App->AddConnector(c1);
	App->AddConnector(c2);

	in->setPoint(Point(501, 601));
	
	a->Execute();
	
	EXPECT_EQ(App->Statementcurrent(),2);
	EXPECT_EQ(App->Statementlist()[0], st1);
	EXPECT_EQ(App->Statementlist()[1], st3);

	EXPECT_EQ(App->Connectorcurrent(), 0);

}

TEST_F(ActionEdgeCoverage, Delete_Execute_Test4) {
	Delete *a = new Delete(App);

	// Statement Exist => delete statement and its connectors out and in.
	SmplAssign* st1 = new SmplAssign(Point(500, 500));
	SmplAssign* st2 = new SmplAssign(Point(500, 600));
	SmplAssign* st3 = new SmplAssign(Point(500, 700));

	Connector *c1 = new Connector(st1, st3, false);
	
	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);

	App->AddConnector(c1);
	
	in->setPoint(Point(501, 601));

	a->Execute();

	EXPECT_EQ(App->Statementcurrent(), 2);
	EXPECT_EQ(App->Statementlist()[0], st1);
	EXPECT_EQ(App->Statementlist()[1], st3);

	EXPECT_EQ(App->Connectorcurrent(), 1);

}


TEST_F(ActionEdgeCoverage, Delete_Execute_Test5) {
	// Connector Exist
	Delete *a = new Delete(App);

	// Statement Exist => delete statement and its connectors out and in.
	SmplAssign* st1 = new SmplAssign(Point(500, 500));
	SmplAssign* st3 = new SmplAssign(Point(500, 700));

	Connector *c1 = new Connector(st1, st3, false);

	App->AddStatement(st1);
	App->AddStatement(st3);

	App->AddConnector(c1);
	Point *par;
	int size;
	st1->getOut(par,size);
	in->setPoint(Point(par[0].x, par[0].y+1));

	a->Execute();

	EXPECT_EQ(App->Statementcurrent(), 2);
	EXPECT_EQ(App->Connectorcurrent(), 0);
}




