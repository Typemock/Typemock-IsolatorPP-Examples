#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"
#include "../ClassesUnderTest/ITransport.h"


namespace Examples {
	/*	Faking pure virtual objects is just as easy as faking any other type.
	use the a.Fake.Instance macro, this will create an object that implements all the pure virtual methods.
	*/
	TEST_CLASS(PureVirtualTests)
	{
	public:

		/*****************************************
				Faking pure virtual methods
		******************************************/

		/*	a.Fake.Instance is effective with pure virtual method too
		*/
		TEST_METHOD(FakingAPureVirutualMethodAndChangingBehavior)
		{
			//Arrange
			auto a = Isolator();
			ITransport* fakeTransport = a.Fake.Instance<ITransport>();

			string bus("Bus");
			a.CallTo(fakeTransport->GetTransport()).WillReturn(&bus);

			Person person;

			//Act
			person.SetTransport(fakeTransport);

			//Assert
			Assert::AreEqual(bus, person.GetTransportName());
		}

		/*	Faking pure virtual methods using a.Fake.Instance also helps in asserting calls on them.
			We can use any of Isolator's Verify APIs on the objects, and see if methods were called.
		*/
		TEST_METHOD(FakingAPureVirutualMethodAndAssertingMethodCalls)
		{
			//Arranges
			auto a = Isolator();
			ITransport* fakeTransport = a.Fake.Instance<ITransport>();

			a.CallTo(fakeTransport->GetTransport()).WillReturn(string("Bus"));

			Person person;

			//Act
			person.SetTransport(fakeTransport);

			auto result = person.GetTransportName();

			//Assert
			a.CallTo(fakeTransport->GetTransport()).VerifyWasCalled();
		}
	};
}