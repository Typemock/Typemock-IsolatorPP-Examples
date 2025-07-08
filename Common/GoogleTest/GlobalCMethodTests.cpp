#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class GlobalCMethods : public ::testing::Test
	{
	};

	/*****************************************
			Faking global methods
	******************************************/

	/*	Faking and asserting on global methods requires using a.CallTo to set its behavior.
		In cases multiple implementations of the method is linked into the application,
		We will need to use a.Testable.GlobalFunction

		Using a.Testable.GlobalFunction will fake all implementations of the method. The default behavior of a method
		declared with a.Testable.GlobalFunction is to call original. In this example
		We require fopen to return NULL, so we use a.CallTo to do that. Since we don't care about
		what fclose returns, we don't define a behavior.
	*/
	TEST(GlobalCMethods, FakingReturnValueOnGlobalMethod)
	{
		//Arrange
		auto a = Isolator();


		a.Testable.GlobalFunction(fopen);
		a.Testable.GlobalFunction(fclose);

		a.CallTo(fopen(A::Any(), A::Any())).WillReturn(0);
		a.CallTo(fclose(A::Any())).WillReturnFake();

		//Act
		Person person;
		person.SaveData();

		//Assert
		a.CallTo(fclose(A::Any())).VerifyWasNotCalled();
	}

	/*	For the other case, we simulate all global calls: fopen, fwrite and fclose.
		This time, we want fopen to return a non-NULL value. Since the default of a.Testable.GlobalFunction returns
		a recursive fake, our code (SaveData) will call the fclose as it goes into the if-clause.
	*/
	TEST(GlobalCMethods, FakingMethodAndUsingRecursiveFake)
	{
		//Arrange
		auto a = Isolator();
		Person person;

		a.Testable.GlobalFunction(fopen);
		a.Testable.GlobalFunction(fwrite);
		a.Testable.GlobalFunction(fclose);

		a.CallTo(fopen(A::Any(), A::Any())).WillReturnFake();
		a.CallTo(fclose(A::Any())).WillReturnFake();
		a.CallTo(fwrite(A::Any(), A::Any(), A::Any(), A::Any())).WillReturnFake();

		//Act
		person.SaveData();

		//Assert
		a.CallTo(fclose(A::Any())).VerifyWasCalled();
	}
}
