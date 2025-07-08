#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"
#include "../ClassesUnderTest/ITransport.h"

namespace Examples {
	// Faking pure virtual objects is the same as faking any other object
	// Isolator++ will dynamically create a new object that implements the pure virtual methods as fakes methods
	class PureVirtualTests : public ::testing::Test
	{

	};

	/*****************************************
			Faking pure virtual methods
	******************************************/

	/*	a.Fake.Instance is effective with pure virtual method too
	*/
	TEST(PureVirtualTests, FakingAPureVirutualMethodAndChangingBehavior)
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
		ASSERT_EQ(0, person.GetTransportName().compare(bus));
	}

	/*	Faking pure virtual methods using a.Fake.Instance also helps in asserting calls on them.
		We can use any of Isolator's Verify APIs on the objects, and see if methods were called.
	*/
	TEST(PureVirtualTests, FakingAPureVirutualMethodAndAssertingMethodCalls)
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
}
