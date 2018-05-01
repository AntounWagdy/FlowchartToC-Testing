#include"WindowsMock.h"
#include"../PT-Project/GUI/Output.h"


TEST_F(GUIEdgePairCoverage, OutputDrawConnection_TEST1) {
	Point p1 = Point(500, 600);
	Point p2 = Point(500, 500);

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win, DrawLine(p1.x, p1.y, p1.x, p1.y + 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p1.x, p1.y + 10, p1.x + 100, p1.y + 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p1.x + 100, p1.y + 10, p1.x + 100, p2.y - 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p1.x + 100, p2.y - 10, p2.x, p2.y - 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y - 10, p2.x, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5, FRAME));

	out->DrawConn(p1, p2, true);
}


TEST_F(GUIEdgePairCoverage, OutputDrawConnection_TEST2) {
	Point p1 = Point(500, 500);
	Point p2 = Point(500, 600);

	EXPECT_CALL(*win, SetPen(UI.HiClr, 3));
	EXPECT_CALL(*win, DrawLine(p1.x, p1.y, p1.x, p1.y + 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p1.x, p1.y + 10, p2.x, p1.y + 10, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p1.y + 10, p2.x, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x - 5, p2.y - 5, FRAME));
	EXPECT_CALL(*win, DrawLine(p2.x, p2.y, p2.x + 5, p2.y - 5, FRAME));

	out->DrawConn(p1, p2, true);
}

