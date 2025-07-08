#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// recursive fakes return 0 or equivalent for methods returning values, and recursive fakes for calls returning classes
	TEST_CLASS(CreateRecursiveFake)
	{
	public:

		/*****************************************
				Recursive fakes
		******************************************/

		/*
		 * Each fake instance is recursive fake by default, this means that
		 * every method returning an instance will return a fake object.
		 * In the example below Address->GetLocation(), being a fake, returns a faked instance of GPSLocation.
		 * That fake instance has fake methods, and their default behavior, returning int,  is to return 0.
		 */
		TEST_METHOD(ReturnFakeObject)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();

			//Act
			GPSLocation* result = person.GetAddressLocation(fakeAddress);

			//Assert
			Assert::AreEqual(0, result->Latitude());
			Assert::AreEqual(0, result->Longitude());
		}

	};
}