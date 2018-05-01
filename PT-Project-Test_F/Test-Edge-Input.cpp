#include"WindowsMock.h"
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"


TEST_F(GUIEdgeCoverage,GetString) {
	win->addChars((char)27);
	string s = in->GetString(out);
	EXPECT_EQ(s, "");

	win->addChars(8);
	win->addChars('A');
	win->addChars('n');
	win->addChars('t');
	win->addChars('o');
	win->addChars('u');
	win->addChars('q');
	win->addChars(8);
	win->addChars('n');
	win->addChars(13);

	s = in->GetString(out);
	EXPECT_EQ(s, "Antoun");
}

TEST_F(GUIEdgeCoverage, GetValue) {
	win->addChars((char)27);
	double s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(45);
	win->addChars(45);
	win->addChars(57);
	win->addChars(13);
	s = in->GetValue(out);
	EXPECT_EQ(s, -9);

	win->addChars(56);
	win->addChars(46);
	win->addChars(46);
	win->addChars(56);
	win->addChars(13);
	s = in->GetValue(out);
	EXPECT_EQ(s, 8.8);

	
	win->addChars(8);
	win->addChars(57);
	win->addChars(57);
	win->addChars(57);
	win->addChars(8);
	win->addChars(13);
	s = in->GetValue(out);
	EXPECT_EQ(s, 99);
}




TEST_F(GUIEdgeCoverage, GetUserAction) {
	win->addPoint(Point(63,0));
	UI.AppMode = DESIGN;
	ActionType s = in->GetUserAction();
	EXPECT_EQ(s, SIM_MODE);
	
	win->addPoint(Point(139, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_ellipse_start);
	
	win->addPoint(Point(234, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_Read);

	win->addPoint(Point(305, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_One_Variable);

	win->addPoint(Point(379, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_SMPL_ASSIGN);

	win->addPoint(Point(457, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_Single_OP);

	win->addPoint(Point(532, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_ellipse_END);

	win->addPoint(Point(592, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_CONDITION);

	win->addPoint(Point(646, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_CONNECTOR);

	win->addPoint(Point(717, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, COPY);

	win->addPoint(Point(781, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, CUT);

	win->addPoint(Point(838, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, MOVE);

	win->addPoint(Point(907, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, COMMENT);

	win->addPoint(Point(920, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, DSN_TOOL);

	
	// Second Row
	win->addPoint(Point(63, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, LOAD);

	win->addPoint(Point(139, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, SAVE);

	win->addPoint(Point(234, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, ADD_Write);

	win->addPoint(Point(305, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, SELECT);

	win->addPoint(Point(379, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, MULTI_SELECT);

	win->addPoint(Point(457, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, UNDO);

	win->addPoint(Point(532, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, REDO);

	win->addPoint(Point(592, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, ZoomIn);

	win->addPoint(Point(646, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, ZoomOut);

	win->addPoint(Point(717, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s,EDIT_CONN);

	win->addPoint(Point(781, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, EDIT_STAT);

	win->addPoint(Point(838, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, DEL);

	win->addPoint(Point(907, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, EXIT);
	

	win->addPoint(Point(500,500));
	s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);

	win->addPoint(Point(UI.width,UI.height));
	s = in->GetUserAction();
	EXPECT_EQ(s, STATUS);

	win->addPoint(Point(63, 0));
	UI.AppMode = SIMULATION;
	s = in->GetUserAction();
	EXPECT_EQ(s, DSN_MODE);

	win->addPoint(Point(157, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, RUN);

	win->addPoint(Point(234, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, DEBUG);


	win->addPoint(Point(314, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, VALID);

	win->addPoint(Point(395, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, Generate);

	win->addPoint(Point(400, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);

	win->addPoint(Point(400, 200));
	s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);

}

TEST_F(GUIEdgeCoverage, GetPointClicked) {
	EXPECT_CALL(*win, WaitMouseClick(_,_));
	win->addPoint(Point(1,2));
	Point p;
	in->GetPointClicked(p);
	EXPECT_EQ(p, Point(1, 2));
}