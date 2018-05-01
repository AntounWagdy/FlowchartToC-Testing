#include"WindowsMock.h"
#include"../PT-Project/GUI/Input.h"
#include"../PT-Project/GUI/Output.h"


TEST_F(GUIEdgePairCoverage, GetString_TEST_1) {
	win->addChars(8);
	win->addChars('A');
	win->addChars('n');
	win->addChars('t');
	win->addChars('o');
	win->addChars('u');
	win->addChars('q');
	win->addChars(8);
	win->addChars('n');
	win->addChars((char)27);
	string s = in->GetString(out);
	EXPECT_EQ(s, "");
}


TEST_F(GUIEdgePairCoverage, GetString_TEST_2) {
	win->addChars('A');
	win->addChars('n');
	win->addChars('t');
	win->addChars('o');
	win->addChars('u');
	win->addChars('q');
	win->addChars(8);
	win->addChars((char)27);
	string s = in->GetString(out);
	EXPECT_EQ(s, "");
}



TEST_F(GUIEdgePairCoverage, GetString_TEST_3) {
	win->addChars('A');
	win->addChars('n');
	win->addChars('t');
	win->addChars(8);
	win->addChars(8);
	win->addChars(8);
	win->addChars(8);
	win->addChars((char)27);
	string s = in->GetString(out);
	EXPECT_EQ(s, "");
}


TEST_F(GUIEdgePairCoverage, GetString_TEST_4) {
	win->addChars('A');
	win->addChars('n');
	win->addChars('t');
	win->addChars(8);
	win->addChars(8);
	win->addChars(8);
	win->addChars(8);
	win->addChars('A');
	win->addChars('N');
	win->addChars(13);

	string s = in->GetString(out);
	EXPECT_EQ(s, "AN");
}


TEST_F(GUIEdgePairCoverage, GetValue_TEST_1) {
	double s;
	win->addChars(55); // 7
	win->addChars(8); 
	win->addChars(40); 
	win->addChars(55);
	win->addChars(13);

	s = in->GetValue(out);
	EXPECT_EQ(s, 7);
}


TEST_F(GUIEdgePairCoverage, GetValue_TEST_2) {
	double s;
	win->addChars(55); // 7
	win->addChars(8);
	win->addChars(40);
	win->addChars(55);
	win->addChars(13);
	s = in->GetValue(out);
	EXPECT_EQ(s, 7);
}


TEST_F(GUIEdgePairCoverage, GetValue_TEST_3) {
	double s;
	win->addChars(55); // 7
	win->addChars(8);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);


	win->addChars(55); // 7
	win->addChars(8);
	win->addChars(8);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(55); // 7
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(55); // 7
	win->addChars(46);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(55); // 7
	win->addChars(46);
	win->addChars(46);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(55); // 7
	win->addChars(45);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);


	win->addChars(45);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);

	win->addChars(40); // 7
	win->addChars(45);
	win->addChars(27);
	s = in->GetValue(out);
	EXPECT_EQ(s, 0);



}