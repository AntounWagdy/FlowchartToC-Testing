#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Run.h"
#include"../PT-Project/Statements/Statement.h"


TEST_F(ActionEdgeCoverage,Run_Execute_Test1) {
	
	Action*a = new Run_Action(App);

	ReadWrite *st = new ReadWrite(Point(500,500),"x",true);// Read Statement
	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(1));

	Start_End *st2 = new Start_End(Point(500, 550),1);//start
	Start_End *st3 = new Start_End(Point(500, 550), 0);//End

	ReadWrite *st4 = new ReadWrite(Point(500, 500), "x", false);// Read Statement
	Conditional * st5 = new Conditional(Point(50, 50), "x", "==", 2, "", 1);

	Connector *c1 = new Connector(st2, st,false);
	Connector *c2 = new Connector(st, st5, false);
	Connector *c3 = new Connector(st5, st4, false);
	Connector *c4 = new Connector(st5, st4, false);
	Connector *c5 = new Connector(st4, st3, false);

	App->AddConnector(c1);
	App->AddConnector(c2);
	App->AddConnector(c3);
	App->AddConnector(c4);
	App->AddConnector(c5);

	App->AddStatement(st);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);
	App->AddStatement(st5);
	
	EXPECT_CALL(*out, PrintMessage("Enter the value of x :"));
	EXPECT_CALL(*out, PrintMessage("1                        //Output"));
	EXPECT_CALL(*out, PrintMessage("Program has exited with code of 0*0"));

	a->Execute();
}

TEST_F(ActionEdgeCoverage, Run_Execute_Test2) {

	Action*a = new Run_Action(App);

	Start_End *st2 = new Start_End(Point(500, 550), 1);//start
	Start_End *st3 = new Start_End(Point(500, 550), 0);//End

	ReadWrite *st4 = new ReadWrite(Point(500, 500), "x", false);// Read Statement
	Conditional * st5 = new Conditional(Point(50, 50), "x", "==", 2, "", 1);

	Connector *c1 = new Connector(st2, st5, false);
	Connector *c3 = new Connector(st5, st4, false);
	Connector *c4 = new Connector(st5, st4, false);
	Connector *c5 = new Connector(st4, st3, false);

	App->AddConnector(c1);
	App->AddConnector(c3);
	App->AddConnector(c4);
	App->AddConnector(c5);
	
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);
	App->AddStatement(st5);

	EXPECT_CALL(*out, PrintMessage("Undeclared identifier. Aborting ..."));
	a->Execute();
}


TEST_F(ActionEdgeCoverage, Run_Execute_Test3) {

	Action*a = new Run_Action(App);

	Start_End *st2 = new Start_End(Point(500, 550), 1);//start
	Start_End *st3 = new Start_End(Point(500, 550), 0);//End

	ReadWrite *st4 = new ReadWrite(Point(500, 500), "x", false);// Read Statement
	
	Connector *c1 = new Connector(st2, st4, false);
	Connector *c5 = new Connector(st4, st3, false);

	App->AddConnector(c1);
	App->AddConnector(c5);

	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);
	
	EXPECT_CALL(*out, PrintMessage("Undeclared identifier. Aborting !!!"));
	a->Execute();
}

TEST_F(ActionEdgeCoverage, Run_Execute_Test4) {

	Action*a = new Run_Action(App);

	Start_End *st2 = new Start_End(Point(500, 550), 1);//start
	Start_End *st3 = new Start_End(Point(500, 550), 0);//End

	ReadWrite *st4 = new ReadWrite(Point(500, 500), "", false);// Read Statement

	Connector *c1 = new Connector(st2, st4, false);
	Connector *c5 = new Connector(st4, st3, false);

	App->AddConnector(c1);
	App->AddConnector(c5);

	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);

	EXPECT_CALL(*out, PrintMessage("Some variablesare wrong. Aborting..."));
	a->Execute();
}