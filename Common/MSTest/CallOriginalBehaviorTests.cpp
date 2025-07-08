#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// when changing behavior to call original, the faked object will execute the original implementation of the method
	TEST_CLASS(CallOriginalBehavior)
	{
	public:
		TEST_METHOD_CLEANUP(TearDown)
		{

		}


		/*****************************************
			Calling original code on fake objects
		******************************************/

		/*
		 * GetZipCode will return the original -1 value, although the object faked.
		 */
		TEST_METHOD(ExecuteOriginalOnAFakeObject)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();

			a.CallTo(fakeAddress->GetZipCode()).WillCallOriginal();

			//Act + Assert
			Assert::AreEqual(-1, person.GetAddressZipCode(fakeAddress));
		}
	};

}