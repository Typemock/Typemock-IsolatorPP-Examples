#include "stdafx.h"

#include "../ClassesUnderTest/GPSLocation.h"

namespace Examples {
	// using a InvokeOriginal allows you to call private methods within your test without changing your production code
	// we already saw this use in CallConstructorTests
	class InvokeMember : public ::testing::Test
	{

	};

	/*****************************************
		Calling private members on a live object
	******************************************/
	TEST(InvokeMember, CallStaticPrivateMethod)
	{
		//Arrange + Act
		auto a = Isolator();
		bool res = a.InvokeOriginal<bool>(A::Global(GPSLocation::IsGPSFound), 10, 10);

		//Assert
		ASSERT_EQ(true, res);
	}
}