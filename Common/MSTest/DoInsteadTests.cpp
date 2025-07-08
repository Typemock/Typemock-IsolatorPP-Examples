#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// WillDoInstead() calls the specified function instead of the original implementation
	TEST_CLASS(DoInstead)
	{
	public:

		/*******************************************
			Setting custom behavior with DoInstead
		********************************************/

		/*  Sometimes, we need to specify a different behavior based on the paramaters that
			are passed to the method at runtime. In this example, we're returning different
			values based on different method calls, when the faked method is static.
		*/
		TEST_METHOD(ReplacingStaticMethodCallBasedOnParameters)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			a.CallTo(Address::GetCapitalCityByCountry(A::Any())).WillDoInstead([](string country)
				{
					if (country.compare("Zombieland") == 0)
						return string("GhostTown");
					else
						return string("Elsewhere");
				});

			//Act
			string zombieCapital = person.GetCapitalCity("Zombieland");
			string otherCapital = person.GetCapitalCity("US");

			//Assert
			Assert::AreEqual(0, zombieCapital.compare("GhostTown"));
			Assert::AreEqual(0, otherCapital.compare("Elsewhere"));
		}

		/*  In this example, we're returning different
			values based on the order the methods get called, when the faked method is an instance member.
		*/
		TEST_METHOD(ReplacingInstanceMethodCallBasedOnOrder)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* address = a.Fake.Instance<Address>();

			a.CallTo(address->GetCityByCountry(A::Any())).WillDoInstead([](string country)
				{
					static int counter = 0;
					counter++;
					if (counter % 2 == 1)
						return string("OddCity");
					else
						return string("EvenCity");
				});

			//Act
			string firstCity = person.GetCityFromAddress(address, "");
			string secondCity = person.GetCityFromAddress(address, "");
			string thirdCity = person.GetCityFromAddress(address, "");
			string fourthCity = person.GetCityFromAddress(address, "");

			//Assert
			Assert::AreEqual(0, firstCity.compare("OddCity"));
			Assert::AreEqual(0, secondCity.compare("EvenCity"));
			Assert::AreEqual(0, thirdCity.compare("OddCity"));
			Assert::AreEqual(0, fourthCity.compare("EvenCity"));
		}




		/* The following example shows how to replace behavior of global functions. This is helpful in case of Windows API
		   or any C global (free) functions. In this case, we're replacing the behavior of the Windows API GetTickCount.
		*/
		TEST_METHOD(ChangeBehaviorToGlobalFunctionWithContext)
		{
			//Arrange
			auto a = Isolator();
			a.Testable.GlobalFunction(GetTickCount);

			a.CallTo(GetTickCount()).WillDoInstead([]()
				{
					return 10000;
				});

			//Act
			int result = GetTickCount();

			//Assert
			Assert::AreEqual(10000, result);
		}

	};
}