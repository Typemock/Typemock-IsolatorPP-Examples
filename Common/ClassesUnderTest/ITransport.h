#pragma once
#include "GPSLocation.h"
#include <string>
#include <vector>
using std::vector;

class ITransport
{
public:
	virtual void SetTransport(char * name) = 0;
	virtual string GetTransport() = 0;
	virtual GPSLocation* GetLocation() = 0;
	// note: we are returing vector by value
	virtual vector<GPSLocation> GetAllStops() = 0;
	virtual void WriteAllStops(GPSLocation* locations) = 0;
};