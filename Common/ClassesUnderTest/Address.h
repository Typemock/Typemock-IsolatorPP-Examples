#pragma once
#include "GPSLocation.h"
using std::string;

class Address
{
private:
	static Address* singleton;

public:
	static Address* GetSingleton();
	static void ClearSingleton();
	static string GetCapitalCityByCountry(string country);

	Address() { }
	Address(GPSLocation* location) { m_GPSLocation = location;}
	void SetCountry(string country);
	void SetCountryChar(char* country);
	string GetCountry();
	void GetCountryByReference(string& country);    
	int GetZipCode();
	char* GetCity();
	GPSLocation* GetLocation();
	string GetCityByCountry(string country);
	void GetStreetName(string* street);
	void SetStreetName(char* streetName);
	void ChangeStreetName(string fromStreet, string toStreet);
	void SetCountryOnSingleton(string country);
    void CallSetCountryInternal(string country);
    void CallOverloadedPrivate();

	static char *GetZipCode(char *country, char *streetName);
private:
	void SetCountryInternal(std::string country);
	static void CountReference();
	void OverloadedPrivate(int i);
	void OverloadedPrivate(char *name);
	GPSLocation* m_GPSLocation;
};