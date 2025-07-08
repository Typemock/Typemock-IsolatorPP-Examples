#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class ChainsBehavior : public ::testing::Test
	{
	};


	/*****************************************
	Mocking a chain of methods
	******************************************/

	/*
	* This shows the basic rule for mocking a chain of methods of a faked object.
	* the behavior will be as follow:
	*  - Every method in the chain will be mocked
	*  - When the chain of method will be called the behavior will be as modified.
	*/
	TEST(ChainsBehavior, SettingChainedMethodsBehavior)
	{
		//Arrange
		auto a = Isolator();
		Person* fake = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

		a.CallTo(fake->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

		//Act + Assert
		ASSERT_EQ(10, fake->GetLocationLatitude(0));
	}


	/*
	* The same rules as above apply when all the instances of the same object
	  are faked using  a.Fake.All<> .
	*/

	TEST(ChainsBehavior, SettingChainedMethodsBehaviorFakeAll)
	{
		//Arrange
		auto a = Isolator();
		Person* fake = a.Fake.All<Person>(FakeOptions::CallOriginal);
		a.CallTo(fake->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

		Person* instance = new Person();

		//Act + Assert
		ASSERT_EQ(10, fake->GetLocationLatitude(0));
	}

	/*
	* The same rules as above apply when the methods in the chain belong to live object.
	*/

	TEST(ChainsBehavior, SettingChainedMethodsBehaviorLive)
	{
		//Arrange
		auto a = Isolator();
		Person* liveObj = new Person();

		a.CallTo(liveObj->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

		//Act + Assert
		ASSERT_EQ(10, liveObj->GetLocationLatitude(0));
	}
}