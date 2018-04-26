#include "Statement.h"

int Statement::static_ID = 0;

Statement::Statement()	
{ 
	ID = ++static_ID;
	Text = "";
	Selected = false;		
}



void Statement::Comment(string s)
{
	C = s;
}

string Statement::GetComment()
{
	if (C.size() == 0)
		return"\"\"";
	return C;
}


bool Statement::IsValid(string s) //as A variable
{
	if (isdigit(s[0]) || isspace(s[0]))
		return false;
	else if (ispunct(s[0]) && int(s[0]) != 95)
		return false;
	for (unsigned int i = 1; i<s.size(); i++)
	{
		if (isspace(s[i]) || (ispunct(s[i]) && int(s[i]) != 95))
		{
			return false;
			break;
		}
	}
	return true;
}



