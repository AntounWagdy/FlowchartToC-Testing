#pragma once
#include<gmock\gmock.h>
#include<gtest\gtest.h>
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"
#include"../PT-Project/ApplicationManager.h"
#include"../PT-Project/Statements/Statement.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::DoDefault;
using ::testing::Invoke;



class mockInput2 : public Input {
public:
	mockInput2(window*p) :Input(p) {}
	MOCK_CONST_METHOD0(GetUserAction, ActionType());
};

class mockConditional : public Conditional {
public:
	mockConditional() : Conditional() {}
	MOCK_CONST_METHOD1(Draw, void(Output*));
};

class mockConnector : public Connector{
public:
	mockConnector(Statement * s,Statement *d) : Connector(s,d,false) {}
	MOCK_CONST_METHOD1(Draw, void(Output*));
};



struct TEST_FIXTURE_3 : testing::Test {
public:
	ApplicationManager * App;
	mockInput2 * in;
	void SetUp() {
		App = new ApplicationManager();
		in = new mockInput2(App->pOut->pWind);
		delete App->pIn;
		App->pIn = in;	
	}

	void TearDown() {
		/*
		delete App;
		delete in;
		*/
	}
};

typedef TEST_FIXTURE_3 AppEdgeCoverage_F;