//
// Created by jpsantos on 17-12-2023.
//

#include <fstream>
#include <sstream>
#include "Dataset.h"
#include <iostream>

Dataset* Dataset::dataset = nullptr;

Dataset::Dataset() {
    loadFlights();
    loadAirports();
    loadAirlines();
}

Dataset* Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}

void Dataset::loadFlights() {
    std::ifstream file("data/flights.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'flights.csv' not opened." << std::endl;
        return;
    }

    std::string row, flightNumber, departureAirport, arrivalAirport, departureTime, arrivalTime;
    getline(file, row);

    while (getline(file, row)) {
        std::istringstream line(row);
        getline(line, flightNumber, ',');
        getline(line, departureAirport, ',');
        getline(line, arrivalAirport, ',');
        getline(line, departureTime, ',');
        getline(line, arrivalTime, '\r');

        flights.emplace_back(flightNumber, departureAirport, arrivalAirport, departureTime, arrivalTime);
    }
    file.close();
}

void Dataset::loadAirports() {
    std::ifstream file("data/airports.csv");
    if (!file.is_open()) {
        std::cout << "Error: File 'airports.csv' not opened." << std::endl;
        return;
    }

    std::string row, airportCode, airportName, city, country;
    getline(file, row);

    while (getline(file, row)) {
        std::istringstream line(row);
        getline(line, airportCode, ',');
        getline(line, airportName, ',');
        getline(line, city, ',');
        getline(line, country, '\r');

        airports.emplace_back(airportCode, airportName, city, country);
    }
    file.close();
}

void Dataset::loadAirlines() {
    ifstream file("data/airlines.csv");
    if (!file.is_open()) {
        cout << "Error: File 'airlines.csv' not opened." << endl;
        return;
    }

    string row, airlineCode, airlineName;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, airlineCode, ',');
        getline(line, airlineName, '\r');

        airlines.emplace_back(airlineCode, airlineName);
    }
    file.close();
}

const vector<Flight> &Dataset::getFlights() const {
    return flights;
}

const vector<Airport> &Dataset::getAirports() const {
    return airports;
}

const vector<Airline> &Dataset::getAirlines() const {
    return airlines;
}