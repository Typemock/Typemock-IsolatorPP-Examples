#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	TEST_CLASS(ChainsBehavior)
	{
	public:

		/*****************************************
		Mocking a chain of methods
		******************************************/

		/*
		* This shows the basic rule for mocking a chain of methods of a faked object.
		* the behavior will be as follow:
		*  - Every method in the chain will be mocked
		*  - When the chain of method will be called the behavior will be as modified.
		*/
		TEST_METHOD(SettingChainedMethodsBehavior)
		{
			//Arrange
			auto a = Isolator();
			Person* fake = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

			a.CallTo(fake->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

			//Act + Assert
			Assert::AreEqual(10, fake->GetLocationLatitude(0));

		}

		/*
		* The same rules as above apply when all the instances of the same object
		  are faked using  a.Fake.All<> .
		*/

		TEST_METHOD(SettingChainedMethodsBehaviorFakeAll)
		{
			//Arrange
			auto a = Isolator();
			Person* fake = a.Fake.All<Person>(FakeOptions::CallOriginal);
			a.CallTo(fake->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

			Person* instance = new Person();

			//Act + Assert
			Assert::AreEqual(10, fake->GetLocationLatitude(0));
		}

		/*
		* The same rules as above apply when the methods in the chain belong to live object.
		*/

		TEST_METHOD(SettingChainedMethodsBehaviorLive)
		{
			//Arrange
			auto a = Isolator();
			Person* liveObj = new Person();

			a.CallTo(liveObj->GetAddressLocation(A::Any())->Latitude()).WillReturn(10);

			//Act + Assert
			Assert::AreEqual(10, liveObj->GetLocationLatitude(0));
		}

	};
}

