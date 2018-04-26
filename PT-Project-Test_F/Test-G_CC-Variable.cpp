#include"../PT-Project/Statements/Variable.h"
#include<gtest\gtest.h>

TEST(VariableGACC,Run){
	Variable *st = new Variable(Point(),"","");
	map<string, double>m;
	EXPECT_EQ(st->Run(m),3);
	
	st = new Variable(Point(), "X", "");
	EXPECT_EQ(st->Run(m), 3);

	st = new Variable(Point(), "", "Y");
	EXPECT_EQ(st->Run(m), 3);
}

TEST(VariableGICC, Run) {
	Variable *st = new Variable(Point(), "X", "Y");
	map<string, double>m;
	EXPECT_EQ(st->Run(m), 0);
}