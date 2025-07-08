#ifdef __linux__

#include "stdafx.h"

#else

#include <string>
#include <exception>
using namespace std;

#endif

#include "Person.h"

int Person::m_static = 0;

Person::Person(int id)
{
	m_id = id;
}

Person::Person(char* newLastName)
{
	lastName = newLastName;
}

int Person::GetId()
{
	return m_id;
}

void Person::GetOlder(int* age)
{
	*age++;
}

bool Person::GetMarried(Person* otherPerson)
{	
	return ChangeLastName(&otherPerson->lastName);	
}

bool Person::ChangeLastName (char** otherLastName)
{
	*otherLastName = lastName;
	return true;
}

void Person::SetAddressCountry (Address* pAddress, string country)
{
	pAddress->SetCountry(country);
}

void Person::SetAddressCountryChar(Address* pAddress, char * country)
{
	pAddress->SetCountryChar(country);
}

void Person::SetAddressCountryOnSingleton (Address* pAddress, string country)
{
	pAddress->SetCountryOnSingleton(country);
}

void Person::SetAddressCountryInternal(Address* pAddress, string country)
{
	pAddress->CallSetCountryInternal(country);
}

void Person::CallAddressOverloadedPrivate(Address* pAddress)
{
	pAddress->CallOverloadedPrivate();
}

std::string Person::GetAddressCountry (Address* pAddress)
{
	try
	{
		return pAddress->GetCountry();
	}
	catch(exception*)
	{
		return "Error";
	}
}

int Person::GetAddressZipCode (Address* pAddress)
{
	return pAddress->GetZipCode();
}

char* Person::GetAddressCity(Address* pAddress)
{
	return pAddress->GetCity();
}

GPSLocation* Person::GetAddressLocation(Address* pAddress)
{
	return pAddress->GetLocation();
}

int Person::GetLocationLatitude(Address* pAddress)
{
	return this->GetAddressLocation(pAddress)->Latitude();
}

char* Person::GetCityFromAddressFactory()
{
	Address* pAddress =  Address::GetSingleton();
	char* city = pAddress->GetCity();

	return city;
}

string Person::GetCapitalCity(string country)
{
	return Address::GetCapitalCityByCountry(country);
}

string Person::GetCityFromAddress(Address* pAddress, string country)
{
	return pAddress->GetCityByCountry(country);
}

string Person::GetStreetNameFromAddress(Address* pAddress)
{
	string street;
	pAddress->GetStreetName(&street);

	return street;
}

void Person::ChangeStreetName(Address* pAddress, string fromStreet, string toStreet)
{
	pAddress->ChangeStreetName(fromStreet, toStreet);
}

void Person::SetStreetNameOnAddress(Address* pAddress, char* street)
{
	pAddress->SetStreetName(street);
}

void Person::SaveData()
{
	char* text = (char*)"address";

	FILE *fp = fopen("personfile.txt", "wb");

	if (fp != nullptr)
	{
		fwrite(text,sizeof(char), sizeof(text), fp);
		fclose(fp);
	}
}

void Person::Save(string filename)
{
	if (!IsValidName(filename))
#ifdef __linux__
        throw exception();
#else
        throw exception("Invalid Name");
#endif
	SaveAll(filename);
}

bool Person::IsValidName(string filename)
{
	throw; // Not implemented yet
}

void Person::SaveAll(string filename)
{
	throw; // Not implemented yet
}

char* Person::GetName()
{
	throw; // Not implemented yet
}

char* Person::GetDogName()
{
	char* name = GetName();
	if (strcmp(name, "Tommy") == 0)
		return (char*)"Lassie";
	else
		return (char*)"Rex";
}

bool Person::Ping()
{
	return CanPing(true);
}

bool Person::CanPing()
{
	throw; // Not implemented yet
}

bool Person::CanPing(bool force)
{
	throw; // Not implemented yet
}
bool Person::GetAddress(GPSLocation& location)
{
	return false;
}

bool Person::TransportStopsAt(GPSLocation& location)
{
	bool found = false;
	vector<GPSLocation> allStops = m_transport->GetAllStops();
	vector<GPSLocation>::iterator it;  
	for(it = allStops.begin() ; it < allStops.end(); it++) 
	{
		if (it->Latitude() == location.Latitude() && it->Longitude() == location.Longitude())
		{
			found = true;
			break;
		}
	}

	return found;
}

void Person::WriteAllTransportStops(GPSLocation* locations)
{
	m_transport->WriteAllStops(locations);
}
