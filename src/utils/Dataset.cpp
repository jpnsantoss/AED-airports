

#include "Dataset.h"


Dataset* Dataset::dataset = nullptr;

Dataset::Dataset() {
    loadAirports();
    loadAirlines();
    loadFlights();
}

/**
 * @brief Gets the singleton instance of the Dataset class.
 * Complexity: O(1)
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
 * Complexity: O(n), where n is the number of lines in the file.
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
        airports.insert(airport);
    }
    file.close();
}

/**
 * @brief Load airlines data from 'airports.csv'.
 * Complexity: O(n), where n is the number of lines in the file.
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

        airlines.emplace(airlineCode, airlineName, callsign, country);
    }
    file.close();
}

/**
 * @brief Load flights data from 'airports.csv'.
 * Complexity: O(n), where n is the number of lines in the file.
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
        flights.insert(flight);
        airportGraph.addEdge(source, target, flight.getDistance(), flight.getAirline());
    }
    file.close();
}

// Getters

/**
 * @brief Gets a vector of all Airport objects.
 * @return A constant reference to the vector of Airport objects.
 */
const unordered_set<Airport> &Dataset::getAirports() const {
    return airports;
}

/**
 * @brief Gets a vector of all Airline objects.
 * Complexity: O(1)
 * @return A constant reference to the vector of Airline objects.
 */
const unordered_set<Airline> &Dataset::getAirlines() const {
    return airlines;
}

/**
 * @brief Gets a vector of all Airport objects.
 * Complexity: O(1)
 * @return A constant reference to the vector of Airport objects.
 */
const unordered_set<Flight> &Dataset::getFlights() const {
    return flights;
}

/**
 * @brief Gets the graph of Airport objects.
 * Complexity: O(1)
 * @return A constant reference to the graph of Airport objects.
 */
const Graph<Airport> &Dataset::getAirportGraph() const {
    return airportGraph;
}

//Aux functions

/**
 * @brief Finds an airport given its code.
 * Complexity: O(1) on average, O(n) in the worst case, where n is the number of airports.
 * @param code - The airport code.
 * @return A pointer to the Airport object if found, otherwise throws an exception.
 */
Airport Dataset::findAirportByCode(const string &code) {
    auto it = airports.find(Airport(code));
    if (it != airports.end()) {
        return *it;
    }
    throw runtime_error("Airport not found");
}

/**
 * @brief Finds an airline given its code.
 * Complexity: O(1) on average, O(n) in the worst case, where n is the number of airlines.
 * @param code - The airline code.
 * @return A pointer to the Airline object if found, otherwise throws an exception.
 */
Airline Dataset::findAirlineByCode(const string &code) {
    auto it = airlines.find(Airline(code));
    if (it != airlines.end()) {
        return *it;
    }
    throw runtime_error("Airline not found");
}

/**
 * @brief Finds a flight given the source and destination airports.
 * Complexity: O(1) on average, O(n) in the worst case, where n is the number of flights.
 * @param source - The source airport.
 * @param destination - The destination airport.
 * @return A pointer to the Flight object if found, otherwise throws an exception.
 */
Flight * Dataset::findFlight(const Airport& source, const Airport& destination) {
    auto it = flights.find(Flight(source, destination, Airline("")));
    if (it != flights.end()) {
        return const_cast<Flight*>(&(*it));
    }
    throw runtime_error("Flight not found");
}