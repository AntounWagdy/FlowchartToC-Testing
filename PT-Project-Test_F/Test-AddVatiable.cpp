#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/AddVariable.h"
using namespace std;


TEST_F(ActionEdgeCoverage,AddVariable_ReadParams) {
	AddVariable *a = new AddVariable(App);

	EXPECT_CALL(*out, PrintMessage("Variable Statement: Click to add the statement")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Please enter a Valid left hand side")).Times(2);
	EXPECT_CALL(*out, PrintMessage("Please enter a Valid right hand side")).Times(2);

	in->setPoint(Point());
	in->setPoint(Point(500, 500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("1X"))
		.WillOnce(Return("_X")).WillOnce(Return("1Y"))
		.WillOnce(Return("_Y"));
	a->ReadActionParameters();
}


TEST_F(ActionEdgeCoverage, AddVariable_Execute) {
	AddVariable *a = new AddVariable(App);

	in->setPoint(Point(500, 500));

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("_X"))
		.WillOnce(Return("_Y"));
	a->Execute();
	EXPECT_EQ(App->Statementcurrent(),1);
	EXPECT_TRUE(dynamic_cast<Variable*>( App->Statementlist()[0]));
}