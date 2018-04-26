#include"../PT-Project/CMUgraphicsLib/CMUgraphics.h"
#include"../PT-Project/GUI/UI_Info.h"
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"
#include<gmock\gmock.h>
#include<gtest\gtest.h>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::DoDefault;
using ::testing::Invoke;

class mockWindow : public window {
public:
	mockWindow(int x,int y, int z,int w) :window(x,y,z,w){}
	MOCK_METHOD1(WaitKeyPress, keytype(char&));
	MOCK_METHOD2(WaitMouseClick, clicktype(int &,int &));

	vector<char> cs;
	vector<Point> pps;
	int i = 0, j = 0;

	void addPoint(Point a) {
		pps.push_back(a);
	}
	clicktype getMouse(int &a, int &b) {
		a = pps[i].x;
		b = pps[i].y;
		i++;
		return NO_CLICK;
	}

	void addChars(char a) {
		cs.push_back(a);
	}
	keytype getCh(char & c) {
		c = cs[i++];
		return ARROW;
	}
};

struct GUIEdgeCoverage : testing::Test {
	Input * in;
	Output * out;
	mockWindow * win;
	void SetUp() {		
		out = new Output();
		win = new mockWindow(UI.width, UI.height, UI.wx, UI.wy);

		ON_CALL(*win, WaitMouseClick(_, _)).WillByDefault(Invoke(win, &mockWindow::getMouse));
		ON_CALL(*win, WaitKeyPress(_)).WillByDefault(Invoke(win, &mockWindow::getCh));

		in = new Input(win);
	}
	void TearDown() {
		/*
		delete in;
		delete out;
		delete win;
		*/
	}
};
