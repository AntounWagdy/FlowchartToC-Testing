#include"Action.h"
#include<map>

class Run_Action :public Action
{
private:
	map<string, double> variables;
public:
	Run_Action(ApplicationManager *a) :Action(a){}
	void ReadActionParameters(){}
	virtual void Execute();

};