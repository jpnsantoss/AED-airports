//
// Created by jpsantos on 16-12-2023.
//

#include "Flight.h"

// Constructor
Flight::Flight(const std::string &flightNumber, const std::string &departureAirport, const std::string &arrivalAirport, const std::string &departureTime, const std::string &arrivalTime)
        : flightNumber(flightNumber), departureAirport(departureAirport), arrivalAirport(arrivalAirport), departureTime(departureTime), arrivalTime(arrivalTime) {}


// Getters
string Flight::getFlightNumber() const {
    return flightNumber;
}

string Flight::getDepartureAirport() const {
    return departureAirport;
}

string Flight::getArrivalAirport() const {
    return arrivalAirport;
}

string Flight::getDepartureTime() const {
    return departureTime;
}

string Flight::getArrivalTime() const {
    return arrivalTime;
}

// Setters
void Flight::setFlightNumber(const string &flightNumber) {
    Flight::flightNumber = flightNumber;
}

void Flight::setDepartureAirport(const string &departureAirport) {
    Flight::departureAirport = departureAirport;
}

void Flight::setArrivalAirport(const string &arrivalAirport) {
    Flight::arrivalAirport = arrivalAirport;
}

void Flight::setDepartureTime(const string &departureTime) {
    Flight::departureTime = departureTime;
}

void Flight::setArrivalTime(const string &arrivalTime) {
    Flight::arrivalTime = arrivalTime;
}