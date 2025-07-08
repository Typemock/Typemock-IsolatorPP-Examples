#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// when changing behavior to call original, the faked object will execute the original implementation of the method
	class CallOriginalBehavior : public ::testing::Test
	{
	};

	/*****************************************
		Calling original code on fake objects
	******************************************/

	/*
	 * GetZipCode will return the original -1 value, although the object faked.
	 */
	TEST(CallOriginalBehavior, ExecuteOriginalOnAFakeObject)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		a.CallTo(fakeAddress->GetZipCode()).WillCallOriginal();

		//Act + Assert
		ASSERT_EQ(-1, person.GetAddressZipCode(fakeAddress));
	}
}