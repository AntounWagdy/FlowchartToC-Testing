#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Save.h"
#include"../PT-Project/Statements/Start_End.h"

bool compare(ifstream &in, ifstream &in2) {
	while ((!in.eof()) && (!in2.eof())) { 
		string line, line2;
		getline(in, line); 
		getline(in2, line2);
		if (line != line2) {
			return false;
		}
	}

	in.close();
	in2.close();  
	return true;
}

TEST_F(ActionEdgeCoverage, Save_Execute) {
	Save * a = new Save(App);


	Start_End* st1 = new Start_End(Point(500, 500),0);
	Start_End* st2 = new Start_End(Point(500, 600), 1);

	st1->SetID(36);
	st2->SetID(37);
	Connector *c = new Connector(st1, st2, false);
	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddConnector(c);
	
	a->Execute();
	ifstream f1("Flow_Chart.txt");
	ifstream f2("Flow_Chart - Gold.txt");

	EXPECT_TRUE(compare(f1,f2));
}