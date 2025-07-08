#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	TEST_CLASS(ThrowException)
	{
	public:

		/*****************************************
				Simulating exceptions
		******************************************/

		TEST_METHOD(FakeStdException)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();

			exception problem;
			a.CallTo(fakeAddress->GetCountry()).WillThrow(&problem);

			//Act
			string result = person.GetAddressCountry(fakeAddress);

			//Assert
			Assert::IsTrue(result == "Error");
		}

	};

}