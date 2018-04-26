#include"../PT-Project/Statements/SmplAssign.h"
#include<gtest\gtest.h>

TEST(smplAssignEdgeCoverage, firstConstructor) {
	SmplAssign *st = new SmplAssign(Point(50, 50), "X", 5);
	EXPECT_EQ(st->LHS, "X");
	EXPECT_EQ(st->RHS, 5);
	EXPECT_EQ(st->LeftCorner , Point(50,50));
	EXPECT_EQ(st->pConn, (Connector*)NULL);
	EXPECT_EQ(st->Inlet, Point(50+ UI.ASSGN_WDTH / 2,50));
	EXPECT_EQ(st->Outlet, Point(50 + UI.ASSGN_WDTH / 2, 50+UI.ASSGN_HI));
}

TEST(smplAssignEdgeCoverage, secondConstructor) {
	SmplAssign *st = new SmplAssign();
	EXPECT_NE(st,(SmplAssign*)NULL);

}

TEST(smplAssignEdgeCoverage, UpdateStatementText) {
	SmplAssign *st = new SmplAssign();
	EXPECT_EQ(st->Text, "");
	st->setLHS("X");
	st->setRHS(2);
	st->UpdateStatementText();
	EXPECT_EQ(st->Text, "X = 2");
}

TEST(smplAssignEdgeCoverage, SettersAndGetters) {
	SmplAssign *st = new SmplAssign(Point(50, 50), "X", 5);
	Connector *x = new Connector(new SmplAssign(), new SmplAssign(),true);
	st->setConn(x);
	Connector ** arr;
	int size;
	st->getConn(arr,size);
	EXPECT_EQ(size, 1);
	EXPECT_EQ(arr[0], x);

	st->setLHS("Y");
	EXPECT_EQ(st->LHS,"Y");
	st->setRHS(12);
	EXPECT_EQ(st->RHS, 12);
	
	EXPECT_EQ(st->getCorner(),Point(50,50));
	EXPECT_EQ(st->getIn(), Point(50 + UI.ASSGN_WDTH / 2, 50));
	Point * parr;
	st->getOut(parr, size);
	EXPECT_EQ(size, 1);
	EXPECT_EQ(parr[0], Point(50 + UI.ASSGN_WDTH / 2, 50 + UI.ASSGN_HI));
	
	EXPECT_EQ(st->width_height(), Point(UI.ASSGN_WDTH, UI.ASSGN_HI));
}

TEST(smplAssignEdgeCoverage,Save) {
	SmplAssign *st = new SmplAssign(Point(50, 50), "X", 5);
	ofstream o("smplAssign.test.save");
	st->Save(o);
	o.close();

	ifstream file("smplAssign.test.save");
	//	OutFile << "SmplAssign" << "   " << ID << "   " << LeftCorner.x << "   " << LeftCorner.y << "   " << this->LHS << "   " << this->RHS << "   " << GetComment() << endl;
	string s;
	int t;
	file >> s;
	EXPECT_EQ(s, "SmplAssign");
	file >> t;
	EXPECT_EQ(t, st->getID());
	file >> t;
	EXPECT_EQ(t, st->getCorner().x);
	file >> t;
	EXPECT_EQ(t, st->getCorner().y);
	file >> s;
	EXPECT_EQ(s, "X");
	file >> t;
	EXPECT_EQ(t, 5);
	file >> s;
	EXPECT_EQ(s, "\"\"");
}

TEST(smplAssignEdgeCoverage, Load) {
	SmplAssign *t = new SmplAssign(Point(50, 50), "X", 5);
	ofstream f("smplAssign.test.load");
	t->Save(f);
	ifstream file("smplAssign.test.load");
	string temp;
	file >> temp;
	SmplAssign *st = new SmplAssign();
	st->Load(file);
	EXPECT_EQ(st->LHS, "X");
	EXPECT_EQ(st->RHS, 5);
	EXPECT_EQ(st->LeftCorner, Point(50, 50));
	EXPECT_EQ(st->pConn, (Connector*)NULL);
	EXPECT_EQ(st->Inlet, Point(50 + UI.ASSGN_WDTH / 2, 50));
	EXPECT_EQ(st->Outlet, Point(50 + UI.ASSGN_WDTH / 2, 50 + UI.ASSGN_HI));
}

TEST(smplAssignEdgeCoverage, Run) {
	SmplAssign *st = new SmplAssign(Point(50, 50), "", 5);
	map<string, double>m;
	EXPECT_EQ(st->Run(m), 3);
	st->setLHS("X");
	EXPECT_EQ(st->Run(m), 1);
}