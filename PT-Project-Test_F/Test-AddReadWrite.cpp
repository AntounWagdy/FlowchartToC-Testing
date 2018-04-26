#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/AddReadWrite.h"

TEST_F(ActionEdgeCoverage, AddReadWrite_ReadParams) {
	AddReadWrite *a = new AddReadWrite(App,true); // Read
	EXPECT_CALL(*out, PrintMessage("Variable Statement: Click to add the statement")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Please enter a Valid statenemt")).Times(2);

	in->setPoint(Point());
	in->setPoint(Point(500, 500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("1X"))
		.WillOnce(Return("_X"));

	a->ReadActionParameters();
}

TEST_F(ActionEdgeCoverage, AddReadWrite_ReadParams_Test1) {
	AddReadWrite *a = new AddReadWrite(App, true); // Read
	in->setPoint(Point(500,500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("_X"));

	a->Execute();
	EXPECT_EQ(App->Statementcurrent(), 1);
	EXPECT_EQ(((ReadWrite*)App->Statementlist()[0])->getKind(),true);
}

TEST_F(ActionEdgeCoverage, AddReadWrite_ReadParams_Test2) {
	AddReadWrite *a = new AddReadWrite(App, false); // Read
	in->setPoint(Point(500,500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("_X"));

	a->Execute();
	EXPECT_EQ(App->Statementcurrent(), 1);
	EXPECT_EQ(((ReadWrite*)App->Statementlist()[0])->getKind(), false);
}