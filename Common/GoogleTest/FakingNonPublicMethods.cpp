#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// use a.CallToPrivate to change behavior of non-public methods
	class FakingNonPublicMethods : public ::testing::Test
	{
	};


	/**************************************************************************************
		Setting behavior on non-public methods with a.Private.CallToInstance
	***************************************************************************************/

	/*	In this test, we fake the private IsValidName and check we get the
		exception thrown from the Person class.
	*/
	TEST(FakingNonPublicMethods, ChangingBehaviorOfPrivateMethod)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();
		a.CallToPrivate(A::Member(person, IsValidName)).WillReturn(false);

		//Act + Assert
		ASSERT_THROW(person->Save(""), exception);

		delete person;
	}

	/*	In this test, we fake the private overloaded method CanPing
	* use A::Type<type>() to specify the type we expect
	*/
	TEST(FakingNonPublicMethods, ChangingBehaviorOfPrivateOverloadedMethod)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();
		a.CallToPrivate(A::Member(person, CanPing), A::Type<bool>()).WillReturn(true);

		//Act + Assert
		ASSERT_TRUE(person->Ping());
		delete person;
	}


	/*	To assert a call waws made on a non-public use VerifyWasCalled.
	*/
	TEST(FakingNonPublicMethods, AssertingPrivateMethodCall)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();

		a.CallToPrivate(A::Member(person, IsValidName)).WillReturn(true);
		a.CallToPrivate(A::Member(person, SaveAll)).WillBeIgnored();

		//Act
		person->Save("");

		//Assert
		a.CallToPrivate(A::Member(person, SaveAll)).VerifyWasCalled();
		delete person;
	}

	/*	To assert a call on a overloaded non-public use A::Type<type>() with VerifyWasCalled.
	*/
	TEST(FakingNonPublicMethods, AssertingOverloadedPrivateMethodCall)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();
		a.CallToPrivate(A::Member(person, CanPing), A::Type<bool>()).WillReturn(true);

		//Act
		person->Ping();

		//Assert
		a.CallToPrivate(A::Member(person, CanPing), A::Type<bool>()).VerifyWasCalled();
		delete person;
	}

	/*	To assert a call on a overloaded with matching arguments using A::Matches
	*/
	TEST(FakingNonPublicMethods, AssertingOverloadedPrivateMethodCallWithMatchingArgumetns)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();
		a.CallToPrivate(A::Member(person, CanPing), A::Type<bool>()).WillBeIgnored();

		//Act
		person->Ping();

		//Assert
		a.CallToPrivate(A::Member(person, CanPing), A::Matches([](bool force) {return true == force; })).VerifyWasCalled();
		delete person;
	}


	/*	To set an out argument in a non-public method use A::SetOut with a.CallToPrivate.
	*/
	TEST(FakingNonPublicMethods, OutParametersInPrivateMethodCall)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();
		GPSLocation gpsLocationToReturn(9, 9);
		a.CallToPrivate(A::Member(person, GetAddress), A::SetOut(gpsLocationToReturn)).WillReturn(true);

		//Act
		GPSLocation gpsLocation(0, 0);
		person->PublicGetAddress(gpsLocation);

		//Assert
		ASSERT_EQ(gpsLocation.Latitude(), 9);
		delete person;
	}

	/*
	 * This test shows the usage of the conditional a.CallToPrivate  for a non public method called with an out arguments.
	 * If person->ChangeLastName(char** otherLastName) is called with "Johns" it will return false, otherwise - true
	*/
	TEST(FakingNonPublicMethods, OutParametersInPrivateMethodCallWithPredicate)
	{
		//Arrange
		auto a = Isolator();
		Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

		a.CallToPrivate(A::Member(person, ChangeLastName), A::SetOut("Smith").WhenIn(A::EqRef("Johns"))).WillReturn(false);

		//Act
		Person* otherPerson = new Person();
		otherPerson->lastName = "Johns";

		//Assert
		ASSERT_FALSE(person->GetMarried(otherPerson));
		ASSERT_STREQ(otherPerson->lastName, "Smith");
		delete otherPerson;
	}
}