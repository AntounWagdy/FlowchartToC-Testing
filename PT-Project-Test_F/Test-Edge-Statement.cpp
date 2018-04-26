#include<gtest\gtest.h>
#include"../PT-Project/Statements/Variable.h"


TEST(StatementEdgeCoverage, Constructor) {
	Variable *st = new Variable();
	EXPECT_EQ(st->Text,"");
	EXPECT_FALSE(st->Selected);
	EXPECT_EQ(st->getID(), st->static_ID);
}

TEST(StatementEdgeCoverage, settersAndGetters) {
	Variable *st = new Variable();
	EXPECT_EQ(st->GetComment(),"\"\"");
	st->Comment("hello");
	EXPECT_EQ(st->GetComment(), "hello");
}
TEST(StatementEdgeCoverage, isValid) {
	Variable *st = new Variable();
	bool res;
	res = st->IsValid("1Hello");
	EXPECT_EQ(res, false);

	res = st->IsValid("1Hello");
	EXPECT_EQ(res, false);
	
	res = st->IsValid("(Hello");
	EXPECT_EQ(res, false);

	res = st->IsValid("H(llo");
	EXPECT_EQ(res, false);

	res = st->IsValid("Hello");
	EXPECT_EQ(res, true);
}

