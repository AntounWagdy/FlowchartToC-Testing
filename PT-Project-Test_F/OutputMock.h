#pragma once
#include"../PT-Project/GUI/Output.h"
#include<gmock\gmock.h>


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::DoDefault;
using ::testing::Invoke;


class mockOutput2 : public Output {
public:
	mockOutput2():Output() {}
	
	MOCK_METHOD5(DrawAssign , void(Point , int , int , string , bool));

	MOCK_METHOD4(DrawCond, void(Point Center, int length, string Text, bool Selected ));
	MOCK_METHOD3(DrawConn, void(Point p1, Point p2, bool selected));
	MOCK_METHOD5(DrawEllipse, void(Point Left, int, int, string Text, bool Selected ));

	MOCK_METHOD5(DrawRead, void(Point left, int width, int height, string text, bool selected ));
	MOCK_METHOD5(DrawWrite, void(Point left, int width, int height, string text, bool selected ));

	MOCK_METHOD1(PrintMessage, void(string ));	//Prints a message on Status bar
};