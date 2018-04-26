#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Run.h"
#include"../PT-Project/Statements/Statement.h"

TEST_F(ActionGACC, RunExecute) {
	// This also satisfies GICC
	Run_Action *a = new Run_Action(App);
	Start_End *st = new Start_End(Point(50,50),0);
	ReadWrite *st2 = new ReadWrite(Point(50, 50),"x",true);
	ReadWrite *st3 = new ReadWrite(Point(50, 50), "x", false);
	Start_End *st4 = new Start_End(Point(50, 50), 1);

	App->AddStatement(st);
	App->AddStatement(st2);
	App->AddStatement(st3);
	App->AddStatement(st4);

	Connector *c1 = new Connector(st4,st2,false);
	Connector *c2 = new Connector(st2, st3, false);
	Connector *c3 = new Connector(st3, st, false);

	App->AddConnector(c1);
	App->AddConnector(c2);
	App->AddConnector(c3);

	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(500));
	EXPECT_CALL(*out, PrintMessage("Enter the value of x :"));
	EXPECT_CALL(*out, PrintMessage("500                        //Output"));
	EXPECT_CALL(*out, PrintMessage("Program has exited with code of 0*0"));
	a->Execute();
}