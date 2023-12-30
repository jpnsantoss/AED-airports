//
// Created by jpsantos on 18-12-2023.
//

#include "Location.h"
#include <cmath>

// Constructor
Location::Location() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

// Constructor
Location::Location(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

// Getters
double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}

// Setters
void Location::setLatitude(double latitude) {
    this->latitude = latitude;
}

void Location::setLongitude(double longitude) {
    this->longitude = longitude;
}

// Distance calculation
double Location::calculateDistanceTo(const Location &other) const {
    double lat1 = this->latitude;
    double lon1 = this->longitude;
    double lat2 = other.getLatitude();
    double lon2 = other.getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}