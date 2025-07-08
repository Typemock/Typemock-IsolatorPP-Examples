#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"


namespace Examples {
	// Conditional arguments changes behavior according to arguments passed
	class Conditional : public ::testing::Test
	{

	};

	/*******************************************
		Setting custom behavior with Conditional Arguments
	********************************************/

	/*  Sometimes, we need to specify different behavior based on the parameters that
		are passed to a method at runtime. In this example, we're returning different
		values based on different method calls, on a static faked method.
	*/
	TEST(Conditional, ReplacingStaticMethodCallBasedOnParameters)
	{
		//Arrange
		auto a = Isolator();
		a.CallTo(Address::GetZipCode(A::Eq("US"), A::Eq("NY"))).WillReturn("12345");
		a.CallTo(Address::GetZipCode(A::Any(), A::Any())).WillReturn("00000");

		//Act
		auto result = Address::GetZipCode("UK", "LONDON");
		auto result2 = Address::GetZipCode("US", "NY");

		//Assert
		ASSERT_TRUE(strcmp(result, "00000") == 0);
		ASSERT_TRUE(strcmp(result2, "12345") == 0);

	}

	/*  In this example, we're returning different
		values using a condition. (A::Eq)
	*/
	
	TEST(Conditional, ChangingReturnValueOfStaticMethodCallBasedOnParameters)
	{
		//Arrange
		auto a = Isolator();
		a.CallTo(Address::GetZipCode(A::Eq("US"), A::Eq("NY"))).WillReturn("12345");
		a.CallTo(Address::GetZipCode(A::Any(), A::Any())).WillReturn("00000");
		//Act
		auto result = Address::GetZipCode("UK", "LONDON");
		auto result2 = Address::GetZipCode("US", "NY");
		//Assert
		ASSERT_TRUE(strcmp(result, "00000") == 0);
		ASSERT_TRUE(strcmp(result2, "12345") == 0);
	}

	/*  In this example, we're returning different
			values using a custom condition. (A::Matches)
	*/
	TEST(Conditional, ChangingReturnValueOfMethodCall_BasedOnParameters_UsingMatches)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* address = a.Fake.Instance<Address>();
		std::string city1("Unknown");
		std::string cityYork("York");

		a.CallTo(address->GetCityByCountry(
			A::Matches([](string& country) { return country == "US" || country == "UK"; })))
			.WillReturn(cityYork);

		a.CallTo(address->GetCityByCountry(A::Any())).WillReturn(city1);

		//Act
		string firstCity = person.GetCityFromAddress(address, "US");
		string secondCity = person.GetCityFromAddress(address, "SP");
		string thirdCity = person.GetCityFromAddress(address, "UK");
		string fourthCity = person.GetCityFromAddress(address, "CA");

		//Assert
		ASSERT_EQ(0, firstCity.compare("York"));
		ASSERT_EQ(0, secondCity.compare("Unknown"));
		ASSERT_EQ(0, thirdCity.compare("York"));
		ASSERT_EQ(0, fourthCity.compare("Unknown"));
	}

	/*  In this example, we're returning different
	values using a condition. (A::Eq) on string objects
	*/
	TEST(Conditional, CountingMethodCallBasedOnObjectParameters)
	{
		//Arrange
		auto a = Isolator();
		auto address = a.Fake.Instance<Address>();

		address->ChangeStreetName("US", "Brooklyn");

		//Act
		auto countCalls = a.CallTo(address->ChangeStreetName(A::Eq("US"), A::Eq("Brooklyn"))).GetTimesCalled();
		
		//Assert
		ASSERT_EQ(countCalls, 1);
	}



	/*  In this example, we're returning different values using a custom condition for a private method.
	*   Note: this is actually a public method - but Private methods can be used on public methods too
	*   So changeing a method to public wont require any changes in your tests
	*/
	TEST(Conditional, ReplacingPrivateMethodCallBasedOnParameters)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* address = a.Fake.Instance<Address>();
		std::string city1("Unknown");
		std::string cityYork("York");

		// public methods can be set as private methods too
		a.CallToPrivate(A::Member(address, GetCityByCountry),
			A::Matches([](string& country) { return country == "US" || country == "UK"; }))
			.WillReturn(&cityYork);

		a.CallToPrivate(A::Member(address, GetCityByCountry), A::Any()).WillReturn(&city1);

		//Act
		string firstCity = person.GetCityFromAddress(address, "US");
		string secondCity = person.GetCityFromAddress(address, "UK");
		string thirdCity = person.GetCityFromAddress(address, "CA");

		//Assert
		ASSERT_EQ(0, firstCity.compare("York"));
		ASSERT_EQ(0, secondCity.compare("York"));
		ASSERT_EQ(0, thirdCity.compare("Unknown"));
	}
}