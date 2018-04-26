#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/AddSmplAssign.h"

TEST_F(ActionEdgeCoverage,AddSmplAssgn_ReadParams) {
	AddSmplAssign *a = new AddSmplAssign(App);

	EXPECT_CALL(*out, PrintMessage("Simple Value Assignment Statement: Click to add the statement")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter a Valid Left hand side")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter the right hand side")).Times(1);


	in->setPoint(Point());
	in->setPoint(Point(500, 500));
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("1X"))
		.WillOnce(Return("_X"));

	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(12));

	a->ReadActionParameters();
}

TEST_F(ActionEdgeCoverage, AddSmplAssgn_Execute) {
	AddSmplAssign *a = new AddSmplAssign(App);

	in->setPoint(Point(500, 500));
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("_X"));
	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(12));

	a->Execute();
	EXPECT_EQ(App->Statementcurrent(),1);
	EXPECT_NE(App->Statementlist()[0], (Statement*)NULL);
}