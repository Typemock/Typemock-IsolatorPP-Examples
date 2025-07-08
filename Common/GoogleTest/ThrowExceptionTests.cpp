#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class ThrowException : public ::testing::Test
	{

	};

	/*****************************************
			Simulating exceptions
	******************************************/

	TEST(ThrowException, FakeStdException)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();
#ifdef __linux__
		exception problem;
#else
		exception problem("Something has definitely gone wrong!");
#endif
		a.CallTo(fakeAddress->GetCountry()).WillThrow(&problem);

		//Act
		string result = person.GetAddressCountry(fakeAddress);

		//Assert
		ASSERT_TRUE(result == string("Error"));

	}
}