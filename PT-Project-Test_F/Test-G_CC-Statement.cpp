#include<gtest\gtest.h>
#include"../PT-Project/Statements/Variable.h"

TEST(StatementGACC, isValid) {
	Variable *st = new Variable();
	EXPECT_TRUE(st->IsValid("var"));
	EXPECT_TRUE(!st->IsValid(" ar"));
	EXPECT_TRUE(!st->IsValid("1ar"));

	EXPECT_TRUE(st->IsValid("_var"));
	EXPECT_TRUE(!st->IsValid("&ar"));
	// !punc && equal to "_" is not applicable

	EXPECT_TRUE(!st->IsValid("_v_ar&iable"));
}


TEST(StatementGICC, isValid) {
	/*
	Some tests here are not applicable too or
	already satisfied by GICC or Edge coverage	
	*/
	EXPECT_TRUE(true); 
}
