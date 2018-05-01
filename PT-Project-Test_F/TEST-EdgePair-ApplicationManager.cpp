#include"../PT-Project/ApplicationManager.h"
#include"../PT-Project/Actions/Save.h"
#include"StatementInputOutputMock.h"
#include<gtest\gtest.h>
#include<gmock\gmock.h>


TEST(AppEdgePairCoverage, GetStatement) {
	ApplicationManager *app = new ApplicationManager();
	Statement *s = app->GetStatement(Point(300, 300));
	EXPECT_EQ(s, (Statement*)NULL);
	SmplAssign *st1 = new SmplAssign(Point(300,300),"X",12);
	SmplAssign *st2 = new SmplAssign(Point(400, 300), "X", 12);
	app->AddStatement(st1);
	app->AddStatement(st2);
	app->GetStatement(Point(200, 200));
	EXPECT_EQ(s, (Statement*)NULL);

}

TEST(AppEdgePairCoverage, updateeInterface) {
	ApplicationManager *app = new ApplicationManager();
	app->UpdateInterface();
}

TEST(AppEdgePairCoverage, Destructor_TEST_1) {
	ApplicationManager *app = new ApplicationManager();
	delete app;
}


TEST(AppEdgePairCoverage, Destructor_TEST_2) {
	ApplicationManager *app = new ApplicationManager();
	SmplAssign *st1 = new SmplAssign(Point(300, 300), "X", 12);
	SmplAssign *st2 = new SmplAssign(Point(300, 300), "X", 12);
	SmplAssign *st3 = new SmplAssign(Point(300, 300), "X", 12);
	SmplAssign *st4 = new SmplAssign(Point(300, 300), "X", 12);
	Connector *c1 = new Connector(st1,st2,false);
	Connector *c2 = new Connector(st2, st3, false);
	Connector *c3 = new Connector(st3, st4,false);

	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddStatement(st3);
	app->AddStatement(st4);
	app->AddConnector(c1);
	app->AddConnector(c2);
	app->AddConnector(c3);

	delete app;
}

TEST(AppEdgePairCoverage, getConnector) {
	ApplicationManager *app = new ApplicationManager();
	EXPECT_EQ(app->GetConnector(Point(300,300)),(Connector*)NULL);
	
	SmplAssign *st1 = new SmplAssign(Point(300, 300), "X", 12);
	SmplAssign *st2 = new SmplAssign(Point(300, 400), "X", 12);
	SmplAssign *st3 = new SmplAssign(Point(300, 500), "X", 12);
	SmplAssign *st4 = new SmplAssign(Point(300, 600), "X", 12);
	Connector *c1 = new Connector(st1, st2, false);
	Connector *c2 = new Connector(st2, st3, false);
	Connector *c3 = new Connector(st3, st4, false);

	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddStatement(st3);
	app->AddStatement(st4);
	app->AddConnector(c1);
	app->AddConnector(c2);
	app->AddConnector(c3);

	EXPECT_EQ(app->GetConnector(Point(350,350)),(Connector*)NULL);
}

TEST(AppEdgePairCoverage, deleteStatement) {
	ApplicationManager *app = new ApplicationManager();
	app->DeleteStatement(new SmplAssign());
	EXPECT_EQ(app->Statementcurrent(), 0);

	SmplAssign *st1 = new SmplAssign(Point(300, 300), "X", 12);
	SmplAssign *st2 = new SmplAssign(Point(300, 400), "X", 12);
	SmplAssign *st3 = new SmplAssign(Point(300, 500), "X", 12);
	SmplAssign *st4 = new SmplAssign(Point(300, 600), "X", 12);
	Connector *c1 = new Connector(st1, st2, false);
	Connector *c2 = new Connector(st2, st3, false);
	Connector *c3 = new Connector(st3, st4, false);

	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddStatement(st3);
	app->AddStatement(st4);
	app->AddConnector(c1);
	app->AddConnector(c2);
	app->AddConnector(c3);

	app->DeleteStatement(new SmplAssign());
	EXPECT_EQ(app->Statementcurrent(), 4);
}

