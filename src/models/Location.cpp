
#include "Location.h"
#include <cmath>

// Constructor
Location::Location() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

/**
 * @brief Constructor for Location class.
 * @param latitude - the latitude of the location.
 * @param longitude - the longitude of the location.
 */
Location::Location(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

// Getters
/**
 * @brief Gets the latitude of the location.
 * @return The latitude.
 */
double Location::getLatitude() const {
    return latitude;
}

/**
 * @brief Gets the longitude of the location.
 * @return The longitude.
 */
double Location::getLongitude() const {
    return longitude;
}

// Setters
/**
 * @brief Sets the latitude of the location.
 * @param latitude - The new latitude.
 */
void Location::setLatitude(double latitude) {
    this->latitude = latitude;
}

/**
 * @brief Sets the longitude of the location.
 * @param longitude - The new longitude.
 */
void Location::setLongitude(double longitude) {
    this->longitude = longitude;
}

// Distance calculation
/**
 * @brief Calculates the distance between two locations.
 * @param other - The other location for distance calculation.
 * @param return - The distance between location.
 */
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