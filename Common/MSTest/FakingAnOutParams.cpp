#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"
#include "../ClassesUnderTest/GPSLocation.h"
#include "../ClassesUnderTest/ITransport.h"

namespace Examples {
	// This sections contains examples on faking and asserting methods with out parameters
	TEST_CLASS(FakingAnOutParams)
	{
	public:

		/*	To set an out argument in a public method use A::SetOut with a.CallTo().
			Note, we use A::SetOut to assign a value to an out parameter.
		*/
		TEST_METHOD(InPublicMethodCall)
		{
			//Arrange
			auto a = Isolator();
			Person* person = new Person();
			a.CallTo(person->GetOlder(A::SetOut(5)));

			//Act
			int age = 0;
			person->GetOlder(&age);

			//Assert
			Assert::AreEqual(age, 5);
			delete person;
		}

		/*	This test shows the usage of the conditional WhenIn for a method called with an in/out arguments.
		*   A::SetOut - sets the our value set
		*   WhenIn    - this is conditional - so the fake is set only the value in is as specified
			This test also shows A::EqRef usage - as we are comparing to a pointer/ref parameter.
		*/
		TEST_METHOD(InPublicMethodCallWithCondition)
		{
			//Arrange
			auto a = Isolator();
			Person* person = new Person();
			a.CallTo(person->GetOlder(A::SetOut(0).WhenIn(A::EqRef(5))));

			//Act
			int age = 5;
			person->GetOlder(&age);

			//Assert
			Assert::AreEqual(age, 0);
			delete person;
		}

		/*	To set an out argument in a non-public method use A::SetOut with a.CallToPrivate().
		*/
		TEST_METHOD(InPrivateMethodCall)
		{
			//Arrange
			auto a = Isolator();
			Person* person = new Person();
			GPSLocation gpsLocationToReturn(9, 9);
			a.CallToPrivate(A::Member(person, GetAddress), A::SetOut(&gpsLocationToReturn)).WillReturn(true);

			//Act
			GPSLocation gpsLocation(0, 0);
			person->PublicGetAddress(gpsLocation);

			//Assert
			Assert::AreEqual(gpsLocation.Latitude(), 9);
			delete person;
		}

		/*
		 * This test shows the usage of the conditional WhenIn for a non public method called with an in/out arguments.
		 * If person->ChangeLastName(char** otherLastName) is called with "Johns" it will return false and set otherLastName to "Smith"
		*/
		TEST_METHOD(InPrivateMethodCallWithCondition)
		{
			//Arrange
			auto a = Isolator();
			Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

			a.CallToPrivate(A::Member(person, ChangeLastName), A::SetOut("Smith").WhenIn(A::EqRef("Johns"))).WillReturn(false);

			//Act
			Person* otherPerson = new Person();
			otherPerson->lastName = "Johns";

			//Asserts
			Assert::AreEqual(false, person->GetMarried(otherPerson));
			Assert::AreEqual(otherPerson->lastName, "Smith");
			delete otherPerson;
		}

		/*
		 * This test shows the usage of the conditional A::MatchesRef for a non public method called with an out arguments (we dont assign the out argument).
		 * If person->ChangeLastName(char** otherLastName) is called with "Smith" it will return false. But the out argument won't change.
		 *
		 * Here we use A::MatchesRef for a custom condition
		*/
		TEST_METHOD(InPrivateMethodCallWithConditionWithoutAssigment)
		{
			//Arrange
			auto a = Isolator();
			Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

			a.CallToPrivate(A::Member(person, ChangeLastName), A::MatchesRef([](char** s) {return !strcmp(*s, "Smith"); }))
				.WillReturn(false);

			//Act
			Person* otherPerson = new Person();
			otherPerson->lastName = "Smith";

			//Asserty
			Assert::AreEqual(false, person->GetMarried(otherPerson));
			Assert::AreEqual(otherPerson->lastName, "Smith");
			delete otherPerson;

		}

		/*
		 * This test shows the usage of the A::SetOut for an out argument which needs additional size definition.
		 * To assign an out GPSLocation[] array we need to pass the allocation memory size of the array.
		*/
		TEST_METHOD(AnArrayInPublicMethodCall)
		{
			//Arrange
			auto a = Isolator();
			ITransport* fakeTransport = a.Fake.Instance<ITransport>();
			GPSLocation locations[] = { GPSLocation(1, 1), GPSLocation(1, 0), GPSLocation(0, 1) };
			size_t sizeOfArray = ARRAYSIZE(locations);
			size_t allocationSizeOfArray = sizeOfArray * sizeof(GPSLocation);

			a.CallTo(fakeTransport->WriteAllStops(A::SetOut(locations, allocationSizeOfArray))).WillBeIgnored();

			//Act
			Person* person = new Person();
			person->SetTransport(fakeTransport);

			GPSLocation personLocations[3];
			person->WriteAllTransportStops(personLocations);

			//Assert
			Assert::AreEqual(personLocations[0].Latitude(), 1);
			Assert::AreEqual(personLocations[0].Longitude(), 1);
		}
	};
}