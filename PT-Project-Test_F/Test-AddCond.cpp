#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/AddCond.h"

TEST_F(ActionEdgeCoverage,AddCond_ReadActionParams_TEST1) {
	AddCond *a = new AddCond(App);
	
	EXPECT_CALL(*out, PrintMessage("Conditional Assignment Statement: Click a valid Point to Draw the statement")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter The Left hand Side")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter the Right hand side: ")).Times(1);
	EXPECT_CALL(*out, PrintMessage("Enter the Right hand side Type (1- double,2-string)")).Times(1);
	EXPECT_CALL(*out, PrintMessage("Enter a Valid Operator")).Times(2);

	in->setPoint(Point());
	in->setPoint(Point(500,500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("1X"))
		.WillOnce(Return("_X")).WillOnce(Return("1Y"))
		.WillOnce(Return("_Y")).WillOnce(Return("<<"))
		.WillOnce(Return("<="));

	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(2));

	a->ReadActionParameters();
}




TEST_F(ActionEdgeCoverage, AddCond_ReadActionParams_TEST2) {
	AddCond *a = new AddCond(App);

	EXPECT_CALL(*out, PrintMessage("Conditional Assignment Statement: Click a valid Point to Draw the statement")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter The Left hand Side")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Enter the Right hand side: ")).Times(1);
	EXPECT_CALL(*out, PrintMessage("Enter the Right hand side Type (1- double,2-string)")).Times(1);
	EXPECT_CALL(*out, PrintMessage("Enter a Valid Operator")).Times(2);

	in->setPoint(Point());
	in->setPoint(Point(500, 500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("1X"))
		.WillOnce(Return("_X")).WillOnce(Return("<<"))
		.WillOnce(Return("<="));

	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(1))
		.WillOnce(Return(12));

	a->ReadActionParameters();
}


TEST_F(ActionEdgeCoverage, AddCond_Execute) {
	AddCond *a = new AddCond(App);
	in->setPoint(Point(500, 500));
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("X")).WillOnce(Return("<="));

	EXPECT_CALL(*in, GetValue(_)).WillOnce(Return(1))
		.WillOnce(Return(12));

	a->Execute();
	EXPECT_EQ(App->Statementcurrent(), 1);
	EXPECT_NE(App->Statementlist()[0], (Statement*)NULL);
}