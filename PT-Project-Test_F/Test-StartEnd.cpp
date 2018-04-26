#include<gtest\gtest.h>
#include"../PT-Project/Statements/Start_End.h"


TEST(StartEndEdgeCoverage, FirstConstructor) {
	Start_End *st = new Start_End(Point(50,50),0); // 0 for end
	EXPECT_EQ(st->getCorner(),Point(50,50));
	EXPECT_EQ(st->St_En, 0);
	EXPECT_EQ(st->C, (Connector*)NULL);
	EXPECT_EQ(st->D_load, false);

	EXPECT_EQ(st->In, Point(50 + UI.EllipseWidth/2 , 50));
	EXPECT_EQ(st->Out, Point(50 + UI.EllipseWidth / 2 , 50 + UI.EllipseH));
}

TEST(StartEndEdgeCoverage, SecondConstructor) {
	Start_End *st = new Start_End();
	EXPECT_NE(st,(Start_End*)NULL);
}



TEST(StartEndEdgeCoverage, SettersAndGetters) {
	Start_End *st = new Start_End(Point(50, 50), 0); // 0 for end
	Connector *x = new Connector(new Start_End(), new Start_End(),false);
	st->setConn(x);
	int size;
	Connector **arr;
	st->getConn(arr, size);
	EXPECT_EQ(size, 1);
	EXPECT_EQ(x, arr[0]);

	st->SetLoad(true);
	EXPECT_EQ(st->D_load,true);

	EXPECT_EQ(st->getCorner(), Point(50, 50));

	EXPECT_EQ(st->getIn(), Point(50 + UI.EllipseWidth/2, 50));
	
	Point * parr;
	st->getOut(parr, size);

	EXPECT_EQ(size, 1);
	EXPECT_EQ(parr[0], Point(50+UI.EllipseWidth/2, 50 + UI.EllipseH));
	EXPECT_EQ(st->getKind(), 0);
}


TEST(StartEndEdgeCoverage,Save) {
	// Start
	Start_End *st = new Start_End(Point(50, 50), 1); // 0 for end
	ofstream f("start.test.save");
	st->Save(f);
	f.close();
	ifstream file("start.test.save");
	string t;
	int te;
	file >> t;
	EXPECT_EQ(t,"STRT" );
	file >> te;
	EXPECT_EQ(te,st->getID() );
	file >> te;
	EXPECT_EQ(te,st->getCorner().x+ UI.EllipseWidth / 2);
	file >> te;
	EXPECT_EQ(te, st->getCorner().y + UI.EllipseH / 2);
	file >> t;
	EXPECT_EQ(t, "\"\"");
	file.close();

	// END
	st = new Start_End(Point(50, 50), 0); // 0 for end
	f.open("End.test.save");
	st->Save(f);
	f.close();
	file.open("End.test.save");
	file >> t;
	EXPECT_EQ(t, "END");
	file >> te;
	EXPECT_EQ(te, st->getID());
	file >> te;
	EXPECT_EQ(te, st->getCorner().x + UI.EllipseWidth / 2);
	file >> te;
	EXPECT_EQ(te, st->getCorner().y + UI.EllipseH / 2);
	file >> t;
	EXPECT_EQ(t, "\"\"");
	file.close();
}



TEST(StartEndEdgeCoverage, load) {
	// START
	Start_End *st = new Start_End(Point(50, 50), 1); // 0 for end
	ofstream f("start.test.load");
	st->Save(f);
	f.close();

	st = new Start_End(); 
	ifstream file("start.test.load");
	string temp;
	file >> temp;
	st->SetLoad(true);
	st->Load(file);

	EXPECT_EQ(st->getCorner(), Point(50, 50));
	EXPECT_EQ(st->St_En, 1);
	EXPECT_EQ(st->C, (Connector*)NULL);
	EXPECT_EQ(st->D_load, true);

	EXPECT_EQ(st->In, Point(50 + UI.EllipseWidth/2, 50));
	EXPECT_EQ(st->Out, Point(50 + UI.EllipseWidth / 2, 50 + UI.EllipseH));
	file.close();


	// END
	st = new Start_End(Point(50, 50), 0); // 0 for end
	f.open("End.test.load");
	st->Save(f);
	f.close();

	st = new Start_End();
	file.open("End.test.load");
	file >> temp;
	st->SetLoad(false);
	st->Load(file);
	EXPECT_EQ(st->getCorner(), Point(50, 50));
	EXPECT_EQ(st->St_En, 0);
	EXPECT_EQ(st->C, (Connector*)NULL);
	EXPECT_EQ(st->D_load,false);

	EXPECT_EQ(st->In, Point(50 + UI.EllipseWidth/2, 50));
	EXPECT_EQ(st->Out, Point(50 + UI.EllipseWidth / 2, 50 + UI.EllipseH));
	file.close();
}


TEST(StartEndEdgeCoverage, Run) {
	Start_End *st = new Start_End();
	map<string, double> m;
	EXPECT_EQ(st->Run(m), 1);
}