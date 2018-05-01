#include"../PT-Project/ApplicationManager.h"
#include"../PT-Project/Actions/Save.h"
#include"StatementInputOutputMock.h"
#include<gtest\gtest.h>
#include<gmock\gmock.h>


TEST(AppGACCCoverage, GetStatement_TEST_1) {
	ApplicationManager *app = new ApplicationManager();
	Conditional *st = new Conditional(Point(300, 300), "X", "==", 12, "Y", 2);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(200,200));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, GetStatement_TEST_2) {
	ApplicationManager *app = new ApplicationManager();
	Conditional *st = new Conditional(Point(300, 300), "X", "==", 12, "Y", 2);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(400, 400));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, GetStatement_TEST_3) {
	ApplicationManager *app = new ApplicationManager();
	Conditional *st = new Conditional(Point(300, 300), "X", "==", 12, "Y", 2);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(320, 400));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, GetStatement_TEST_4) {
	ApplicationManager *app = new ApplicationManager();
	SmplAssign *st = new SmplAssign(Point(300, 300),"X",12);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(200,200));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, GetStatement_TEST_5) {
	ApplicationManager *app = new ApplicationManager();
	SmplAssign *st = new SmplAssign(Point(300, 300), "X", 12);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(400, 400));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, GetStatement_TEST_6) {
	ApplicationManager *app = new ApplicationManager();
	SmplAssign *st = new SmplAssign(Point(300, 300), "X", 12);
	app->AddStatement(st);
	Statement *s = app->GetStatement(Point(350, 400));
	EXPECT_EQ(s, (Statement*)NULL);
}


TEST(AppGACCCoverage, isPointBetween) {
	ApplicationManager *app = new ApplicationManager();
	bool res = app->IsPointBetween(Point(50,50),Point(100,100),Point(300,300));
	EXPECT_FALSE(res);

	res = app->IsPointBetween(Point(400, 400), Point(100, 100), Point(300, 300));
	EXPECT_FALSE(res);

	res = app->IsPointBetween(Point(150, 400), Point(100, 100), Point(300, 300));
	EXPECT_FALSE(res);
}



TEST(AppGACCCoverage, GetConnector_TEST_1) {
	ApplicationManager *app = new ApplicationManager();
	Statement *st1 = new SmplAssign(Point(200,300),"X",1);
	Statement *st2 = new SmplAssign(Point(200, 200), "X", 1);
	Connector *x = new Connector(st1, st2, false);
	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddConnector(x);
	Point *parr;
	int size;
	st1->getOut(parr,size);
	Connector * res= app->GetConnector(parr[0]);
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(parr[0].x+50,parr[0].y+10));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x, st2->getIn().y-8));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x-3, st2->getIn().y-3));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x + 3, st2->getIn().y - 3));
	EXPECT_TRUE(res == x);
}



TEST(AppGACCCoverage, GetConnector_TEST_2) {
	ApplicationManager *app = new ApplicationManager();
	Statement *st1 = new SmplAssign(Point(200, 200), "X", 1);
	Statement *st2 = new SmplAssign(Point(200, 300), "X", 1);
	Connector *x = new Connector(st1, st2, false);
	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddConnector(x);
	Point *parr;
	int size;
	st1->getOut(parr, size);
	Connector * res = app->GetConnector(parr[0]);
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(parr[0].x , parr[0].y + 10));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x, st2->getIn().y - 3));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(st2->getIn());
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x - 3, st2->getIn().y - 3));
	EXPECT_TRUE(res == x);
}



TEST(AppGACCCoverage, GetConnector_TEST_3) {
	ApplicationManager *app = new ApplicationManager();
	Statement *st1 = new SmplAssign(Point(200, 200), "X", 1);
	Statement *st2 = new SmplAssign(Point(500, 200), "X", 1);
	Connector *x = new Connector(st1, st2, false);
	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddConnector(x);
	Point *parr;
	int size;
	st1->getOut(parr, size);
	Connector * res = app->GetConnector(parr[0]);
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x, st2->getIn().y - 7));
	EXPECT_TRUE(res == x);

	res = app->GetConnector(st2->getIn());
	EXPECT_TRUE(res == x);

	res = app->GetConnector(Point(st2->getIn().x - 3, st2->getIn().y - 3));
	EXPECT_TRUE(res == x);
}