#include"../PT-Project/Statements/Variable.h"
#include<gtest\gtest.h>
#include"OutputMock.h"

TEST(VariableEdgeCoverage,FirstConstructor) {
	Point pos = Point(50, 60);
	Variable *st = new Variable(pos, "X", "Y");
	EXPECT_EQ(st->LHS , "X");
	EXPECT_EQ(st->RHS , "Y");
	EXPECT_EQ(st->LeftCorner,pos);
	EXPECT_EQ(st->pConn, (Connector*)NULL);

	EXPECT_EQ(st->Inlet, Point(pos.x+UI.ASSGN_WDTH/2,pos.y));
	EXPECT_EQ(st->Outlet, Point(pos.x + UI.ASSGN_WDTH / 2, pos.y+UI.ASSGN_HI));
}


TEST(VariableEdgeCoverage, SecondConstructor) {
	Variable *st = new Variable();
	EXPECT_NE(st,(Statement*)NULL);
}

TEST(VariableEdgeCoverage, UpdateStatementText) {
	Variable *st = new Variable();
	st->UpdateStatementText();
	EXPECT_EQ(st->Text, "    = ");
	st->setLHS("X");
	st->setRHS("Y");
	EXPECT_EQ(st->Text, "X = Y");
}
TEST(VariableEdgeCoverage, settersAndGetters) {
	Variable *st = new Variable(Point(50,60),"","");
	Connector *x = new Connector(new Variable(), new Variable(),false);
	st->setConn(x);
	Connector ** arr;
	int size;
	st->getConn(arr, size);
	EXPECT_EQ(arr[0],x);
	EXPECT_EQ(size, 1);

	st->setLHS("T");
	EXPECT_EQ(st->LHS, "T");
	st->setRHS("Y");
	EXPECT_EQ(st->RHS, "Y");

	EXPECT_EQ(st->getCorner(), Point(50, 60));

	EXPECT_EQ(st->getIn() , Point(50 + UI.ASSGN_WDTH / 2, 60));
	Point *parr;
	st->getOut(parr,size);
	EXPECT_EQ(size, 1);
	EXPECT_EQ(parr[0] , Point(50 + UI.ASSGN_WDTH / 2, 60 + UI.ASSGN_HI));	
	EXPECT_EQ(st->width_height(),Point(UI.ASSGN_WDTH, UI.ASSGN_HI));

}



TEST(VariableEdgeCoverage, Save) {
	Point pos = Point(50, 60);
	Variable *st = new Variable(pos, "X", "Y");

	ofstream f("variable.test.save");
	st->Save(f);
	f.close();
	ifstream file("variable.test.save");
	string t;
	int te;
	file >> t;
	EXPECT_EQ(t, "VARIABLE");
	file >> te;
	EXPECT_EQ(te, st->getID());
	file >> te;
	EXPECT_EQ(te, st->getCorner().x);
	file >> te;
	EXPECT_EQ(te, st->getCorner().y);
	
	file >> t;
	EXPECT_EQ(t, st->LHS);
	file >> t;
	EXPECT_EQ(t, st->RHS);
	file >> t;
	EXPECT_EQ(t, "\"\"");
	file.close();
}

TEST(VariableEdgeCoverage, load) {
	Point pos = Point(50, 50);
	Variable *st = new Variable(pos,"X","Y"); // 0 for end
	ofstream f("variable.test.load");
	st->Save(f);
	f.close();

	st = new Variable();
	ifstream file("variable.test.load");
	string temp;
	file >> temp;

	st->Load(file);

	EXPECT_EQ(st->LHS, "X");
	EXPECT_EQ(st->RHS, "Y");
	EXPECT_EQ(st->LeftCorner, pos);
	EXPECT_EQ(st->pConn, (Connector*)NULL);

	EXPECT_EQ(st->Inlet, Point(pos.x + UI.ASSGN_WDTH / 2, pos.y));
	EXPECT_EQ(st->Outlet, Point(pos.x + UI.ASSGN_WDTH / 2, pos.y + UI.ASSGN_HI));
	file.close();
}

TEST(VariableEdgeCoverage, Run) {
	Variable *st = new Variable();
	map<string, double>m;
	EXPECT_EQ(st->Run(m),3);
	st->setLHS("X");
	st->setRHS("Y");
	EXPECT_EQ(st->Run(m), 0);
	m["Y"] = 2;
	EXPECT_EQ(st->Run(m), 1);
}

TEST(VariableEdgeCoverage, Draw) {
	Variable *st = new Variable();
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out, DrawAssign(_,_,_,_,_));
	st->Draw(out);
}

TEST(VariableEdgeCoverage, PrintInfo) {
	Variable *st = new Variable();
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out, PrintMessage("ID = " + to_string(st->getID()) + ", Comment: " + ""));
	st->PrintInfo(out);
}
