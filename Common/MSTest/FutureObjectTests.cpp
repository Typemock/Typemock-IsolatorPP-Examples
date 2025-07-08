#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	/*	Future objects are object that are created, either on the stack or the heap, after the method under test
	was called. Isolator++ catches the constructor call and fakes it for one or any objects of the type specified.
	To do so use a.Fake.All. This method also returns a handle that allows to change behavior and assert method calls
	on the future object. This works on past objects too
	*/
	TEST_CLASS(FutureObjectTests)
	{
	public:

		/*****************************************
				Faking future objects
		******************************************/

		/*	a.Fake.All is effective with future (and past) objects, for examples singletons.
			These are usually created inside factory methods, like in this test.
		*/
		TEST_METHOD(FakingTheSingletonObjectAndChangingBehavior)
		{
			//Arrange
			auto a = Isolator();
			Address* fakeAddressHandle = a.Fake.All<Address>();

			a.CallTo(fakeAddressHandle->GetCity()).WillReturn("London");

			//Act + Assert
			// GetCityFromAddressFactory creates a new Address
			Assert::AreEqual("London", Person::GetCityFromAddressFactory());
		}

		/*	Faking future objects using a.Fake.All also helps in asserting calls on them.
			We can use any of Isolator's Verify APIs on the objects, and see if methods were called.
		*/
		TEST_METHOD(FakingTheSingletonObjectAndAssertingMethodCalls)
		{
			//Arrange
			auto a = Isolator();
			Address* fakeAddressHandle = a.Fake.All<Address>();

			//Act
			Person::GetCityFromAddressFactory();

			//Assert
			a.CallTo(fakeAddressHandle->GetCity()).VerifyWasCalled();
		}
	};
}