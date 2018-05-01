#include"WindowsMock.h"
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"

TEST_F(GUIGACCCoverage, GetString) {
	win->addChars(40);
	win->addChars(50);
	win->addChars(70);
	win->addChars(13);

	double s = in->GetValue(out);
	EXPECT_EQ(s, 2);
}

TEST_F(GUIGACCCoverage, GetUserAction_TEST_1) {
	UI.AppMode = DESIGN;
	win->addPoint(Point(0,-1));
	ActionType s = in->GetUserAction();
	EXPECT_EQ(s, STATUS);

	win->addPoint(Point(-1, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, DSN_TOOL);


	win->addPoint(Point(910, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, DSN_TOOL);

	win->addPoint(Point(-1, 60));
	s = in->GetUserAction();
	EXPECT_EQ(s, DSN_TOOL);
}



TEST_F(GUIGACCCoverage, GetUserAction_TEST_2) {
	UI.AppMode = SIMULATION;
	win->addPoint(Point(0, -1));
	ActionType s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);

	win->addPoint(Point(-1, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);


	win->addPoint(Point(400, 0));
	s = in->GetUserAction();
	EXPECT_EQ(s, No_Action);
}