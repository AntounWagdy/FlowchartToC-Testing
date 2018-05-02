#include<gmock\gmock.h>
#include<gtest\gtest.h>
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"
#include"../PT-Project/ApplicationManager.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::DoDefault;
using ::testing::Invoke;



//==================================================================================//
//	             Input, output, and application manager Mocks           			//
//==================================================================================//


class mockInput3 : public Input {
	public:
		mockInput3(window*p) :Input(p) {}
		MOCK_CONST_METHOD1(GetPointClicked, void(Point & p));
		MOCK_CONST_METHOD1(GetString, string(Output *pO));
		MOCK_CONST_METHOD1(GetValue, double(Output *pO));


		vector<Point> pp;
		int i = 0;
		mockInput3* setPoint(Point a) {
			pp.push_back(a);
			return this;
		}
		mockInput3* setPoint(int a ,int b) {
			pp.push_back(Point(a, b));
			return this;
		}
		void getPoint(Point &p) {
			p = pp[i++];
		}
};

class mockOutput3 : public Output {
public:
	mockOutput3():Output() {}
	MOCK_METHOD1(PrintMessage,void(string Message));
	MOCK_METHOD0(CreateInput, Input*());
};


class mockAppManager3 : public ApplicationManager {
public:
	mockAppManager3() :ApplicationManager() {}
	MOCK_CONST_METHOD0(GetOutput, Output*());
	MOCK_CONST_METHOD0(GetInput, Input*());
	MOCK_CONST_METHOD0(GetUserAction, ActionType());
};


//==================================================================================//
//								Testing Fixture          							//
//==================================================================================//


struct TEST_FIXTURE_4 : testing::Test {
public:
	mockAppManager3 *App;
	mockOutput3 * out;
	mockInput3 * in;

	void SetUp() {
		App = new mockAppManager3();
		out = new mockOutput3();
		in = new mockInput3(out->pWind);
		delete App->pOut;
		App->pOut = out;

		delete App->pIn;
		App->pIn = in;


		ON_CALL(*in, GetPointClicked(_)).WillByDefault(Invoke(in, &mockInput3::getPoint));
		EXPECT_CALL(*App, GetOutput()).WillRepeatedly(Return(out));
		EXPECT_CALL(*App, GetInput()).WillRepeatedly(Return(in));

	}

	void TearDown() {
		/*
		delete App;
		delete in;
		delete out;
		*/
	}
};

typedef TEST_FIXTURE_4 mainCoverage;