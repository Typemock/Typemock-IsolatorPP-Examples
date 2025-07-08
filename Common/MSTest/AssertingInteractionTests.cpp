#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	TEST_CLASS(AssertingInteraction)
	{
	public:
		/*****************************************
				Method Interaction Assertion
		******************************************/

		/*
		 * This test shows the usage of VerifyWasCalled for a method called on a faked dependency.
		 * If pAddress->SetCountry will not be called the test will fail and Isolator++ will throw an IsolatorException
		*/
		TEST_METHOD(AssertCallWasMadeOnDependency)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* pAddress = a.Fake.Instance<Address>();

			//Act
			person.SetAddressCountry(pAddress, "US");

			//Assert
			a.CallTo(pAddress->SetCountry(A::Any())).VerifyWasCalled();
		}


		/*
		 * This test shows the usage of VerifyWasCalled for a method called with a specific argument on a faked dependency.
		 * If pAddress->SetCountry will not be called with "UK" the test will fail and Isolator++ will throw an IsolatorException
		*/
		TEST_METHOD(AssertCallWasMadeWithSpecificArgumentsOnDependency)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* pAddress = a.Fake.Instance<Address>();

			//Act
			person.SetAddressCountryChar(pAddress, "UK");

			//Assert
			a.CallTo(pAddress->SetCountryChar(A::Eq("UK"))).VerifyWasCalled();
		}

		/*
		 * This test shows the usage of VerifyWasCalled for a method called using A::Matches custom lambda checker
		 * If pAddress->SetCountry will not be called with a string with length longer than 3 the test will fail and Isolator++ will throw an IsolatorException
		*/
		TEST_METHOD(AssertCallWasMadeWithSpecificArgumentsOnDependencyWithPredicates)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* pAddress = a.Fake.Instance<Address>();

			//Act
			person.SetAddressCountry(pAddress, "UK");

			//Assert
			a.CallTo(pAddress->SetCountry(A::Matches([](string& str) { return str.length() <= 3; }))).
				VerifyWasCalled();
		}

		/*
		 * This test shows the usage of VerifyWasNotCalled for a method called on a faked dependency.
		 * If pAddress->SetCountry is called, the test will fail and Isolator++ will throw an IsolatorException
		*/
		TEST_METHOD(AssertCallWasNotMadeOnDependency)
		{
			//Arrange
			auto a = Isolator();
			Address* pAddress = a.Fake.Instance<Address>();

			//Assert
			a.CallTo(pAddress->SetCountry(A::Any())).VerifyWasNotCalled();
		}

		/*
		 * This test shows the usage of GetTimesCalled
		 * Isolator++ keeps track of the called methods in the test
		 * Using GetTimesCalled we verify  how many times a method got called in the test.
		*/
		TEST_METHOD(TimesCalledMethodOnDependency)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* pAddress = a.Fake.Instance<Address>();

			//Act
			person.SetAddressCountry(pAddress, "US");
			person.SetAddressCountry(pAddress, "UK");
			person.SetAddressCountry(pAddress, "Germany");

			int timesCalled = a.CallTo(pAddress->SetCountry(A::Any())).GetTimesCalled();

			//Assert
			Assert::AreEqual(3, timesCalled);
		}

		/*
		 * This test shows how to handle methods with out/by-ref value type arguments
		 * Note, the GetOlder method has an int* argument we can't just write A::Eq(2)
		 * Using A::EqRef there is no need to define another variable for assertion.
		 * Using VerifyWasNotCalled we verify that the method wasn't called in the test with specific arguments.
		*/
		TEST_METHOD(WasNotCalledWithConcreteOutParam)
		{
			//Arrange
			auto a = Isolator();
			Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal); // Can also use FakeOptions::Lean, but methods will not be tracked and asserting them will require using a.CallTo on the method

			//Act
			int age = 0;
			person->GetOlder(&age);
			person->GetOlder(&age);

			//Assert
			a.CallTo(person->GetOlder(A::EqRef(2))).VerifyWasNotCalled();
		}

		/*
		 * This test shows how to handle methods with out/by-ref value type arguments
		 * Note, as GetOlder method has int* argument we can't just write A::Eq(0)
		 * Using A::EqRef there is no need to define another variable for assertion.
		 * Using VerifyWasCalled we verify that the method was called in the test with specific arguments.
		*/
		TEST_METHOD(WasCalledWithConcreteOutParam)
		{
			//Arrange
			auto a = Isolator();
			Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal);

			//Act
			int age = 0;
			person->GetOlder(&age);
			person->GetOlder(&age);

			//Assert
			a.CallTo(person->GetOlder(A::EqRef(0))).VerifyWasCalled();
		}
	};
}



