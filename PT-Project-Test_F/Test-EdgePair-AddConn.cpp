#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Add_Conn.h"


TEST_F(ActionEdgePairCoverage, AddCond_ReadActionParams_TEST1) {
	Add_Conn *a = new Add_Conn(App);
	Statement * st1 = new SmplAssign(Point(500,500),"A",23);
	Statement * st2 = new SmplAssign(Point(500, 600), "W", 23);
	
	App->AddStatement(st1);
	App->AddStatement(st2);


	in->setPoint(Point(200,200));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 601));

	EXPECT_CALL(*out,PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	a->ReadActionParameters();
}


TEST_F(ActionEdgePairCoverage, AddCond_ReadActionParams_TEST2) {
	Add_Conn *a = new Add_Conn(App);
	Conditional * st = new Conditional(Point(200,200),"","",12,"",1);
	Statement * st1 = new SmplAssign(Point(500, 500), "A", 23);
	Statement * st2 = new SmplAssign(Point(500, 600), "W", 23);

	Connector *c1 = new Connector(st, st1,false);
	Connector *c2 = new Connector(st, st1, false);

	App->AddStatement(st);
	App->AddStatement(st1);
	App->AddStatement(st2);

	App->AddConnector(c1);
	App->AddConnector(c2);


	in->setPoint(st->getIn());
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 601));

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	a->ReadActionParameters();
}
