

#include "Dataset.h"


Dataset* Dataset::dataset = nullptr;

Dataset::Dataset() {
    loadAirports();
    loadAirlines();
    loadFlights();
}

/**
 * @brief Gets the singleton instance of the Dataset class.
 * @return A pointer to the instance.
 */
Dataset* Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}

/**
 * @brief Load airports data from 'airports.csv'.
 */
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

/**
 * @brief Load airlines data from 'airports.csv'.
 */
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

/**
 * @brief Load flights data from 'airports.csv'.
 */
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
        airportGraph.addEdge(source, target, flight.getDistance(), flight.getAirline());
    }
    file.close();
}

// Getters

/**
 * @brief Gets a vector of all Flight objects.
 * @return A constant reference to the vector of Flight objects.
 */
const vector<Flight> &Dataset::getFlights() const {
    return flights;
}

/**
 * @brief Gets a vector of all Airport objects.
 * @return A constant reference to the vector of Airport objects.
 */
const vector<Airport> &Dataset::getAirports() const {
    return airports;
}

/**
 * @brief Gets a vector of all Airline objects.
 * @return A constant reference to the vector of Airline objects.
 */
const vector<Airline> &Dataset::getAirlines() const {
    return airlines;
}

/**
 * @brief Gets the graph of Airport objects.
 * @return A constant reference to the graph of Airport objects.
 */
const Graph<Airport> &Dataset::getAirportGraph() const {
    return airportGraph;
}

//Aux functions

/**
 * @brief Finds an airport by its code.
 * Complexity: O(n), where n is the number of airports.
 * @param code - the airport code.
 * @return The airport object with the specified code.
 */
Airport Dataset::findAirportByCode(const string &code) {
    for (const Airport& airport : airports) {
        if (airport.getAirportCode() == code) {
            return airport;
        }
    }
    throw runtime_error("Airport not found");
}

/**
 * @brief Finds an airline by its code.
 * Complexity: O(n), where n is the number of airlines.
 * @param code - the airline code.
 * @return The airline object with the specified code.
 */
Airline Dataset::findAirlineByCode(const string &code) {
    for (const Airline& airline : airlines) {
        if (airline.getCode() == code) {
            return airline;
        }
    }
    throw runtime_error("Airline not found");
}

/**
 * @brief Finds a flight based on source and destination airports.
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param source - the source airport of the flight.
 * @param destination - the destination airport of the flight.
 * @return A pointer to the found flight object; nullptr if not found.
 */
Flight* Dataset::findFlight(const Airport& source, const Airport& destination) {
    for (Flight& flight : flights) {
        if (flight.getSource() == source && flight.getTarget() == destination) {
            return &flight;
        }
    }
    return nullptr;
}
