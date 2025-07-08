#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// Static calls can be faked explicitely on each method, or on all methods with the a.Fake.Statics macro. 
	// All faked static methods follow Recursive Fakes and sequncing rules, like faked instance methods
	TEST_CLASS(FakeStaticMethods)
	{
	public:

		/*****************************************
				Faking static methods
		******************************************/


		/*	It is useful to fake a factory method, and return a controlled object.
			In this example, we create a real object to return, and modify its behavior.
			We then use a.CallTo on the static factory method to return it.
		*/
		TEST_METHOD(ReturningAFakeObjectFromAFactoryMethod)
		{
			//Arrange
			auto a = Isolator();
			// Preparing the returned object
			Address myAddress;
			a.CallTo(myAddress.GetCity()).WillReturn("London");

			// Faking the static factory method
			a.CallTo(Address::GetSingleton()).WillReturn(&myAddress);

			//Act + Assert
			// Checking the resulting call
			Assert::AreEqual("London", Person::GetCityFromAddressFactory());
		}

		/*	Sometimes we need to fake all the static methods on a class.
			We use the a.Fake.Statics for that. All faked methods default
			behaviors follow the Recursive Fakes and sequencing rules.
			In this case, the default char* returned from GetCity is an empty string.
		*/
		TEST_METHOD(FakingAllStaticMethodsOnAType)
		{
			//Arrange
			auto a = Isolator();
			// Fake all methods
			a.Fake.Statics<Address>();

			//Act + Assert
			// All static Address methods are faked.
			Assert::AreEqual("", Person::GetCityFromAddressFactory());

			// In fact, because all static methods are faked, GetSingleton always returns a fake Address instance
			// The Address object itself is recursively faked, meaning any calls to it
			// will never cause crashes and will consistently return fake values.
			Assert::IsTrue(Address::GetSingleton() != NULL);
		}

		/*	In this example, we create clear a singleton and make sure that calling it calls
			a private static method CountReference()
		*/
		TEST_METHOD(IgnoringPrivateStaticMethod)
		{
			//Arrange
			auto a = Isolator();
			a.CallToPrivate(A::Global(Address::CountReference)).WillBeIgnored();

			//Act
			Address::ClearSingleton();

			//Assert
			a.CallToPrivate(A::Global(Address::CountReference)).VerifyWasCalled();
		}
	};
}