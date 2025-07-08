#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"


namespace Examples {
	class BehaviorSequencing : public ::testing::Test
	{
	};

	/*****************************************
			Setting behaviors in sequence
	******************************************/

	/*
	 * This shows the basic rule for sequenced behavior.
	 * When set the second time the behavior of a method
	 * the behavior will be as follow:
	 *  - Every call will return the next value that was specified in the order of a.CallTo statements
	 *  - The last statement of a.CallTo will define the default for each subsequent call .
	 */
	TEST(BehaviorSequencing, LastSequencedValueRemains)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		a.CallTo(fakeAddress->GetZipCode()).WillReturn(90210);
		a.CallTo(fakeAddress->GetZipCode()).WillReturn(93108);
		a.CallTo(fakeAddress->GetZipCode()).WillReturn(91008);

		//Act + Assert
		ASSERT_EQ(90210, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(93108, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(91008, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(91008, person.GetAddressZipCode(fakeAddress));
	}

	/*
	 * The same sequencing rules as above apply to faking different
	 * behaviors on a method
	 */
	TEST(BehaviorSequencing, MixingBehaviors)
	{
		//Arrange
		auto a = Isolator();
		Person person;
		Address* fakeAddress = a.Fake.Instance<Address>();

		a.CallTo(fakeAddress->GetZipCode()).WillCallOriginal();
		a.CallTo(fakeAddress->GetZipCode()).WillReturn(90210);
		a.CallTo(fakeAddress->GetZipCode()).WillReturnFake();


		//Act + Assert
		ASSERT_EQ(-1, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(90210, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(0, person.GetAddressZipCode(fakeAddress));
		ASSERT_EQ(0, person.GetAddressZipCode(fakeAddress));

	}
}