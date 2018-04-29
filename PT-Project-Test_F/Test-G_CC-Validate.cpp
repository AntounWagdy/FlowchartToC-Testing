#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Validate.h"
#include"../PT-Project/Statements/Statement.h"

TEST_F(ActionGACC , ValidateExecute_TEST_1) {
	Validate *a = new Validate(App);
	
	Start_End *st = new Start_End(Point(500, 500), 0);
	SmplAssign *st2 = new SmplAssign(Point(), "", 12);
	SmplAssign *st3 = new SmplAssign(Point(), "", 12);
	Conditional *st4 = new Conditional(Point(50,50),"","",12,"",1);
	Conditional *st5 = new Conditional(Point(50, 50), "", "", 12, "", 1);
	Conditional *st6 = new Conditional(Point(50, 50), "", "", 12, "", 1);
	Start_End *st7 = new Start_End(Point(500, 500), 1);

	Connector *c1 = new Connector(st, st2, false);
	Connector *c2 = new Connector(st2 , st4, false);
	Connector *c3 = new Connector(st4, st7, false);
	Connector *c4 = new Connector(st4, st7, false);
	Connector *c5 = new Connector(st5, st7, false);

	App->AddStatement(st);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);
	App->AddStatement(st5);
	App->AddStatement(st6);
	App->AddStatement(st7);

	App->AddConnector(c1);
	App->AddConnector(c2);
	App->AddConnector(c3);
	App->AddConnector(c4);
	App->AddConnector(c5);

	EXPECT_CALL(*out,PrintMessage("Your FlowChart is not fully connected, check missing connectors!"));
	a->Execute();
}

TEST_F(ActionGACC, ValidateExecute_TEST_2) {
	Validate *a = new Validate(App);
	Start_End *st1 = new Start_End(Point(500, 500), 0);
	Start_End *st2 = new Start_End(Point(500, 500), 1);
	
	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddConnector(new Connector(st2,st1,false));
	
	EXPECT_CALL(*out, PrintMessage("Congratulation, your flow chart is valid, you can debug, run or generate your code :D "));

	a->Execute();
}

TEST_F(ActionGACC, ValidateExecute_TEST_3) {
	Validate *a = new Validate(App);
	Start_End *st1 = new Start_End(Point(500, 500), 0);
	Conditional *st2 = new Conditional(Point(),"","",12,"",1);
	SmplAssign * st3 = new SmplAssign(Point(), "", 12);
	Start_End *st4 = new Start_End(Point(500, 500), 1);
	SmplAssign * st5 = new SmplAssign(Point(), "", 12);


	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);
	App->AddStatement(st5);

	App->AddConnector(new Connector(st4, st2, false));
	App->AddConnector(new Connector(st2, st3, false));
	App->AddConnector(new Connector(st3, st2, false));
	App->AddConnector(new Connector(st2, st5, false));
	App->AddConnector(new Connector(st5, st2, false));


	EXPECT_CALL(*out, PrintMessage("Your FlowChart is not fully connected, check missing connectors!"));

	a->Execute();
}



TEST_F(ActionGACC, ValidateExecute_TEST_4) {
	Validate *a = new Validate(App);
	Start_End *st1 = new Start_End(Point(500, 500), 0);
	SmplAssign * st3 = new SmplAssign(Point(), "", 12);
	SmplAssign * st4 = new SmplAssign(Point(), "", 12);
	Start_End *st5 = new Start_End(Point(500, 500), 1);
	

	App->AddStatement(st1);
	App->AddStatement(st5);
	App->AddStatement(st3);
	App->AddStatement(st4);
	
	App->AddConnector(new Connector(st1, st3, false));
	App->AddConnector(new Connector(st4, st5, false));
	

	EXPECT_CALL(*out, PrintMessage("Your FlowChart is not fully connected, check missing connectors!"));

	a->Execute();
	EXPECT_TRUE(!a->getVaild());
}