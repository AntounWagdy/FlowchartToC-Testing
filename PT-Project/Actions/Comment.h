#include "Action.h"
#include"../Statements/Statement.h"

class Comment: public Action 
{
private:
	Statement*S;
	string C; // Comment
public:
	FRIEND_TEST(ActionEdgeCoverage, Comment_ReadParams);
	Comment(ApplicationManager*AppManager);
	void Execute();
	virtual void ReadActionParameters();

};