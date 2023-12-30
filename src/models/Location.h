//
// Created by jpsantos on 18-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_LOCATION_H
#define PROJECT_AED_AIRPORTS_LOCATION_H

class Location {
private:
    double latitude;
    double longitude;

public:
    Location();
    // Constructor
    Location(double latitude, double longitude);

    // Getters
    double getLatitude() const;
    double getLongitude() const;

    // Setters
    void setLatitude(double latitude);
    void setLongitude(double longitude);

    // Distance calculation
    double calculateDistanceTo(const Location &other) const;
};

#endif //PROJECT_AED_AIRPORTS_LOCATION_H
