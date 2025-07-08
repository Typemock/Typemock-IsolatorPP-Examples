#pragma once
#include "Address.h"
#include "ITransport.h"
#include "GPSLocation.h"
using std::string;

class Person
{
public:
	Person() {};
	Person(int id);
	int GetId();
	char* GetDogName();
	char* GetName();
	char* lastName;
	void GetOlder(int* age);
	bool GetMarried(Person* otherPerson);
	void SetAddressCountry(Address* pAddress, std::string country);
	void SetAddressCountryChar(Address* pAddress, char* country);
	
	void	SetAddressCountryOnSingleton (Address* pAddress, std::string country);
	string GetAddressCountry (Address* pAddress);
	int		GetAddressZipCode (Address* pAddress);
	char*	GetAddressCity(Address* pAddress);
	GPSLocation* GetAddressLocation(Address* pAddress);
	int GetLocationLatitude(Address * pAddress);
	string  GetCityFromAddress(Address* pAddress, string country);
	static char* GetCityFromAddressFactory();
	string GetCapitalCity(string country);
	string GetStreetNameFromAddress(Address* pAddress);
	void SetStreetNameOnAddress(Address* pAddress, char* street);
    void SetAddressCountryInternal(Address* pAddress, string country);
	void CallAddressOverloadedPrivate(Address* pAddress);

	void SaveData();
	void Save(string filename);

	void SetTransport(ITransport* transport) {m_transport = transport;}
	string GetTransportName() { return m_transport->GetTransport();}
	bool Ping();
	bool PublicGetAddress(GPSLocation& location) { return GetAddress(location); }
	bool TransportStopsAt(GPSLocation& location);
	void WriteAllTransportStops(GPSLocation* locations);
	void ChangeStreetName(Address* pAddress, string fromStreet, string toStreet);

private:
    bool ChangeLastName (char** otherLastName);
	bool IsValidName(string filename);
	void SaveAll(string filename);
	bool CanPing();
	bool CanPing(bool force);
	bool GetAddress(GPSLocation& location);
	ITransport* m_transport;
	int m_array[5];
	int m_id;
	static int m_static;
	Person(char* lastName);
};
