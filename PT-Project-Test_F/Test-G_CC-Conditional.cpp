#include <gtest\gtest.h>
#include"..\PT-Project\Statements\Conditional.h"

TEST(ConditionalGACC, Run) {
	Conditional *st = new Conditional(Point(50, 50), "X", ">=", 12, "", 1);
	map<string, double> m;
	EXPECT_EQ(st->Run(m), 0);

	m["X"] = 12;
	st = new Conditional(Point(50, 50), "X", ">=", 12, "Y", 2);
	EXPECT_EQ(st->Run(m), 0);

	m.erase("X");
	st = new Conditional(Point(50, 50), "X", ">=", 12, "", 2);
	EXPECT_EQ(st->Run(m), 3);

	st = new Conditional(Point(50, 50), "", ">=", 12, "Y", 1);
	EXPECT_EQ(st->Run(m), 3);

	// Till here we satisfied the GACC for the first and the second and part of the third if condition
	m["X"] = 12;
	m["Y"] = 12;
	st = new Conditional(Point(50, 50), "X", ">=", 12, "Y", 2);
	EXPECT_EQ(st->Run(m), 1);

	m.erase("Y");
	st = new Conditional(Point(50, 50), "X", ">=", 14, "Y", 1);
	EXPECT_EQ(st->Run(m), 2);
	// others for GACC are already covered in Edge coverage
}


TEST(ConditionalGICC, Run) {
	// here we will do the testcases for GICC that does not Exist in GACC
	
	Conditional *st = new Conditional(Point(50, 50), "X", ">=", 12, "Y", 1);
	map<string, double> m;
	EXPECT_EQ(st->Run(m), 0);


	st = new Conditional(Point(50, 50), "", ">=", 12, "", 2);
	EXPECT_EQ(st->Run(m), 3);

	m["Y"] = 1;
	m["X"] = 12;
	st = new Conditional(Point(50, 50), "X", ">=", 12, "Y", 1);
	EXPECT_EQ(st->Run(m), 1);
}