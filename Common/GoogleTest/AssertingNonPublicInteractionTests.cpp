#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	class AssertingNonPublicInteraction : public ::testing::Test
	{
	};

	/*****************************************
			Method Interaction Assertion
	******************************************/

	/*
	 * This test shows the usage of VerifyWasNotCalled for a method called on a faked dependency.
	 * If pAddress->SetCountryInternal was not called the test will fail and Isolator++ will throw an IsolatorException
	 *
	 * We use A::Member to define the private member
	*/
	TEST(AssertingNonPublicInteraction, AssertCallWasMadeOnDependency)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* pAddress = a.Fake.Instance<Address>(FakeOptions::CallOriginal);

		//Act
		person.SetAddressCountryInternal(pAddress, "US");

		//Assert
		a.CallToPrivate(A::Member(pAddress, SetCountryInternal)).VerifyWasCalled();
	}


	/*
	 * This test shows the usage of VerifyWasNotCalled for a method called on a faked dependency.
	 * If Address::CountReference was called, the test will fail and Isolator++ will throw an IsolatorException
	 *
	 * We use A::Global to define the private static method
	*/
	TEST(AssertingNonPublicInteraction, AssertCallWasNotMadeOnStaticDependency)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* pAddress = a.Fake.Instance<Address>();

		a.Fake.Statics<Address>();

		//Act
		person.SetAddressCountry(pAddress, "US");

		//Assert
		// this is how we test static methods
		a.CallToPrivate(A::Global(Address::CountReference)).VerifyWasNotCalled();
	}

	/*
	 * This test shows the usage of GetTimesCalled
	 * Isolator++ keeps track of the called methods in the test
	 * Using GetTimesCalled we can verify how many times a method was called in the test.
	*/
	TEST(AssertingNonPublicInteraction, TimesCalledMethodOnDependency)
	{
		//Arrange
		auto a = Isolator();
		a.Fake.Statics<Address>();
		Person person;
		Address* pAddress = a.Fake.Instance<Address>();

		//Act
		person.SetAddressCountry(pAddress, "US");
		person.SetAddressCountry(pAddress, "UK");
		person.SetAddressCountry(pAddress, "Germany");

		int timesCalled = a.CallToPrivate(A::Member(pAddress, SetCountry)).GetTimesCalled(); // we can use the private api on a public method

		//Assert
		ASSERT_EQ(3, timesCalled);
	}

	/*
	 * This test shows the usage of VerifyWasNotCalled for an overloaded method called on a faked dependency.
	 * If pAddress->OverloadedPrivate(int) was not called or
	 * pAddress->OverloadedPrivate(char &) was called the test will fail and Isolator++ will throw an IsolatorException
	*/
	TEST(AssertingNonPublicInteraction, AssertOverloadCallWasMadeOnDependency)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* pAddress = a.Fake.Instance<Address>(FakeOptions::CallOriginal);

		//Act
		person.CallAddressOverloadedPrivate(pAddress);

		//Assert
		a.CallToPrivate(A::Member(pAddress, OverloadedPrivate), A::Type<int>()).VerifyWasCalled();
		a.CallToPrivate(A::Member(pAddress, OverloadedPrivate), A::Type<char*>()).VerifyWasNotCalled();
	}

	/*
	 * This test shows the usage of VerifyNotCalled for a non public method called with a custom checker A::Matches to test the Argument.
	 * If person->SaveAll(string) is not be called with "foo" as an argument the test will fail and Isolator++ will throw an IsolatorException
	 * Here we are using a custom checker with A::Matches
	*/
	TEST(AssertingNonPublicInteraction, AssertPrivateWithCondition)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();

		a.CallToPrivate(A::Member(person, IsValidName)).WillReturn(true);
		a.CallToPrivate(A::Member(person, SaveAll)).WillBeIgnored();

		//Act
		person->Save("foo");

		//Assert
		a.CallToPrivate(A::Member(person, SaveAll), A::Matches([](std::string& val)
			{ return val == "foo"; }))
			.VerifyWasCalled();
	}

	/*
	 * This test shows the usage of VerifyWasNotCalled for a non public method called with a specific custom checked arguments.
	 * If person->SaveAll(string) was called with "foo" as an argument the test will fail and Isolator++ will throw an IsolatorException
	*/
	TEST(AssertingNonPublicInteraction, AssertPrivateWithConditionWasNotCalled)
	{
		//Arrange
		auto a = Isolator();
		Person* person = new Person();

		a.CallToPrivate(A::Member(person, IsValidName)).WillReturn(true);
		a.CallToPrivate(A::Member(person, SaveAll)).WillBeIgnored();

		auto lambda = [](std::string& val)
			{
				return val == "foo";
			};

		//Act
		person->Save("bar");

		//Assert
		a.CallToPrivate(A::Member(person, SaveAll), A::Matches(lambda)).VerifyWasNotCalled();
	}

	/*
	 * This test shows the usage of VerifyWasCalled for a non public method called with in/out arguments.
	 * If person->ChangeLastName(char** otherLastName) is not be called with "Smith" as an argument the test will fail and Isolator++ will throw an IsolatorException
	*/
	TEST(AssertingNonPublicInteraction, AssertPrivateWithConditionWasCalledWithRet)
	{
		//Arrange
		auto a = Isolator();
		Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal); // this create a real object - so we can track it for Verify

		Person* anotherPerson = new Person();
		anotherPerson->lastName = "Smith";

		//Act
		person->GetMarried(anotherPerson);

		//Assert
		a.CallToPrivate(A::Member(person, ChangeLastName), A::Eq("Smith")).VerifyWasCalled(); // was called with "Smith"
	}

	/*
	 * This test shows the usage of VerifyWasNotCalled for a non public method called with in/out arguments.
	 * Only if the method is called with a "Brown" VerifyWasCalled will throw an exception.
	*/
	TEST(AssertingNonPublicInteraction, AssertPrivateWithConditionWasNotCalledWithRet)
	{
		//Arrange
		auto a = Isolator();
		Person* person = a.Fake.Instance<Person>(FakeOptions::CallOriginal); // this create a real object - we can track it for assert

		Person* anotherPerson = new Person();
		anotherPerson->lastName = "Smith";

		//Act
		person->GetMarried(anotherPerson);

		//Assert
		a.CallToPrivate(A::Member(person, ChangeLastName), A::Eq("Brown")).VerifyWasNotCalled(); // was not called with "Brown"
	}
}