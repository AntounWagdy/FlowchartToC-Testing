#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Add_Start_End.h"
using namespace std;


TEST_F(ActionEdgeCoverage,AddStartEnd_ReadParams) {
	Action *a = new Add_Start_End(App,1); // 1 for start

	EXPECT_CALL(*out, PrintMessage("Click a valid point to draw the statement")).Times(2);
	in->setPoint(Point());
	in->setPoint(Point(500,500));
	a->ReadActionParameters();
}


TEST_F(ActionEdgeCoverage, AddStartEnd_Execute) {
	Action *a = new Add_Start_End(App, 1); // 1 for start

	in->setPoint(Point(500, 500));
	a->Execute();

	EXPECT_EQ(App->Statementcurrent(), 1);
	EXPECT_TRUE(App->Statementlist()[0]!=NULL);
}


