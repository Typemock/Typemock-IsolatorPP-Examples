#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class Ignore : public ::testing::Test
	{
	};

	/*****************************************
			Faking void calls
	******************************************/

	/*
	  WillBeIgnored can be used to ignore void methods on live object.
	*/
	TEST(Ignore, Ignore_MethodThatThrows_OnLiveObject)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address address;

		a.CallTo(address.SetCountry(A::Any())).WillBeIgnored();

		//Act
		// this would otherwise throw an exception
		person.SetAddressCountry(&address, "");
	}
}