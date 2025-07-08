#include "stdafx.h"

#include "../ClassesUnderTest/GPSLocation.h"

namespace Examples {
	// using a InvokeOriginal allows you to call private methods within your test without changing your production code
	// we already saw this use in CallConstructorTests
	TEST_CLASS(InvokeMember)
	{
	public:

		/*****************************************
			Calling private members on real objects
		******************************************/

		TEST_METHOD(CallStaticPrivateMethod)
		{
			//Arrange + Act
			auto a = Isolator();
			bool res = a.InvokeOriginal<bool>(A::Global(GPSLocation::IsGPSFound), 10, 10);

			//Assert
			Assert::AreEqual(true, res);
		}
	};
}