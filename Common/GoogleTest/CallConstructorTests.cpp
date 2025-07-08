#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	/*
	* Isolator++ can enable you to call constructor on the fake object.
	* But only once per object lifetime
	*/
	class CallConstructorTests : public ::testing::Test
	{
	};

	/*****************************************
		Calling constructor on the fake objects
	******************************************/

	/*
	 * GetId() will return the original 1 value, although the object faked as the constructor was called and so id was set.
	 */
	TEST(CallConstructorTests, CallPublicConstructorWithArguments)
	{
		//Arrange
		auto a = Isolator();
		auto fakePerson = a.Fake.Instance<Person>();
		a.InvokeOriginal(A::Ctor(fakePerson), 1);

		a.CallTo(fakePerson->GetId()).WillCallOriginal();

		//Act + Assert
		ASSERT_EQ(1, fakePerson->GetId());
	}

	/*
	* Here we are calling a private constructor with an argument (equivalent to using new Person("Smith"))
	*/
	TEST(CallConstructorTests, CallPrivateConstructorWithArguments)
	{
		//Arrange
		auto a = Isolator();
		auto fakePerson = a.Fake.Instance<Person>();
		char* lastName = "Smith";
		a.InvokeOriginal(A::Ctor(fakePerson), lastName);

		//Act + Assert
		ASSERT_STREQ(lastName, fakePerson->lastName);
	}
}