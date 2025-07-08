#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	TEST_CLASS(ArgumentTests)
	{
	public:
		/*****************************************
				Not specifying parameters
		******************************************/

		/*	This test is an example of how to setup a fake
			in which we dont care about the arguments.
			Use A::Any() to tell Isolator that the arguments are not important for the faking
			This works for all argument types pointers, by value or by refernece
			I can also be used for assertion methods where called
		*/
		TEST_METHOD(SetUpAFakeAndIgnoreForAnyAgumentsPassed)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address address;

			a.CallTo(address.SetStreetName(A::Any())).WillBeIgnored();

			//Act
			person.SetStreetNameOnAddress(&address, "HighStreet");

			//Assert
			string result = person.GetStreetNameFromAddress(&address);

			Assert::IsTrue(result.compare("") == 0);
		}

		/*****************************************
			Faking referenced parameters
	******************************************/

	/*	It is possible to simulate out arguments and those that are returned by reference using
		A::SetOut. You can use A::SetOut for every referenced argument
	*/
		TEST_METHOD(UsingSetOutToFakeAnOutArgument)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();
			string fakeStreet("HighStreet");

			a.CallTo(fakeAddress->GetStreetName(A::SetOut(string("HighStreet")))).WillBeIgnored();

			//Act
			string result = person.GetStreetNameFromAddress(fakeAddress);

			//Assert
			Assert::IsTrue(result.compare(string("HighStreet")) == 0);
		}


		/*****************************************
			Argument Validation
	******************************************/

	/*	It is possible to validate an arguments using A::Matches and using a custom lambda checker
	*/
		TEST_METHOD(ValidatingArgumentsInLambdaMethod)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* address = a.Fake.Instance<Address>();

			a.CallTo(address->GetCityByCountry(A::Matches([](string& country) { return country.length() < 5; })))
				.WillReturn(string(""));

			//Act
			auto result = person.GetCityFromAddress(address, "UK");

			//Assert
			Assert::IsTrue(result == string(""));

		}

		/*	It is possible to validate argument that need to be checked together using WillDoInstead
		*   This will also handle the return value, and we get to use all arguments
		*/
		TEST_METHOD(ValidatingMultipleArgumentsInLambdaMethod)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address address;

			bool result = false;

			//note: this is a live instance - we only fake this method of address
			a.CallTo(address.ChangeStreetName(A::Any(), A::Any())).WillDoInstead([&](string fromStreet, string toStreet)
				{
					// Check if the street names are the same
					result = (fromStreet.length() == toStreet.length());
				}
			);

			//Act + Assert
			person.ChangeStreetName(&address, "Oxford", "Camden");
			Assert::IsTrue(result);

			person.ChangeStreetName(&address, "Oxford", "Baker");
			Assert::IsFalse(result);
		}
	};
}




