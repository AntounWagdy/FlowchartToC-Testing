#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Load.h"
#include"../PT-Project/Statements/SmplAssign.h"
TEST_F(ActionEdgeCoverage,Load_Execute) {
	Load * a = new Load(App);
	SmplAssign* st1 = new SmplAssign(Point(500, 500));
	SmplAssign* st2 = new SmplAssign(Point(500, 600));
	Connector * c = new Connector(st1, st2,false);

	App->AddConnector(c);
	App->AddStatement(st1);
	App->AddStatement(st2);

	a->Execute();

	bool d = false;
	bool b = false;

	for (int i = 0; i < App->Statementcurrent(); i++) {
		d |= ((dynamic_cast<Start_End*>(App->Statementlist()[i])) && (((Start_End*)App->Statementlist()[i])->getKind()==0));
		b |= ((dynamic_cast<Start_End*>(App->Statementlist()[i])) && (((Start_End*)App->Statementlist()[i])->getKind() == 1));
	}
	EXPECT_TRUE(b&&d);
}