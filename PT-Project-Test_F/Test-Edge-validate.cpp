#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Validate.h"
#include"../PT-Project/Statements/Statement.h"

TEST_F(ActionEdgeCoverage,Validate_Execute_Test1) {
	Validate * a = new Validate(App);
	EXPECT_CALL(*out, PrintMessage("FlowChart Can't contain more/less than one Start!"));
	a->Execute();
	EXPECT_FALSE(a->getVaild());
}

TEST_F(ActionEdgeCoverage, Validate_Execute_Test2) {
	Validate * a = new Validate(App);
	Start_End *st = new Start_End(Point(500,500),1);
	App->AddStatement(st);
	EXPECT_CALL(*out, PrintMessage("FlowChart Can't contain more/less than one End!"));
	a->Execute();
	EXPECT_FALSE(a->getVaild());
}




TEST_F(ActionEdgeCoverage, Validate_Execute_Test3) {
	Validate*a = new Validate(App);

	ReadWrite *st = new ReadWrite(Point(500, 500), "x", true);// Read Statement
	
	Start_End *st2 = new Start_End(Point(500, 550), 1);//start
	Start_End *st3 = new Start_End(Point(500, 550), 0);//End

	ReadWrite *st4 = new ReadWrite(Point(500, 500), "x", false);// Read Statement
	Conditional * st5 = new Conditional(Point(50, 50), "x", "==", 2, "", 1);

	Connector *c1 = new Connector(st2, st, false);
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

	a->Execute();
	EXPECT_TRUE(a->getVaild());
}
TEST_F(ActionEdgeCoverage, Validate_Execute_Test4) {
	Validate * a = new Validate(App);
	Start_End *st1 = new Start_End(Point(500, 500), 1);
	Start_End *st2 = new Start_End(Point(500, 500), 0);
	SmplAssign *st3 = new SmplAssign(Point(500, 500));

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddConnector(new Connector(st1, st2,false));

	EXPECT_CALL(*out, PrintMessage("Your FlowChart is not fully connected, check missing connectors!"));
	a->Execute();
	EXPECT_FALSE(a->getVaild());
}


TEST_F(ActionEdgeCoverage, Validate_Execute_Test5) {
	Validate *a = new Validate(App);
	Start_End *st1 = new Start_End(Point(500, 500), 1);
	Start_End *st2 = new Start_End(Point(500, 500), 0);
	Conditional *st3 = new Conditional(Point(500, 500),"","",1,"",1);

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddConnector(new Connector(st1, st3, false));
	App->AddConnector(new Connector(st3, st2, false));


	EXPECT_CALL(*out, PrintMessage("Your FlowChart is not fully connected, check missing connectors!"));
	a->Execute();
	EXPECT_FALSE(a->getVaild());
}