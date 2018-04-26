#include"../PT-Project/Actions/Add_Conn.h"
#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Statements/Statement.h"
#include"../PT-Project/Statements/Conditional.h"

TEST_F(ActionGICC,AddConn_ReadParams_TEST_1) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Statement *st1 = new SmplAssign(Point(500, 500),"",0); 
	Statement *st2 = new SmplAssign(Point(500, 700), "",0);

	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);
	
	a->ReadActionParameters();
}


TEST_F(ActionGICC, AddConn_ReadParams_TEST_2) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : ")).Times(2);

	Statement *st1 = new Start_End(Point(500, 500), 1); // start
	Statement *st2 = new Start_End(Point(500, 700),0);

	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);

	a->ReadActionParameters();
}



TEST_F(ActionGICC, AddConn_ReadParams_TEST_3) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : ")).Times(2);

	Statement *st1 = new Start_End(Point(500, 500), 1);
	Statement *st2 = new Start_End(Point(500, 700), 0);

	in->setPoint(Point(501, 701));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);

	a->ReadActionParameters();
}


TEST_F(ActionGICC, AddConn_ReadParams_TEST_4) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Statement *st1 = new Start_End(Point(400, 400), 1);
	Statement *st2 = new Start_End(Point(500, 500), 1);
	Statement *st3 = new Start_End(Point(500, 700), 0);
	Connector *c = new Connector(st1, st2, false);

	in->setPoint(Point(401, 401));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddConnector(c);

	a->ReadActionParameters();
}

TEST_F(ActionGICC, AddConn_ReadParams_TEST_5) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Statement *st1 = new SmplAssign(Point(500, 500), "", 0);
	Statement *st2 = new SmplAssign(Point(500, 700), "", 0);


	in->setPoint(Point(400,400));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);

	a->ReadActionParameters();
}

TEST_F(ActionGICC, AddConn_ReadParams_TEST_6) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : ")).Times(2);

	Statement *st1 = new SmplAssign(Point(500, 500), "", 0);
	Statement *st2 = new SmplAssign(Point(500, 700), "", 0);

	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);

	a->ReadActionParameters();
}

TEST_F(ActionGICC, AddConn_Execute_TEST_1) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Statement *st1 = new SmplAssign(Point(500, 500), "", 0);
	Statement *st2 = new Start_End(Point(500, 750), 1);
	Statement *st3 = new Start_End(Point(500, 700), 0);


	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddStatement(st3);

	a->Execute();
}


TEST_F(ActionGACC, AddConn_Execute_TEST_2) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Statement *st2 = new Start_End(Point(500, 750), 1);
	Statement *st3 = new Start_End(Point(500, 700), 0);


	in->setPoint(st2->getIn());
	in->setPoint(st3->getIn());

	App->AddStatement(st2);
	App->AddStatement(st3);

	a->Execute();
}
