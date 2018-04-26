#include<gtest\gtest.h>
#include"../PT-Project/Actions/Action.h"
#include"../PT-Project/Actions/Add_Conn.h"
#include"../PT-Project/ApplicationManager.h"


TEST(BaseActionGACC, IsPoint) {
	ApplicationManager *app = new ApplicationManager();
	Add_Conn *a = new Add_Conn(app);
	EXPECT_TRUE(a->IsPoint(Point(0,100)));
	EXPECT_TRUE(!a->IsPoint(Point(0, 600)));
	EXPECT_TRUE(a->IsPoint(Point(0, 750)));
	// GICC is not applicable here
}


TEST(BaseActionGACC, IsPointDraw) {
	ApplicationManager *app = new ApplicationManager();
	Add_Conn *a = new Add_Conn(app);
	EXPECT_EQ(a->IsPointDraw(Point(),UI.ASSGN_WDTH),Point(3,0));
	EXPECT_EQ(a->IsPointDraw(Point(),UI.EllipseWidth),Point(3,0));
	// Some of GACC testcases  are not applicable here
	// GICC is not applicable here
}

TEST(BaseActionGACC, IsValid_h) {
	ApplicationManager *app = new ApplicationManager();
	Add_Conn *a = new Add_Conn(app);
	EXPECT_EQ(a->Valid_H(Point(), UI.ASSGN_WDTH), Point());
	EXPECT_EQ(a->Valid_H(Point(), UI.EllipseWidth), Point(0, 195));
	// Some of GACC testcases  are not applicable here
	// GICC is not applicable here
}


