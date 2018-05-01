#include"../PT-Project/ApplicationManager.h"
#include"../PT-Project/Actions/Save.h"
#include"StatementInputOutputMock.h"
#include<gtest\gtest.h>
#include<gmock\gmock.h>

TEST(AppEdgeCoverage, Constructor) {
	ApplicationManager *app = new ApplicationManager();
	EXPECT_EQ(app->Statementcurrent(), 0);
	EXPECT_EQ(app->Connectorcurrent(), 0);
	EXPECT_EQ(app->pSelectedStat, (Statement*)NULL);
	EXPECT_EQ(app->pSelectedConn, (Connector*)NULL);
	for (int i = 0; i < 200; i++) {
		EXPECT_EQ(app->Statementlist()[i], (Statement*)NULL);
		EXPECT_EQ(app->Connectorlist()[i], (Connector*)NULL);
	}
}

TEST(AppEdgeCoverage, AddStatement) {
	ApplicationManager *app = new ApplicationManager();
	SmplAssign *x = new SmplAssign();
	app->AddStatement(x);
	
	EXPECT_EQ(app->Statementcurrent(), 1);
	EXPECT_EQ(app->Statementlist()[0],x);
	
	for (int i = 0; i < 212; i++) {
		SmplAssign *x = new SmplAssign();
		app->AddStatement(x);
	}
	EXPECT_EQ(app->Statementcurrent(), 200);
}


TEST(AppEdgeCoverage, Addconnector) {
	ApplicationManager *app = new ApplicationManager();
	Connector*x = new Connector(new SmplAssign(),new SmplAssign(),false);
	app->AddConnector(x);

	EXPECT_EQ(app->Connectorcurrent(), 1);
	EXPECT_EQ(app->Connectorlist()[0], x);

	for (int i = 0; i < 212; i++) {
		Connector*x = new Connector(new SmplAssign(), new SmplAssign(), false);
		app->AddConnector(x);
	}
	EXPECT_EQ(app->Connectorcurrent(), 200);
}



TEST(AppEdgeCoverage, IsPointBetween) {
	ApplicationManager *app = new ApplicationManager();
	bool x = app->IsPointBetween(Point(50,50),Point(),Point(100,100));
	EXPECT_TRUE(x);

	x = app->IsPointBetween(Point(), Point(50,50), Point(100, 100));
	EXPECT_TRUE(!x);
}



TEST(AppEdgeCoverage, deleteConnector_TEST_1) {
	ApplicationManager *app = new ApplicationManager();
	Statement *s1 = new SmplAssign();
	Statement *s2 = new SmplAssign();
	Connector *x = new Connector(s1,s2,false);
	Connector *y = new Connector(s2, s1, false);

	app->AddConnector(y);
	app->AddConnector(x);

	Connector **temp;
	int size;
	s1->getConn(temp,size);
	EXPECT_EQ(temp[0],x);
	app->DeleteConnector(x);
	
	s1->getConn(temp, size);
	EXPECT_EQ(temp[0], (Connector*)NULL);
	EXPECT_EQ(app->Connectorcurrent(),1);
	EXPECT_EQ(app->Connectorlist()[0], y);
}



TEST(AppEdgeCoverage, deleteConnector_TEST_2) {
	ApplicationManager *app = new ApplicationManager();
	Statement *s1 = new Conditional(Point(50,50),"","",12,"",1);
	Statement *s2 = new SmplAssign();
	Connector *x = new Connector(s1, s2, false);
	Connector *y = new Connector(s2, s1, false);

	app->AddConnector(y);
	app->AddConnector(x);

	Connector **temp;
	int size;
	s1->getConn(temp, size);
	EXPECT_EQ(temp[0], x);

	app->DeleteConnector(x);

	s1->getConn(temp, size);
	EXPECT_EQ(temp[0], (Connector*)NULL);
	EXPECT_EQ(app->Connectorcurrent(), 1);
	EXPECT_EQ(app->Connectorlist()[0], y);
}


TEST(AppEdgeCoverage, deleteConnector_TEST_3) {
	ApplicationManager *app = new ApplicationManager();
	Statement *s1 = new Conditional(Point(50, 50), "", "", 12, "", 1);
	Statement *s2 = new SmplAssign();

	Connector *z = new Connector(s1, s2, false);
	Connector *x = new Connector(s1, s2, false);
	Connector *y = new Connector(s2, s1, false);

	app->AddConnector(x);
	app->AddConnector(z);
	app->AddConnector(y);

	Connector **temp;
	int size;
	s1->getConn(temp, size);
	EXPECT_EQ(temp[1], x);
	app->DeleteConnector(x);

	s1->getConn(temp, size);
	EXPECT_EQ(temp[1], (Connector*)NULL);
	EXPECT_EQ(app->Connectorcurrent(), 2);
	EXPECT_EQ(app->Connectorlist()[1], z);
	EXPECT_EQ(app->Connectorlist()[0], y);
}

TEST(AppEdgeCoverage, deleteStatement) {
	ApplicationManager * app = new ApplicationManager();
	Statement * st1 = new SmplAssign();
	Statement * st2 = new SmplAssign();
	Statement * st3 = new SmplAssign();
	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddStatement(st3);

	app->DeleteStatement(st2);
	EXPECT_EQ(app->Statementcurrent(),2);
	EXPECT_EQ(app->Statementlist()[0], st1);
	EXPECT_EQ(app->Statementlist()[1], st3);
}

TEST(AppEdgeCoverage, GetStatement) {
	ApplicationManager * app = new ApplicationManager();
	Conditional *x = new Conditional(Point(500, 500), "", "", 12, "", 1);
	Conditional *y = new Conditional(Point(450, 450), "", "", 12, "", 1);
	SmplAssign *w = new SmplAssign(Point(300, 300), "", 1);
	SmplAssign *z = new SmplAssign(Point(200, 200), "", 1);


	app->AddStatement(x);
	app->AddStatement(y);
	app->AddStatement(w);
	app->AddStatement(z);

	Statement *res =  app->GetStatement(x->getIn());
	Statement * res2 = app->GetStatement(Point(301,301));

	EXPECT_EQ(x,res);
	EXPECT_EQ(w, res2);

}

TEST(AppEdgeCoverage, GetConnector) {
	ApplicationManager * app = new ApplicationManager();
	

	/*Invalid for the coverage satisfying*/
	// ==
	SmplAssign *j = new SmplAssign(Point(1000, 1000), "X", 0);
	SmplAssign *k = new SmplAssign(Point(1100, 1000 + UI.ASSGN_HI), "X", 0);
	Connector *l = new Connector(j,k, false);

	// >
	SmplAssign *m = new SmplAssign(Point(800, 800), "X", 0);
	SmplAssign *n = new SmplAssign(Point(750, 750), "X", 0);
	Connector *o = new Connector(m,n, false);

	// <
	SmplAssign *p = new SmplAssign(Point(750, 750), "X", 0);
	SmplAssign *q = new SmplAssign(Point(800, 800), "X", 0);
	Connector *r = new Connector(p,q, false);


	/*valid*/
	// ==
	SmplAssign *a = new SmplAssign(Point(500,500),"X",0);
	SmplAssign *b = new SmplAssign(Point(600, 500 + UI.ASSGN_HI), "X", 0);
	Connector *c = new Connector(a, b, false);

	// >
	SmplAssign *d = new SmplAssign(Point(500, 500), "X", 0);
	SmplAssign *e = new SmplAssign(Point(700,700), "X", 0);
	Connector *f = new Connector(d,e, false);

	// <
	SmplAssign *g = new SmplAssign(Point(700, 700), "X", 0);
	SmplAssign *h = new SmplAssign(Point(500, 500), "X", 0);
	Connector *i = new Connector(g,h, false);
	

	app->AddStatement(j);
	app->AddStatement(k);
	app->AddConnector(l);

	app->AddStatement(m);
	app->AddStatement(n);
	app->AddConnector(o);

	app->AddStatement(p);
	app->AddStatement(q);
	app->AddConnector(r);


	app->AddStatement(a);
	app->AddStatement(b);
	app->AddConnector(c);

	app->AddStatement(d);
	app->AddStatement(e);
	app->AddConnector(f);

	app->AddStatement(g);
	app->AddStatement(h);
	app->AddConnector(i);

	Point *parr;
	int size;
	a->getOut(parr,size);
	EXPECT_EQ(app->GetConnector(Point(parr[0].x, parr[0].y-5)), c);

	d->getOut(parr, size);
	EXPECT_EQ(app->GetConnector(Point(parr[0].x,parr[0].y+4)), f);

	g->getOut(parr, size);
	EXPECT_EQ(app->GetConnector(parr[0]), i);
}

TEST(AppEdgeCoverage, Loading_TEST_1) {
	ApplicationManager * app = new ApplicationManager();
	ifstream f("app.manager.load.test");
	f.close();
	app->Loading(f);
	EXPECT_EQ(app->Statementcurrent(), 0);
	EXPECT_EQ(app->Connectorcurrent(), 0);
}


TEST(AppEdgeCoverage, Loading_TEST_2) {
	ApplicationManager * app = new ApplicationManager();
	Start_End* st1 = new Start_End(Point(50,50),1);
	Variable* st2 = new Variable(Point(50, 50),"B","O");
	SmplAssign* st3 = new SmplAssign(Point(50, 50),"P",12);
	ReadWrite* st4 = new ReadWrite(Point(50,50),"P",false);
	ReadWrite* st5 = new ReadWrite(Point(50, 50), "P", true);
	Conditional* st6 = new Conditional(Point(50, 50),"P","P",12,"P",1);
	Start_End* st7 = new Start_End(Point(50, 50), 0);

	Connector*c1 = new Connector(st1,st5,false);
	Connector*c2 = new Connector(st5, st2, false);
	Connector*c3 = new Connector(st2,st3,false);
	Connector*c4 = new Connector(st3,st6,false);
	Connector*c5 = new Connector(st6, st4, false);
	Connector*c6 = new Connector(st6, st7, false);
	Connector*c7 = new Connector(st4,st7,false);

	app->AddStatement(st1);
	app->AddStatement(st2);
	app->AddStatement(st3);
	app->AddStatement(st4);
	app->AddStatement(st5);
	app->AddStatement(st6);
	app->AddStatement(st7);

	app->AddConnector(c1);
	app->AddConnector(c2);
	app->AddConnector(c3);
	app->AddConnector(c4);
	app->AddConnector(c5);
	app->AddConnector(c6);
	app->AddConnector(c7);

	EXPECT_EQ(app->Connectorcurrent(), 7);
	EXPECT_EQ(app->Statementcurrent(), 7);

	
	Save * action = new Save(app);
	action->Execute();
	
	// Clear The Area
	app->GetOutput()->ClearDrawArea();

	for (int i = 0; i < app->Connectorcurrent(); i++)
	{
		app->DeleteConnector(app->Connectorlist()[i]);
		i--;
	}

	for (int i = 0; i < app->Statementcurrent(); i++)
	{
		app->DeleteStatement(app->Statementlist()[i]);
		i--;
	}
	EXPECT_EQ(app->Connectorcurrent(), 0);
	EXPECT_EQ(app->Statementcurrent(), 0);


	ifstream file;
	file.open("Flow_Chart.txt");

	
	app->Loading(file);

	EXPECT_EQ(app->Connectorcurrent(), 7);
	EXPECT_EQ(app->Statementcurrent(), 7);

	bool a=false,b=false,c= false,d=false,e=false,f=false,g=false;

	for (int i = 0; i < 7; i++) {
		if (dynamic_cast<Start_End*>(app->Statementlist()[i]) && ((Start_End*)(app->Statementlist()[i]))->getKind() == 1)
			a = true;
		if (dynamic_cast<Start_End*>(app->Statementlist()[i]) && ((Start_End*)(app->Statementlist()[i]))->getKind() == 0)
			b = true;
		if (dynamic_cast<ReadWrite*>(app->Statementlist()[i]) && !((ReadWrite*)(app->Statementlist()[i]))->getKind())
			c = true;
		if (dynamic_cast<ReadWrite*>(app->Statementlist()[i]) && ((ReadWrite*)(app->Statementlist()[i]))->getKind())
			d = true;
		if (dynamic_cast<SmplAssign*>(app->Statementlist()[i]))
			e = true;
		if (dynamic_cast<Conditional*>(app->Statementlist()[i]))
			f = true;
		if (dynamic_cast<Variable*>(app->Statementlist()[i]))
			g = true;
	}
	EXPECT_TRUE(a && b && c && d && e && f && g);
}

TEST(AppEdgeCoverage, GetInput) {
	ApplicationManager App;
	Input* a = App.GetInput();
	EXPECT_NE(a, (Input*)NULL);
}
TEST_F(AppEdgeCoverage_F, GetUserAction) {	
	EXPECT_CALL(*in, GetUserAction()).WillOnce(Return(ADD_CONDITION));
	EXPECT_EQ(App->GetUserAction(),ADD_CONDITION);
}


TEST_F(AppEdgeCoverage_F, UpdateInterface) {
	mockConditional* st1 = new mockConditional();
	mockConditional* st2 = new mockConditional();
	mockConnector* c1 = new mockConnector(st1,st2);
	mockConnector* c2 = new mockConnector(st1, st2);

	App->AddStatement(st1);
	App->AddStatement(st2);
	App->AddConnector(c1);
	App->AddConnector(c2);

	EXPECT_CALL(*st1,Draw(_));
	EXPECT_CALL(*st2, Draw(_));
	EXPECT_CALL(*c1, Draw(_));
	EXPECT_CALL(*c2, Draw(_));
	App->UpdateInterface();
}

