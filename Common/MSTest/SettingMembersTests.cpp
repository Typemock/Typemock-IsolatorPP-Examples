#include "stdafx.h"

#include "../ClassesUnderTest/Person.h"

namespace Examples {
	// a.Variable.Set is used to change variables, usually on the tested object
	// a.Variable.Get is used query variables, usually on the tested object
	TEST_CLASS(SettingMembersTests)
	{
	public:
		/**************************************************************************************
		  Setting static and instance members with a.Variable.Set and a.Variable.Get
		***************************************************************************************/

		/*	In this test, we set the private m_id member and check
			The value was actually set.
		*/
		TEST_METHOD(SetPrivateInstanceMember)
		{
			//Arrange
			auto a = Isolator();
			Person* person = new Person();
			a.Variable.Set(A::Member(person, m_id), 10);

			//Act
			// now let's get that private member
			int memberValue = a.Variable.Get<int>(A::Member(person, m_id));

			//Assert
			Assert::AreEqual(10, memberValue);

			// we can also do this from public api but 
			Assert::AreEqual(10, person->GetId());

			delete person;
		}

		/*	In this test, we set the private static m_static member and check
			The value was actually set.
		*/
		TEST_METHOD(SetPrivateStaticMember)
		{
			//Arrange
			auto a = Isolator();
			a.Variable.Set(A::Global(Person::m_static), 1);

			//Act
			// now let's get that private member
			int memberValue = a.Variable.Get<int>(A::Global(Person::m_static));

			//Assert
			Assert::AreEqual(1, memberValue);
		}

		/*	In this test, we'll set and then get the private m_array member and check
			The value was actually set.
		*/
		TEST_METHOD(GetPrivateArray)
		{
			//Arrante
			auto a = Isolator();
			Person* person = new Person();
			int arr_set[5] = { 1, 2, 3, 4, 5 };

			a.Variable.Set(A::Member(person, m_array), &arr_set[0]);

			//Act
			//Now let's get that private member. 
			//Note, getting an array value will NOT make any copy but return a pointer to the array:
			int* arr_get = a.Variable.Get<int*>(A::Member(person, m_array));


			//Assert
			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(arr_set[i], arr_get[i]);
			}
		}
	};
}

