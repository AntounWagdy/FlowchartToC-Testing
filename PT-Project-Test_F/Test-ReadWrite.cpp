#include<gtest\gtest.h>
#include"../PT-Project/Statements/ReadWrite.h"
#include"OutputMock.h"


TEST(ReadWriteEdgeCoverage,FirstConstructor) {
	//State is true for read statement
	Point pos = Point(50, 50);
	ReadWrite* st = new ReadWrite(pos, "X", true);
	EXPECT_EQ(st->s,"X");
	EXPECT_EQ(st->state, true);
	EXPECT_EQ(st->LeftCorner, pos);
	EXPECT_EQ(st->pConn,(Connector*)NULL);
	EXPECT_EQ(st->Inlet, Point(pos.x+UI.r_width/2,pos.y));
	EXPECT_EQ(st->Outlet, Point(pos.x + UI.r_width / 2, pos.y+UI.r_height));
	EXPECT_EQ(st->R_load, false);
}

TEST(ReadWriteEdgeCoverage, SecondConstructor) {
	//State is true for read statement
	ReadWrite* st = new ReadWrite();
	EXPECT_NE(st, (ReadWrite*)NULL);
}

TEST(ReadWriteEdgeCoverage, UpdateStatementText) {
	ReadWrite* st = new ReadWrite();
	st->UpdateStatementText();
	EXPECT_EQ(st->Text, "     ");
	st = new ReadWrite(Point(), "X", true);
	EXPECT_EQ(st->Text, "X");
}


TEST(ReadWriteEdgeCoverage,SettersANDGetters) {
	ReadWrite* st = new ReadWrite(Point(50,50), "X", true);
	Connector * temp = new Connector(new ReadWrite(), new ReadWrite(),false);
	st->setConn(temp);
	int size;
	Connector **arr;
	st->getConn(arr, size);
	EXPECT_EQ(temp, arr[0]);
	EXPECT_EQ(size,1);

	Point pos(30,30);
	st->SetLeftCorner(pos.x,pos.y);
	EXPECT_EQ(st->getCorner(),pos);
	st->SetIn_Out();
	EXPECT_EQ(st->getIn(), Point(pos.x + UI.r_width / 2, pos.y));
	
	Point *parr;
	st->getOut(parr, size);
	EXPECT_EQ(size, 1);
	EXPECT_EQ(parr[0], Point(pos.x + UI.r_width / 2, pos.y + UI.r_height));

	st->SetR_Load(true);
	EXPECT_EQ(st->R_load, true);

	st->setString("Y");
	EXPECT_EQ(st->s, "Y");

	EXPECT_EQ(st->getKind(),true);

	EXPECT_EQ(st->width_height(), Point(UI.r_width, UI.r_height));
}

TEST(ReadWriteEdgeCoverage,Save){
	// Read Statement
	ReadWrite* st = new ReadWrite(Point(50, 50), "X", true);
	ofstream o("test.read.save");
	st->Save(o);
	o.close();

	ifstream file("test.read.save");
	string temp;
	int t;
	file >> temp;
	EXPECT_EQ(temp,"READ");
	file >> t;
	EXPECT_EQ(t, st->getID());
	file >> t;
	EXPECT_EQ(t, st->getCorner().x);
	file >> t;
	EXPECT_EQ(t, st->getCorner().y);
	file >> temp;
	EXPECT_EQ(st->getVar(), temp);
	file >> temp;
	EXPECT_EQ(st->GetComment(), "\"\"");
	file.close();


	// Write Statement
	st = new ReadWrite(Point(50, 50), "X", false);
	o.open("test.write.save");
	st->Save(o);
	o.close();

	file.open("test.write.save");
	

	file >> temp;
	EXPECT_EQ(temp, "WRITE");
	file >> t;
	EXPECT_EQ(t, st->getID());
	file >> t;
	EXPECT_EQ(t, st->getCorner().x);
	file >> t;
	EXPECT_EQ(t, st->getCorner().y);
	file >> temp;
	EXPECT_EQ(st->getVar(), temp);
	file >> temp;
	EXPECT_EQ(st->GetComment(), "\"\"");
	file.close();
}

TEST(ReadWriteEdgeCoverage, Load) {
	Point pos(50, 100);
	ReadWrite* st = new ReadWrite(pos, "X", true);
	ofstream o("test.read.load");
	st->Save(o);
	o.close();
	ifstream i("test.read.load");
	st->SetR_Load(true);
	string temp; 
	i >> temp;
	st->Load(i);
	i.close();
	EXPECT_EQ(st->s, "X");
	EXPECT_EQ(st->state, true);
	EXPECT_EQ(st->LeftCorner, pos);
	EXPECT_EQ(st->pConn, (Connector*)NULL);
	EXPECT_EQ(st->Inlet, Point(pos.x + UI.r_width / 2, pos.y));
	EXPECT_EQ(st->Outlet, Point(pos.x + UI.r_width / 2, pos.y + UI.r_height));
	EXPECT_EQ(st->R_load, true);


	// Write Statement
	st = new ReadWrite(pos, "X", false);
	o.open("test.write.load");
	st->Save(o);
	o.close();
	i.open("test.write.load");
	st->SetR_Load(false);
	
	i >> temp;
	st->Load(i);
	i.close();
	EXPECT_EQ(st->s, "X");
	EXPECT_EQ(st->state, false);
	EXPECT_EQ(st->LeftCorner, pos);
	EXPECT_EQ(st->pConn, (Connector*)NULL);
	EXPECT_EQ(st->Inlet, Point(pos.x + UI.r_width / 2, pos.y));
	EXPECT_EQ(st->Outlet, Point(pos.x + UI.r_width / 2, pos.y + UI.r_height));
	EXPECT_EQ(st->R_load, false);
}

TEST(ReadWriteEdgeCoverage, Run) {
	ReadWrite *st = new ReadWrite();
	map<string, double>m;
	EXPECT_EQ(st->Run(m), 3);
	st->setString("X");
	EXPECT_EQ(st->Run(m), 1);
}


TEST(ReadWriteEdgeCoverage, Draw_TEST_1) {
	ReadWrite *st = new ReadWrite(Point(50,50),"x",true);
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out,DrawRead(_,_,_,_,_));
	st->Draw(out);
}


TEST(ReadWriteEdgeCoverage, Draw_TEST_2) {
	ReadWrite *st = new ReadWrite(Point(50, 50), "x", false);
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out, DrawWrite(_, _, _, _, _));
	st->Draw(out);
}



TEST(ReadWriteEdgeCoverage, PrintInfo_TEST_1) {
	ReadWrite *st = new ReadWrite(Point(50, 50), "x", true);
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out, PrintMessage("ID = "+to_string(st->getID())+", Comment: "+" Read statement\n"));
	st->PrintInfo(out);
}

TEST(ReadWriteEdgeCoverage, PrintInfo_TEST_2) {
	ReadWrite *st = new ReadWrite(Point(50, 50), "x", false);
	mockOutput2 * out = new mockOutput2();
	EXPECT_CALL(*out, PrintMessage("ID = " + to_string(st->getID()) + ", Comment: " + " Write statement\n"));
	st->PrintInfo(out);
}