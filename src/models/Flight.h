//
// Created by jpsantos on 16-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_FLIGHT_H
#define PROJECT_AED_AIRPORTS_FLIGHT_H

#include <string>
using namespace std;
class Flight {
private:
    string flightNumber;
    string departureAirport;
    string arrivalAirport;
    string departureTime;
    string arrivalTime;

public:
    // Constructor
    Flight(const string &flightNumber, const string &departureAirport, const string &arrivalAirport, const string &departureTime, const string &arrivalTime);

    // Getters
    string getFlightNumber() const;
    string getDepartureAirport() const;
    string getArrivalAirport() const;
    string getDepartureTime() const;
    string getArrivalTime() const;

    // Setters
    void setFlightNumber(const string &flightNumber);
    void setDepartureAirport(const string &departureAirport);
    void setArrivalAirport(const string &arrivalAirport);
    void setDepartureTime(const string &departureTime);
    void setArrivalTime(const string &arrivalTime);
};

#endif //PROJECT_AED_AIRPORTS_FLIGHT_H