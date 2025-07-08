#pragma once

class GPSLocation
{
public:
	GPSLocation(int lat, int lon);
	GPSLocation();
	int Longitude();
	int Latitude();

private:
	static bool IsGPSFound(int lat, int lon);
	int longitude;
	int latitude;
};