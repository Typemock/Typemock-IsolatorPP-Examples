#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// Live objects are partially real, partially faked. 
	// We create them as regular objects, and then use a.CallTo to change part of their behavior.
	TEST_CLASS(LiveObjectTests)
	{
	public:

		/*****************************************
				Working with Live Objects
		******************************************/

		/*	We usually work with live objects when they are under test. In this case, we fake an internal call
			to a public method. To change that behavior we use the a.CallTo on the object we just created.
		*/
		TEST_METHOD(FakingAPublicMethod)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			a.CallTo(person.GetName()).WillReturn("Tommy");

			//Act + Assert
			Assert::AreEqual("Lassie", person.GetDogName());

		}

		/*	Asserting a method call by using VerifyWasCalled . However, in order for that to work, we
			need to use at least once an Isolator API on that object before. This can be a.CallTo or anything similar,
			and doesn't have to be for the same method.
			In this example, we both change the behavior of the public method, and assert it was called.
		*/
		TEST_METHOD(AssertingACall)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			a.CallTo(person.GetName()).WillReturn("Jerry");

			//Act + Assert
			Assert::AreEqual("Rex", person.GetDogName());
			a.CallTo(person.GetName()).VerifyWasCalled();
		}


		/*	Sometimes, we need to change behavior on a non-public method of the tested object.
			We use the a.CallToPrivate for that.
		*/
		TEST_METHOD(FakingAPrivateMethod)
		{
			//Arrange
			auto a = Isolator();
			Person* person = new Person();
			a.CallToPrivate(A::Member(person, IsValidName)).WillReturn(false);

			//Act + Assert
			Assert::ExpectException<exception>([person] {person->Save(""); });
			delete person;
		}
	};
}