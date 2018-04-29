#include<gtest\gtest.h>
#include"../PT-Project/Statements/Variable.h"

TEST(StatementEdgePairCoverage, isValid1) {
    // case 1
	Variable *st = new Variable();
	bool res = st->IsValid("!var");
	EXPECT_EQ(res, false);

}

TEST(StatementEdgePairCoverage, isValid2) {
	// case 2
	Variable *st = new Variable();
	bool res = st->IsValid("var iable");
	EXPECT_EQ(res, false);
}
TEST(StatementEdgePairCoverage, isValid3) {
	// case 3
	Variable *st = new Variable();
	bool res = st->IsValid("v");
	EXPECT_EQ(res, true);
}
TEST(StatementEdgePairCoverage, isValid4) {
	// case 4
	Variable *st = new Variable();
	bool res = st->IsValid("var");
	EXPECT_EQ(res, true);
}
TEST(StatementEdgePairCoverage, isValid5) {
	// case 5
	Variable *st = new Variable();
	bool res = st->IsValid("va!");
	EXPECT_EQ(res, false);

}