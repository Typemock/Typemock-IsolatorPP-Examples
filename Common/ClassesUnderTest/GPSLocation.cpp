#ifdef __linux__

#include "stdafx.h"

#else

#include <string>
#include <exception>
using namespace std;

#endif

#include "GPSLocation.h"

GPSLocation::GPSLocation(int lat, int lon)
{
	if (IsGPSFound(lat,lon))
	{
		// do something
	}
	longitude = lon;
	latitude = lat;
}

GPSLocation::GPSLocation()
{
	longitude = 0;
	latitude = 0;
}

int GPSLocation::Longitude()
{
	return longitude;
}

int GPSLocation::Latitude()
{
	return latitude;
}

bool GPSLocation::IsGPSFound(int lat, int lon)
{
	return (lat>0 && lon>0);
}

