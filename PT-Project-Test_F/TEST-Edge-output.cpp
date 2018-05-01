#include"WindowsMock.h"
#include"../PT-Project/GUI/Output.h"
#include<fstream>

TEST_F(GUIEdgeCoverage, outputConstructor) {
	EXPECT_EQ(UI.width, 915);
	EXPECT_EQ(UI.height, 700);
	EXPECT_EQ(UI.wx, 15);
	EXPECT_EQ(UI.wy, 15);

	EXPECT_EQ(UI.AppMode, DESIGN);

	EXPECT_EQ(UI.StBrWdth, 50);
	EXPECT_EQ(UI.TlBrWdth, 116);
	EXPECT_EQ(UI.MnItWdth, 80);

	EXPECT_EQ(UI.DrawClr, BLUE);
	EXPECT_EQ(UI.HiClr, RED);
	EXPECT_EQ(UI.MsgClr, BLACK);

	EXPECT_EQ(UI.ASSGN_WDTH, 160);
	EXPECT_EQ(UI.ASSGN_HI, 33);

	EXPECT_EQ(UI.COND_LGN, 43);

	EXPECT_EQ(UI.r_width, 100);
	EXPECT_EQ(UI.r_height, 34);

	EXPECT_EQ(UI.EllipseH, 46);
	EXPECT_EQ(UI.EllipseWidth, 80);

	
	//Create the output window
	EXPECT_NE(out->pWind, (window*)NULL);
	string dir = "E:\\CMP 2018\\402\\Testing\\Trials\\PT-Project\\images\\bg1.jpg" ;
	ifstream f(dir);
	EXPECT_TRUE(f.good());
	EXPECT_CALL(*win, DrawImage(_,0,UI.TlBrWdth,-1,-1));
	EXPECT_CALL(*win, SetPen(BLACK,2));	
}

TEST_F(GUIEdgeCoverage, OutputCreateInput) {
	Input *temp = out->CreateInput();
	EXPECT_NE(temp, (Input*)NULL);
}

TEST_F(GUIEdgeCoverage, OutputCreateWindow) {
	window *temp = out->CreateWind(1,1,1,1);
	EXPECT_NE(temp, (window*)NULL);
}



TEST_F(GUIEdgeCoverage, OutputCreateStatusBar) {
	out->CreateStatusBar();
	EXPECT_CALL(*win, DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth,FRAME));
}

TEST_F(GUIEdgeCoverage, CreateDesignToolBar) {
	out->CreateDesignToolBar();
	EXPECT_EQ(UI.AppMode , DESIGN);	//Design Mode
	EXPECT_CALL(*win,DrawImage(_, 0, 0,-1,-1));
}

TEST_F(GUIEdgeCoverage, OutputCreateSimulationToolBar) {

	EXPECT_CALL(*win, DrawImage(_, _, _, _, _)).Times(2);

	EXPECT_CALL(*win, SetPen(BLACK, 2)); //New!
	EXPECT_CALL(*win, DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth,FRAME));
	out->CreateSimulationToolBar();

	EXPECT_EQ(UI.AppMode, SIMULATION);
}


TEST_F(GUIEdgeCoverage, OuputClearStatusBar) {
	EXPECT_CALL(*win, DrawImage(_, _, _, _, _));
	EXPECT_CALL(*win, DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth, FRAME));
	out->ClearStatusBar();
}

TEST_F(GUIEdgeCoverage, OutputClearDrawArea_TEST1) {
	EXPECT_CALL(*win, SetPen(BLACK,1));
	EXPECT_CALL(*win, DrawImage(_, UI.TlBrWdth, UI.width, UI.height - UI.StBrWdth - UI.TlBrWdth,-1));
	UI.AppMode = SIMULATION;
	out->ClearDrawArea();
}
TEST_F(GUIEdgeCoverage, OutputClearDrawArea_TEST2) {
	EXPECT_CALL(*win, SetPen(BLACK, 1));
	EXPECT_CALL(*win, DrawImage(_, 0, UI.TlBrWdth, UI.width, UI.height - UI.StBrWdth - UI.TlBrWdth));
	UI.AppMode = DESIGN;
	out->ClearDrawArea();
}

TEST_F(GUIEdgeCoverage, OutputPrintMessage) {
	string Msg = "Hello world";
	
	EXPECT_CALL(*win, SetPen(UI.MsgClr, 50));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(10, UI.height - (int)(UI.StBrWdth / 1.5), Msg));
	EXPECT_CALL(*win, SetPen(UI.MsgClr, 2));
	
	out->PrintMessage(Msg);
}

TEST_F(GUIEdgeCoverage, OutputDrawAssign_TEST1) {
	Point Left = Point(500, 400);
	int width = UI.ASSGN_WDTH;
	int height = UI.ASSGN_HI;
	string Text = "x=y";
	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win, DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height,FILLED,0,0));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 15, Left.y + height / 4, Text));

	out->DrawAssign(Left,width,height,Text,false);
}


TEST_F(GUIEdgeCoverage, OutputDrawAssign_TEST2) {
	Point Left = Point(500, 400);
	int width = UI.ASSGN_WDTH;
	int height = UI.ASSGN_HI;
	string Text = "x=y";
	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win, DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height, FILLED, 0, 0));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 15, Left.y + height / 4, Text));

	out->DrawAssign(Left, width, height, Text, true);
}


TEST_F(GUIEdgeCoverage, OutputDrawCond_TEST1) {
	Point p = Point(500, 400);
	int length = UI.COND_LGN;
	string Text = "x=y";

	int x[] = { p.x - length,p.x,p.x + length,p.x };
	int y[] = { p.y,p.y - length,p.y,p.y + length };

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win, DrawPolygon(x, y, 4, FILLED));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(p.x - (3 * length) / 4, p.y - 10, Text));

	out->DrawCond(p, length, Text, false);
}


TEST_F(GUIEdgeCoverage, OutputDrawCond_TEST2) {
	Point p = Point(500, 400);
	int length = UI.COND_LGN;
	string Text = "x=y";

	int x[] = { p.x - length,p.x,p.x + length,p.x };
	int y[] = { p.y,p.y - length,p.y,p.y + length };

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win, DrawPolygon(x,y,4,FILLED));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(p.x - (3 * length) / 4, p.y - 10, Text));

	out->DrawCond(p, length, Text, true);
}




TEST_F(GUIEdgeCoverage, OutputDrawConnection_TEST1) {
	Point p1 = Point(500, 600);
	Point p2 = Point(500, 500);


	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y, p1.x, p1.y + 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y + 10, p1.x + 100, p1.y + 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p1.x + 100, p1.y + 10, p1.x + 100, p2.y - 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p1.x + 100, p2.y - 10, p2.x, p2.y - 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y - 10, p2.x, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5,FRAME));

	out->DrawConn(p1, p2, false);
}


TEST_F(GUIEdgeCoverage, OutputDrawConnection_TEST2) {
	Point p1 = Point(500, 500);
	Point p2 = Point(500, 600);

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y, p1.x, p1.y + 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y + 10, p2.x, p1.y + 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p1.y + 10, p2.x, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5,FRAME));

	out->DrawConn(p1, p2, false);
}


TEST_F(GUIEdgeCoverage, OutputDrawConnection_TEST3) {
	Point p1 = Point(500, 500);
	Point p2 = Point(300, 500);

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y, p1.x, p1.y - 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p1.x, p1.y - 10, p2.x, p2.y - 10,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y - 10, p2.x, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5,FRAME));
	EXPECT_CALL(*win,DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5,FRAME));

	out->DrawConn(p1, p2, false);
}



TEST_F(GUIEdgeCoverage, OutputDrawConnection_TEST4) {
	Point p1 = Point(500, 500);
	Point p2 = Point(300, 500);

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));

	EXPECT_CALL(*win, DrawLine(p1.x, p1.y, p1.x, p1.y - 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p1.x, p1.y - 10, p2.x, p2.y - 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y - 10, p2.x, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5, FRAME));

	out->DrawConn(p1, p2, true);
}


TEST_F(GUIEdgeCoverage, OutputDrawRead_Test_1) {
	Point Left = Point(500, 500);
	int r_width = UI.r_width;
	int r_height = UI.r_height;
	string Text = "X";
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win,DrawPolygon(a, b, 4,FRAME));
	EXPECT_CALL(*win,SetPen(BLACK, 2));
	EXPECT_CALL(*win,SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win,DrawString(Left.x + 15, Left.y + 7, "Read " + Text));
	out->DrawRead(Left, r_width,r_height,Text, true);
}


TEST_F(GUIEdgeCoverage, OutputDrawRead_Test_2) {
	Point Left = Point(500, 500);
	int r_width = UI.r_width;
	int r_height = UI.r_height;
	string Text = "X";
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win, DrawPolygon(a, b, 4, FRAME));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 15, Left.y + 7, "Read " + Text));
	out->DrawRead(Left, r_width, r_height, Text, false);
}

TEST_F(GUIEdgeCoverage, OutputDrawWrite_Test_1) {
	Point Left = Point(500, 500);
	int r_width = UI.r_width;
	int r_height = UI.r_height;
	string Text = "X";
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));
	EXPECT_CALL(*win, DrawPolygon(a, b, 4, FRAME));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 15, Left.y + 7, "Write " + Text));
	out->DrawWrite(Left, r_width, r_height, Text, false);
}


TEST_F(GUIEdgeCoverage, OutputDrawWrite_Test_2) {
	Point Left = Point(500, 500);
	int r_width = UI.r_width;
	int r_height = UI.r_height;
	string Text = "X";
	int a[4] = { Left.x, Left.x - 20, Left.x + r_width, Left.x + r_width + 20 };
	int b[4] = { Left.y, Left.y + r_height, Left.y + r_height, Left.y };

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win, DrawPolygon(a, b, 4, FRAME));
	EXPECT_CALL(*win, SetPen(BLACK, 2));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 15, Left.y + 7, "Write " + Text));
	out->DrawWrite(Left, r_width, r_height, Text, true);
}


TEST_F(GUIEdgeCoverage, OutputDrawElipse_Test_1) {
	Point Left = Point(500, 500);
	int EllipseWidth = UI.EllipseWidth;
	int EllipseH = UI.EllipseWidth;
	string Text = "Start";
	
	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	
	EXPECT_CALL(*win,DrawEllipse(Left.x, Left.y, Left.x + EllipseWidth, Left.y + EllipseH, FILLED));
	EXPECT_CALL(*win,SetPen(BLACK,1));
	EXPECT_CALL(*win,SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win,DrawString(Left.x + 25, Left.y + 15, Text));

	out->DrawEllipse(Left, EllipseWidth, EllipseH, Text, true);
}


TEST_F(GUIEdgeCoverage, OutputDrawElipse_Test_2) {
	Point Left = Point(500, 500);
	int EllipseWidth = UI.EllipseWidth;
	int EllipseH = UI.EllipseWidth;
	string Text = "Start";

	EXPECT_CALL(*win, SetPen(UI.DrawClr, 3));

	EXPECT_CALL(*win, DrawEllipse(Left.x, Left.y, Left.x + EllipseWidth, Left.y + EllipseH, FILLED));
	EXPECT_CALL(*win, SetPen(BLACK, 1));
	EXPECT_CALL(*win, SetFont(20, BOLD, BY_NAME, "Arial"));
	EXPECT_CALL(*win, DrawString(Left.x + 25, Left.y + 15, Text));

	out->DrawEllipse(Left, EllipseWidth, EllipseH, Text, false);
}

