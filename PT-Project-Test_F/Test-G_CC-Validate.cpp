#include"InputOutputAppManagerMocking.h"
#include"../PT-Project/Actions/Validate.h"
#include"../PT-Project/Statements/Statement.h"

TEST_F(ActionGACC , ValidateExecute) {
	Validate *a = new Validate(App);
	
	a->Execute();
}