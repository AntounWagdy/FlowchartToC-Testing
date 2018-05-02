#include "../PT-Project/ApplicationManager.h"
#include"mainMock.h"
#include<gtest\gtest.h>
#include<gmock\gmock.h>
int mainFunction(mockAppManager3 * AppManager);
int mainFunction(ApplicationManager * AppManager);

TEST_F(mainCoverage, TEST_1) {
	//Create an object of ApplicationManager
	EXPECT_CALL(*App, GetUserAction()).WillOnce(Return(ADD_ellipse_start))
		.WillOnce(Return(ADD_ellipse_END))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(SELECT))
		.WillOnce(Return(STATUS))
		.WillOnce(Return(No_Action))
		.WillOnce(Return(ADD_Single_OP))
		.WillOnce(Return(ADD_Single_OP))
		.WillOnce(Return(EDIT_STAT))
		.WillOnce(Return(EDIT_CONN))
		.WillOnce(Return(MULTI_SELECT))
		.WillOnce(Return(MOVE))
		.WillOnce(Return(COPY))
		.WillOnce(Return(CUT))
		.WillOnce(Return(DEBUG))
		.WillOnce(Return(Generate))
		.WillOnce(Return(EXIT));

	in->setPoint(Point(400, 400))
		->setPoint(500,500)
		->setPoint(400-UI.EllipseWidth / 2 +1,401)
		->setPoint(500-UI.EllipseWidth/2+1, 501);
	
	mainFunction(App);
	EXPECT_EQ(App->Statementcurrent(), 2);
	EXPECT_EQ(App->Connectorcurrent(), 1);
}

TEST_F(mainCoverage, TEST_2) {
	EXPECT_CALL(*App, GetUserAction()).WillOnce(Return(ADD_ellipse_start))
		.WillOnce(Return(ADD_ellipse_END))
		.WillOnce(Return(ADD_Read))
		.WillOnce(Return(ADD_CONDITION))
		.WillOnce(Return(ADD_Write))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(ADD_CONNECTOR))
		.WillOnce(Return(RUN))
		.WillOnce(Return(EXIT));


	in->setPoint(Point(400, 400)) // Start Loc
		->setPoint(500, 500) // End Loc
		->setPoint(300, 300) // Read Loc
		->setPoint(200, 200) // condition Loc
		->setPoint(600, 600); // write Loc
		

	EXPECT_CALL(*in, GetString(_)).WillOnce(Return("X"))
		.WillOnce(Return("X")) 
		.WillOnce(Return("=="))
		.WillOnce(Return("X"));

	EXPECT_CALL(*in, GetValue(_))
		.WillOnce(Return(1))
		.WillOnce(Return(12))
		.WillOnce(Return(12));

	in->setPoint(400 - UI.EllipseWidth / 2 + 1, 401)
		->setPoint(321, 301)

		->setPoint(321, 301)
		->setPoint(201, 201)
		
		->setPoint(201, 201)
		->setPoint(621, 601)

		->setPoint(621, 601)
		->setPoint(500 - UI.EllipseWidth / 2 + 1, 501)

		->setPoint(201, 201)
		->setPoint(500 - UI.EllipseWidth / 2 + 1, 501);

	EXPECT_CALL(*out, PrintMessage(_)).Times(AtLeast(1));
	EXPECT_CALL(*out, PrintMessage("Congratulation, your flow chart is valid, you can debug, run or generate your code :D ")).Times(1);
	EXPECT_CALL(*out, PrintMessage("12                        //Output"));
	EXPECT_CALL(*out, PrintMessage("Program has exited with code of 0*0"));
	EXPECT_CALL(*out, PrintMessage("Enter the value of X :"));
	EXPECT_CALL(*out, PrintMessage("Click on The valid Destination Statemnt : ")).Times(5);
	EXPECT_CALL(*out, PrintMessage("Click on The valid Source Statemnt : ")).Times(5);


	mainFunction(App);
	EXPECT_EQ(App->Statementcurrent(), 5);
	EXPECT_EQ(App->Connectorcurrent(), 5);
}


TEST_F(mainCoverage, TEST_3) {
	EXPECT_CALL(*App, GetUserAction()).WillOnce(Return(ADD_SMPL_ASSIGN))
		.WillOnce(Return(ADD_One_Variable))
		.WillOnce(Return(COMMENT))
		.WillOnce(Return(SAVE))
		.WillOnce(Return(DEL))
		.WillOnce(Return(LOAD))
		.WillOnce(Return(EXIT));

	in->setPoint(200, 200)
		->setPoint(400, 200)
		->setPoint(201, 201)
		->setPoint(0,0);

	EXPECT_CALL(*in, GetString(_))
		.WillOnce(Return("X"))
		.WillOnce(Return("Y"))
		.WillOnce(Return("X"))
		.WillOnce(Return("This is a comment :D"))
		.WillOnce(Return("Y"));


	EXPECT_CALL(*in, GetValue(_))
		.WillOnce(Return(12));
	mainFunction(App);
	EXPECT_EQ(App->Statementcurrent(),2);
	EXPECT_EQ(App->Connectorcurrent(),0);
	EXPECT_TRUE(dynamic_cast<SmplAssign*>(App->Statementlist()[0]) || dynamic_cast<SmplAssign*>(App->Statementlist()[1]));
	EXPECT_TRUE(dynamic_cast<Variable*>(App->Statementlist()[0]) || dynamic_cast<Variable*>(App->Statementlist()[1]));

}
int mainFunction(mockAppManager3 * AppManager) {
	ActionType ActType;
	do {
		ActType = AppManager->GetUserAction();
		AppManager->ExecuteAction(ActType);
		AppManager->UpdateInterface();
	} while (ActType != EXIT);
	return 0;
}


TEST(Project, main) {
	//mainFunction(new ApplicationManager());
}

int mainFunction(ApplicationManager * AppManager) {
	ActionType ActType;
	do {
		ActType = AppManager->GetUserAction();
		AppManager->ExecuteAction(ActType);
		AppManager->UpdateInterface();
	} while (ActType != EXIT);
	return 0;
}