//
// Created by jpsantos on 17-12-2023.
//

#include <fstream>
#include <sstream>
#include "Dataset.h"
#include <iostream>

Dataset* Dataset::dataset = nullptr;

Dataset::Dataset() {
    loadAirports();
    loadAirlines();
    loadFlights();
}

Dataset* Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}

void Dataset::loadAirports() {
    ifstream file("data/airports.csv");
    if (!file.is_open()) {
        cout << "Error: File 'airports.csv' not opened." << endl;
        return;
    }

    string row, airportCode, airportName, city, country;
    string latitude_str, longitude_str;
    double latitude, longitude;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, airportCode, ',');
        getline(line, airportName, ',');
        getline(line, city, ',');
        getline(line, country, ',');
        getline(line, latitude_str, ',');
        getline(line, longitude_str, '\r');

        latitude = stod(latitude_str);
        longitude = stod(longitude_str);

        Location location(latitude, longitude);
        Airport airport(airportCode, airportName, city, country, location);
        airportGraph.addVertex(airport);
        airports.push_back(airport);
    }
    file.close();
}

void Dataset::loadAirlines() {
    ifstream file("data/airlines.csv");
    if (!file.is_open()) {
        cout << "Error: File 'airlines.csv' not opened." << endl;
        return;
    }

    string row, airlineCode, airlineName, callsign, country;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, airlineCode, ',');
        getline(line, airlineName, ',');
        getline(line, callsign, ',');
        getline(line, country, '\r');

        airlines.emplace_back(airlineCode, airlineName, callsign, country);
    }
    file.close();
}

void Dataset::loadFlights() {
    ifstream file("data/flights.csv");
    if (!file.is_open()) {
        cout << "Error: File 'flights.csv' not opened." << endl;
        return;
    }

    string row, sourceCode, targetCode, airlineCode;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, sourceCode, ',');
        getline(line, targetCode, ',');
        getline(line, airlineCode, '\r');

        // Find the actual Airport and Airline objects from the dataset
        Airport source = findAirportByCode(sourceCode);
        Airport target = findAirportByCode(targetCode);
        Airline airline = findAirlineByCode(airlineCode);
        Flight flight(source, target, airline);
        flights.push_back(flight);
        airportGraph.addEdge(source, target, flight.getDistance());
    }
    file.close();
}

// Getters
const vector<Flight> &Dataset::getFlights() const {
    return flights;
}

const vector<Airport> &Dataset::getAirports() const {
    return airports;
}

const vector<Airline> &Dataset::getAirlines() const {
    return airlines;
}

const Graph<Airport> &Dataset::getAirportGraph() const {
    return airportGraph;
}

//Aux functions
Airport Dataset::findAirportByCode(const string &code) {
    for (const auto &airport : airports) {
        if (airport.getAirportCode() == code) {
            return airport;
        }
    }
    throw std::runtime_error("Airport not found");
}

Airline Dataset::findAirlineByCode(const string &code) {
    for (const auto &airline : airlines) {
        if (airline.getCode() == code) {
            return airline;
        }
    }
    throw std::runtime_error("Airline not found");
}
