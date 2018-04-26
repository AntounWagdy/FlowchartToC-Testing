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


class mockInput : public Input {
	public:
		mockInput(window*p) :Input(p) {}
		MOCK_CONST_METHOD1(GetPointClicked, void(Point & p));
		MOCK_CONST_METHOD1(GetString, string(Output *pO));
		MOCK_CONST_METHOD1(GetValue, double(Output *pO));


		vector<Point> pp;
		int i = 0;
		void setPoint(Point a) {
			pp.push_back(a);
		}
		void getPoint(Point &p) {
			p = pp[i++];
		}
};

class mockAppManager : public ApplicationManager{
	public:
		mockAppManager() :ApplicationManager() {}
		MOCK_METHOD1(GetStatement, Statement*(Point p));

		MOCK_CONST_METHOD0(GetOutput, Output*());
		MOCK_CONST_METHOD0(GetInput, Input*());
};

class mockOutput : public Output {
public:
	mockOutput():Output() {}
	MOCK_METHOD1(PrintMessage,void(string Message));
	MOCK_METHOD0(CreateInput, Input*());
};



//==================================================================================//
//								Testing Fixture          							//
//==================================================================================//


typedef ActionEdgeCoverage ActionGACC;
typedef ActionEdgeCoverage ActionGICC;


struct ActionEdgeCoverage : testing::Test {
public:
	mockAppManager *App;
	mockOutput * out;
	mockInput * in;

	void SetUp() {
		App = new mockAppManager();
		out = new mockOutput();
		in = new mockInput(out->pWind);

		ON_CALL(*in, GetPointClicked(_)).WillByDefault(Invoke(in, &mockInput::getPoint));
		
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
