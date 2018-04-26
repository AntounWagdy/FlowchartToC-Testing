#include <gtest\gtest.h>
#include"..\PT-Project\Statements\Conditional.h"

TEST(ConditionalEdgeCoverage, FirstConstructor) {
	Point pos{ 50,50 };
	Conditional *st = new Conditional(pos, "X", ">", 2, "", 1);
	EXPECT_NE(st , (Conditional *)NULL);


	EXPECT_EQ(st->Text, "X>2");
	EXPECT_EQ(st->center.x, pos.x);
	EXPECT_EQ(st->center.y, pos.y);
	EXPECT_EQ(st->pConn[0], (Connector*)NULL);
	EXPECT_EQ(st->pConn[1], (Connector*)NULL);
	EXPECT_EQ(st->Inlet.x ,50);
	EXPECT_EQ(st->Inlet.y , 50 - UI.COND_LGN);

	EXPECT_EQ(st->Outlet[0].x, 50+UI.COND_LGN);
	EXPECT_EQ(st->Outlet[0].y, 50);
	EXPECT_EQ(st->Outlet[1].x, 50 - UI.COND_LGN);
	EXPECT_EQ(st->Outlet[1].y, 50);
	EXPECT_EQ(st->GetComment(),"\"\"");
}




TEST(ConditionalEdgeCoverage, SecondConstructor) {
	Conditional*s = new Conditional();
	EXPECT_NE(s, (Conditional*)NULL);
}


TEST(ConditionalEdgeCoverage, updateStatementText) {
	Conditional*st = new Conditional(Point(), "", ">", 1, "Y", 2);
	st->UpdateStatementText();
	EXPECT_EQ(st->Text, "    ==  ");

	st = new Conditional(Point(), "X", ">", 1, "Y", 2);
	EXPECT_EQ(st->Text, "X>Y");

	st = new Conditional(Point(), "X", ">", 1, "Y", 1);
	EXPECT_EQ(st->Text, "X>1");
}

TEST(ConditionalEdgeCoverage, Operator) {
	Conditional* st = new Conditional();
	EXPECT_EQ(st->Operator("=="),"Equ");
	EXPECT_EQ(st->Operator("!="), "NotEqu");
	EXPECT_EQ(st->Operator(">"), "GRT");
	EXPECT_EQ(st->Operator("<"), "SML");
	EXPECT_EQ(st->Operator(">="), "GrtEqu");
	EXPECT_EQ(st->Operator("<="), "SmlEqu");
}


TEST(ConditionalEdgeCoverage, OperatorS) {
	Conditional* st = new Conditional();
	st->Operator_S("Equ");
	EXPECT_EQ(st->Op,"==");
	st->Operator_S("NotEqu");
	EXPECT_EQ(st->Op, "!=");
	st->Operator_S("GRT");
	EXPECT_EQ(st->Op, ">");
	st->Operator_S("SML");
	EXPECT_EQ(st->Op, "<");
	st->Operator_S("GrtEqu");
	EXPECT_EQ(st->Op, ">=");
	st->Operator_S("SmlEqu");
	EXPECT_EQ(st->Op, "<=");
}

TEST(ConditionalEdgeCoverage, settersANDgetters) {
	Conditional *st = new Conditional(Point(50,30), "", ">", 1, "Y", 2);
	st->SetCenter(50, 10, 20);
	EXPECT_EQ(st->center.x, 50);
	EXPECT_EQ(st->center.y, 30);
	
	EXPECT_EQ(st->getCorner().x, 50 - UI.COND_LGN);
	EXPECT_EQ(st->getCorner().y, 30 - UI.COND_LGN);

	EXPECT_EQ(st->getIn().x, 50);
	EXPECT_EQ(st->getIn().y, 30 - UI.COND_LGN);

	EXPECT_EQ(st->width_height().x,UI.COND_LGN);
	EXPECT_EQ(st->width_height().y, UI.COND_LGN);

	Point * parr;
	int size;
	st->getOut(parr, size);
	EXPECT_EQ(size, 2);
	EXPECT_EQ(parr[0].x, 50 + UI.COND_LGN);
	EXPECT_EQ(parr[0].y, 30);
	EXPECT_EQ(parr[1].x, 50 - UI.COND_LGN);
	EXPECT_EQ(parr[1].y, 30);



	st->SetID(12);
	EXPECT_EQ(12, st->getID());

	st->setLHS("T");
	EXPECT_EQ(st->LHS,"T");

	st->setOp("==");
	EXPECT_EQ("==",st->Op);

	st->setRHS(12);
	EXPECT_EQ(st->RHS1, 12);

	st->setRHS("Y");
	EXPECT_EQ(st->RHS2, "Y");

	Connector *x = new Connector((Statement*)new Conditional(), (Statement*)new Conditional(),false);
	Connector *y = new Connector((Statement*)new Conditional(), (Statement*)new Conditional(), false);

	st->setFConn(x);
	EXPECT_EQ(st->pConn[0], x);

	st->setSConn(y);
	EXPECT_EQ(st->pConn[1], y);
	// Deleting the pointer after setting it should be studied. 
	// but here we assume that it won't happen as it is not the function of the program
	
	st->setFConn(NULL);
	st->setSConn(NULL);
	st->setConn(x);
	EXPECT_EQ(st->pConn[0], x);
	st->setConn(y);
	EXPECT_EQ(st->pConn[1], y);

	Connector**arr;
	st->getConn(arr, size);
	EXPECT_EQ(size, 2);
	EXPECT_EQ(arr[0], x);
	EXPECT_EQ(arr[1], y);

}

// draw would be delayed for now and tested with input and output (same as print info)

TEST(ConditionalEdgeCoverage, Save) {
	Conditional * st = new Conditional(Point(50,100), "X", ">", 1, "Y", 2); // X>Y

	ofstream o;
	o.open("cond.test");
	st->Save(o);
	o.close();

	ifstream file;
	file.open("cond.test");
	string s;
	int i;
	file >> s;
	EXPECT_EQ(s, "COND");
	file >> i;
	EXPECT_EQ(i, st->getID());
	file >> i;
	EXPECT_EQ(i, st->center.x);
	file >> i;
	EXPECT_EQ(i, st->center.y - UI.COND_LGN);
	file >> s;
	EXPECT_EQ(st->LHS, s);
	
	file >> s;
	string temp = st->Op;
	st->Operator(s);
	EXPECT_EQ(st->Op,temp);

	file >> s;
	EXPECT_EQ(st->RHS2, s);
	file >> s;
	EXPECT_EQ("\"\"", s); // Comment
	file.close();


	// Second test case
	st = new Conditional(Point(), "X", ">", 1, "Y", 1); // X>1
	o.open("cond.Save.test");
	st->Save(o);
	o.close();

	file.open("cond.Save.test");
	
	file >> s;
	EXPECT_EQ(s, "COND");
	file >> i;
	EXPECT_EQ(i, st->getID());
	file >> i;
	EXPECT_EQ(i, st->center.x);
	file >> i;
	EXPECT_EQ(i, st->center.y - UI.COND_LGN);
	file >> s;
	EXPECT_EQ(st->LHS, s);

	file >> s;
	temp = st->Op;
	st->Operator(s);
	EXPECT_EQ(st->Op, temp);

	file >> i;
	EXPECT_EQ(st->RHS1, i);
	file >> s;
	EXPECT_EQ("\"\"", s); // Comment
}


TEST(ConditionalEdgeCoverage, Load) {
	Point pos{ 50,50 };
	Conditional *s = new Conditional(pos, "X", ">", 2, "", 1);
	
	ofstream o;
	o.open("cond.load.test");
	s->Save(o);
	o.close();


	ifstream i;
	string temp;
	i.open("cond.load.test");
	i >> temp;
	Conditional *st = new Conditional();
	st->Load(i);

	EXPECT_NE(st, (Conditional *)NULL);
	EXPECT_EQ(st->Text, "X>2");
	EXPECT_EQ(st->center.x, pos.x);
	EXPECT_EQ(st->center.y, pos.y);
	EXPECT_EQ(st->pConn[0], (Connector*)NULL);
	EXPECT_EQ(st->pConn[1], (Connector*)NULL);
	EXPECT_EQ(st->Inlet.x, 50);
	EXPECT_EQ(st->Inlet.y, 50 - UI.COND_LGN);

	EXPECT_EQ(st->Outlet[0].x, 50 + UI.COND_LGN);
	EXPECT_EQ(st->Outlet[0].y, 50);
	EXPECT_EQ(st->Outlet[1].x, 50 - UI.COND_LGN);
	EXPECT_EQ(st->Outlet[1].y, 50);
	EXPECT_EQ(st->GetComment(), "\"\"");
}


TEST(ConditionalEdgeCoverage, Run) {
	Point pos{ 50,50 };
	Conditional *st = new Conditional(pos, "", ">", 2, "", 1);
	map<string, double>m;
	int res = st->Run(m);
	EXPECT_EQ(res, 3);
	st->setLHS("X");
	res = st->Run(m);
	EXPECT_EQ(res, 0);

	st = new Conditional(pos, "X", ">", 2, "Y", 2);
	m["X"] = 1;
	res = st->Run(m);
	EXPECT_EQ(res, 0);

	m["Y"] = 2;
	// Operation of != Variable
	st->Op = "!=";
	res = st->Run(m);
	EXPECT_EQ(res, 1);
	
	m["Y"] = 1;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of != Value
	st->def = 1;
	st->RHS1 = 4;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 1;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of == Variable
	st->Op = "==";
	st->def = 2;
	m["X"] = m["Y"] = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	m["Y"] = 1;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of == Value
	st->def = 1;
	st->RHS1 = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 1;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of > Variable
	st->Op = ">";
	st->def = 2;
	m["X"] = 10 , m["Y"] = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	m["Y"] = 15;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of > Value
	st->def = 1;
	st->RHS1 = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 15;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of >= Variable
	st->Op = ">=";
	st->def = 2;
	m["X"] = 10, m["Y"] = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	m["Y"] = 15;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of >= Value
	st->def = 1;
	st->RHS1 = 5;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 15;
	res = st->Run(m);
	EXPECT_EQ(res, 2);



	// Operation of < Variable
	st->Op = "<";
	st->def = 2;
	m["X"] = 5, m["Y"] = 10;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	m["Y"] = 2;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of < Value
	st->def = 1;
	st->RHS1 = 10;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 2;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of <= Variable
	st->Op = "<=";
	st->def = 2;
	m["X"] = 5, m["Y"] = 10;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	m["Y"] = 2;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

	// Operation of <= Value
	st->def = 1;
	st->RHS1 = 10;
	res = st->Run(m);
	EXPECT_EQ(res, 1);

	st->RHS1 = 2;
	res = st->Run(m);
	EXPECT_EQ(res, 2);

}