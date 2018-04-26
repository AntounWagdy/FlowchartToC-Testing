#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Comment.h"
#include"../PT-Project/Statements/SmplAssign.h"

TEST_F(ActionEdgeCoverage, Comment_ReadParams) {
	Comment* a = new Comment(App);
	SmplAssign *st = new SmplAssign(Point(500, 500));
	App->AddStatement(st);
	in->setPoint(Point(501, 501));
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("Hello World"));

	a->ReadActionParameters();
	EXPECT_EQ(a->C, "Hello World");
}

TEST_F(ActionEdgeCoverage, Comment_Execute_Test1) {
	Comment* a = new Comment(App);
	SmplAssign *st = new SmplAssign(Point(500, 500));
	App->AddStatement(st);
	in->setPoint(Point(501, 501));
	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("Hello World"));

	a->Execute();
	EXPECT_EQ(App->Statementlist()[0]->GetComment(), "Hello World");
}

TEST_F(ActionEdgeCoverage, Comment_Execute_Test2) {
	EXPECT_CALL(*out, PrintMessage("There is no Statements to Comment on !")).Times(1);
	Comment* a = new Comment(App);
	a->Execute();
}