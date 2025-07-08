#ifdef __linux__

#include "stdafx.h"

#else

#include <string>
#include <exception>
using namespace std;

#endif

#include "Address.h"

Address* Address::singleton = NULL;

void Address::SetCountry(string country)
{
	throw; // Not implemented yet
}
void Address::SetCountryChar(char * country)
{
	throw; // Not implemented yet
}

string Address::GetCountry()
{
	throw; // Not implemented yet
}

void Address::GetCountryByReference(string& country)
{
	throw; // Not implemented yet
}


int Address::GetZipCode()
{
	return -1;
}

char* Address::GetCity()
{
	throw; // Not implemented yet
}

GPSLocation* Address::GetLocation()
{
	throw; // Not implemented yet
}

Address* Address::GetSingleton()
{
	if (singleton == NULL)
		singleton = new Address();
	return singleton;
}

void Address::ClearSingleton()
{
	CountReference();
	if (singleton != NULL)
	{
		delete singleton;
		singleton = NULL;
	}
}

string Address::GetCapitalCityByCountry(string country)
{
	throw; // Not implemented yet
}

string Address::GetCityByCountry(string country)
{
	throw; // Not implemented yet
}

void Address::SetStreetName(char* streetName)
{
	throw; // Not implemented yet
}

void Address::GetStreetName(string* street)
{
	*street = "";
}
void Address::ChangeStreetName(string fromStreet, string toStreet)
{
	throw; // Not implemented yet // Not implemented yet
}

void Address::SetCountryOnSingleton(string country)
{
	Address::GetSingleton()->SetCountryInternal(country);
}

void Address::CallSetCountryInternal(string country)
{
	SetCountryInternal(country);
}

void Address::SetCountryInternal(std::string country)
{
	// do something here
}
void Address::CallOverloadedPrivate()
{
	OverloadedPrivate(1);
}

void Address::OverloadedPrivate(int i)
{
	// do something here
}
void Address::OverloadedPrivate(char *name)
{
	// do something here
}

void Address::CountReference()
{
	throw; // Not implemented yet
}

char* Address::GetZipCode(char *country, char *streetName)
{
	throw; // Not implemented yet
}


