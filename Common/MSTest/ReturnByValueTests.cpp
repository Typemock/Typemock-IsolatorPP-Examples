#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"
#include "../ClassesUnderTest/GPSLocation.h"
#include "../ClassesUnderTest/ITransport.h"
#include "../ClassesUnderTest/Address.h"

namespace Examples {
	TEST_CLASS(ReturnByValueTests)
	{
	public:

		/*****************************************
				Return object by value
		******************************************/

		/*	In this test we show, how to fake a method to return an object with specified values.
			This is done automatically by Isolator++
		*/
		TEST_METHOD(ReturnLocations)
		{
			//Arrange
			auto a = Isolator();
			GPSLocation testLocation = GPSLocation(1, 1);
			Person realPerson = Person();

			vector<GPSLocation> testStopsVector;
			testStopsVector.push_back(GPSLocation(0, 0));
			testStopsVector.push_back(testLocation);
			testStopsVector.push_back(GPSLocation(2, 2));

			ITransport* fakeTransport = a.Fake.Instance<ITransport>();
			// GetAllStops returns vector<GPSLocation> by value 
			a.CallTo(fakeTransport->GetAllStops()).WillReturn(testStopsVector);

			//Act
			realPerson.SetTransport(fakeTransport);

			//Assert
			Assert::IsTrue(realPerson.TransportStopsAt(testLocation));
		}
	};
}