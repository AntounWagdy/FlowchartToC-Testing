#include<gtest\gtest.h>
#include"../PT-Project/Actions/Action.h"
#include"../PT-Project/Actions/Add_Conn.h"
#include"../PT-Project/ApplicationManager.h"

TEST(BaseActionEdgeCoverage,Constructor) {
	ApplicationManager *App = new ApplicationManager();
	Action *a = new Add_Conn(App);
	EXPECT_EQ(a->pManager, App);
}

TEST(BaseActionEdgeCoverage, isValid) {
	ApplicationManager *App = new ApplicationManager();
	Action *st = new Add_Conn(App);

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


TEST(BaseActionEdgeCoverage, IsPoint) {
	ApplicationManager *App = new ApplicationManager();
	Action *st = new Add_Conn(App);

	bool res;
	res = st->IsPoint(Point());
	EXPECT_TRUE(res);
	res = st->IsPoint(Point(500,500));
	EXPECT_FALSE(res);
}

TEST(BaseActionEdgeCoverage, isPointDraw) {
	ApplicationManager *App = new ApplicationManager();
	Action *st = new Add_Conn(App);
	Point res;
	// Elipse
	res = st->IsPointDraw(Point(), UI.EllipseWidth);
	EXPECT_EQ(res,Point(3,0));

	res = st->IsPointDraw(Point(1000,500), UI.EllipseWidth);
	EXPECT_EQ(res, Point((UI.width - UI.EllipseWidth) - 15, 500));

	res = st->IsPointDraw(Point(500, 500), UI.EllipseWidth);
	EXPECT_EQ(res, Point(500, 500));


	// Conditional
	res = st->IsPointDraw(Point(), UI.COND_LGN);
	EXPECT_EQ(res, Point((int)(1.7*(UI.COND_LGN / sqrt(2))), 0));

	res = st->IsPointDraw(Point(1000, 500), UI.COND_LGN);
	EXPECT_EQ(res, Point((int)(UI.width - 2 * (UI.COND_LGN / sqrt(2))), 500));

	res = st->IsPointDraw(Point(500, 500), UI.COND_LGN);
	EXPECT_EQ(res, Point(500, 500));



	// ReadWrite
	res = st->IsPointDraw(Point(), UI.r_width);
	EXPECT_EQ(res, Point(30, 0));

	res = st->IsPointDraw(Point(1000, 500), UI.r_width);
	EXPECT_EQ(res, Point((int)(UI.width - (1.3*UI.r_width)), 500));

	res = st->IsPointDraw(Point(500, 500), UI.r_width);
	EXPECT_EQ(res, Point(500, 500));
}



TEST(BaseActionEdgeCoverage, ValidH) {
	ApplicationManager *App = new ApplicationManager();
	Action *st = new Add_Conn(App);
	Point res;
	
	// Elipse
	res = st->Valid_H(Point(0,1000), UI.EllipseH);
	EXPECT_EQ(res, Point(0, 1000 - UI.EllipseH + (((UI.height-UI.StBrWdth) - 1000) - 10)));

	res = st->Valid_H(Point(500, 500), UI.EllipseH);
	EXPECT_EQ(res, Point(500, 500));


	// Conditional
	res = st->Valid_H(Point(), UI.COND_LGN);
	EXPECT_EQ(res, Point(0, (int)((UI.TlBrWdth - 0.6*(-1 * (UI.COND_LGN / sqrt(2)))))));

	res = st->Valid_H(Point(0, 1000), UI.COND_LGN);
	EXPECT_EQ(res, Point(0, (int)((UI.height - UI.StBrWdth) - (1.5*UI.COND_LGN / sqrt(2)) - 8)));

	res = st->Valid_H(Point(500, 500), UI.COND_LGN);
	EXPECT_EQ(res, Point(500, 500));


	// ReadWrite
	res = st->Valid_H(Point(0, 0), UI.r_height);
	EXPECT_EQ(res, Point(0, ((2 * UI.r_height) + 35)));

	res = st->Valid_H(Point(0, 1000), UI.r_height);
	EXPECT_EQ(res, Point(0, ((UI.height - UI.StBrWdth) - UI.r_height)));

	res = st->Valid_H(Point(500, 500), UI.r_height);
	EXPECT_EQ(res, Point(500, 500));

}