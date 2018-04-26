#include"../PT-Project/Actions/Add_Conn.h"
#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Statements/Start_End.h"
#include"../PT-Project/Statements/Conditional.h"


TEST_F(ActionEdgeCoverage, AddConn_ReadParameters_TEST1) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : "));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : "));

	Start_End *st1 = new Start_End(Point(500,500),1); //s-1 => start
	Start_End *st2 = new Start_End(Point(500, 700), 0); //s-0 => end

	in->setPoint(Point(501, 501));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);


	a->ReadActionParameters();
	
	EXPECT_EQ(a->S,st1);
	EXPECT_EQ(a->D, st2);
}



TEST_F(ActionEdgeCoverage, AddConn_ReadParameters_TEST2) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : ")).Times(2);

	Conditional *st1 = new Conditional(Point(500,500),"","", 12 , "2" ,1); //s-1 => start
	st1->setConn(new Connector(new Conditional(),new Conditional(),false));
	Start_End *st2 = new Start_End(Point(500, 700), 0); //s-0 => end


	in->setPoint(Point(400,400));
	in->setPoint(Point(500,458));

	in->setPoint(Point(400,400));
	in->setPoint(Point(501, 701));

	App->AddStatement(st1);
	App->AddStatement(st2);
	

	a->ReadActionParameters();

	EXPECT_EQ(a->S, st1);
	EXPECT_EQ(a->D, st2);
}

TEST_F(ActionEdgeCoverage, AddConn_Execute_TEST1) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("there is not enough Statements to connect !"));
	a->Execute();
}

TEST_F(ActionEdgeCoverage, AddConn_Execute_TEST2) {
	Add_Conn *a = new Add_Conn(App);

	Start_End *st2 = new Start_End(Point(500, 700), 0);
	App->AddStatement(st2);
	Conditional *st = new Conditional(Point(500,500),"","",12,"",1);
	st->setConn(new Connector(new Conditional(), new Conditional(), false));
	App->AddStatement(st);

	in->setPoint(Point(500, 458));
	in->setPoint(Point(501, 701));


	a->Execute();

	EXPECT_EQ(a->S,st);
	EXPECT_EQ(a->D,st2);

}

TEST_F(ActionEdgeCoverage, AddConn_Execute_TEST3) {
	Add_Conn *a = new Add_Conn(App);

	EXPECT_CALL(*out, PrintMessage("there is no valid Connectors to be drawn !"));
	
	Start_End *st = new Start_End(Point(500, 700), 1);
	App->AddStatement(st);
	st = new Start_End(Point(400, 700), 1);
	App->AddStatement(st);
	st = new Start_End(Point(300, 700), 1);
	App->AddStatement(st);

	a->Execute();
}
