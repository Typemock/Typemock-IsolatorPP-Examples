#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class ChangeReturnValue : public ::testing::Test
	{
	};

	/*****************************************
			Returning fake values
	******************************************/

	/*
	 * GetZipCode will return the specified value instead of executing the original method logic
	 */
	TEST(ChangeReturnValue, ReturnPrimitive)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		a.CallTo(fakeAddress->GetZipCode()).WillReturn(100);

		//Act + Assert
		ASSERT_EQ(100, person.GetAddressZipCode(fakeAddress));
	}

	/*
	 * GetCity will return the specified string instead of executing the original method logic
	 */
	TEST(ChangeReturnValue, ReturnString)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		a.CallTo(fakeAddress->GetCity()).WillReturn("New York");

		//Act + Assert
		ASSERT_STREQ("New York", person.GetAddressCity(fakeAddress));
	}

	/*
	 * GetLocation will return the specified object instead of executing the original method logic
	 * The default return of the faked GetLocation is a fake GPSLocation object
	 */
	TEST(ChangeReturnValue, ReturnObject)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		GPSLocation newyork(41, 74);

		a.CallTo(fakeAddress->GetLocation()).WillReturn(newyork);

		//Act
		GPSLocation* result = person.GetAddressLocation(fakeAddress);

		//Assert
		ASSERT_EQ(74, result->Longitude());
		ASSERT_EQ(41, result->Latitude());
	}
}