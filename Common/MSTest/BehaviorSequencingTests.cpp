#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	TEST_CLASS(BehaviorSequencing)
	{
	public:

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
		TEST_METHOD(LastSequencedValueRemains)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();

			a.CallTo(fakeAddress->GetZipCode()).WillReturn(90210);
			a.CallTo(fakeAddress->GetZipCode()).WillReturn(93108);
			a.CallTo(fakeAddress->GetZipCode()).WillReturn(91008);

			//Act + Assert
			Assert::AreEqual(90210, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(93108, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(91008, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(91008, person.GetAddressZipCode(fakeAddress));
		}

		/*
		 * The same sequencing rules as above apply to faking different
		 * behaviors on a method
		 */
		TEST_METHOD(MixingBehaviors)
		{
			//Arrange
			auto a = Isolator();
			Person person;
			Address* fakeAddress = a.Fake.Instance<Address>();

			a.CallTo(fakeAddress->GetZipCode()).WillCallOriginal();
			a.CallTo(fakeAddress->GetZipCode()).WillReturn(90210);
			a.CallTo(fakeAddress->GetZipCode()).WillReturnFake();


			//Act + Assert
			Assert::AreEqual(-1, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(90210, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(0, person.GetAddressZipCode(fakeAddress));
			Assert::AreEqual(0, person.GetAddressZipCode(fakeAddress));

		}

	};
}