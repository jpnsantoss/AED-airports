
#include "StatisticsController.h"
#include "FlightController.h"

/**
 * @brief Constructs a StatisticsControler object and initializes the airportGraph using the dataset.
 */
StatisticsController::StatisticsController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

/**
 * @brief Gets the total number of airports in the dataset.
 * Complexity: O(1).
 * @return The total number of airports.
 */
size_t StatisticsController::getTotalAirports() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getAirports().size();
}

/**
 * @brief Gets the total number of flights in the dataset.
 * Complexity: O(1).
 * @return The total number of flights.
 */
size_t StatisticsController::getTotalFlights() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getFlights().size();
}

/**
 * @brief Gets the number of flights out of a specific airport and the associated airlines.
 * Complexity: O(n), where n is the number of flights from the airport.
 * @param identifier - the origin airport code.
 * @return The number of flights.
 */
int StatisticsController::numberOfFlightsOutAirport(string &identifier) {
    int num = 0;
    Dataset* dataset = Dataset::getInstance();

    for (char& c: identifier)
        c = (char)toupper(c);
    Airport airport = FlightController::findAirport(identifier);

    for (const Flight& f : dataset->getFlights()) {
        if(f.getSource().getAirportCode() == airport.getAirportCode()) {
            num++;
        }
    }
    return num;
}

/**
 * @brief Gets a set of airlines the operate flights out of a specific airport.
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param identifier - the origin airport code.
 * @return A set of airlines operating flights out of the specified airport.
 */
set<Airline> StatisticsController::setOfFlightsOutAirport(string &identifier) {
    set<Airline> airlines;
    Dataset* dataset = Dataset::getInstance();

    for (char& c: identifier)
        c = (char)toupper(c);
    Airport airport = FlightController::findAirport(identifier);

    for (const Flight& f : dataset->getFlights()) {
        if(f.getSource().getAirportCode() == airport.getAirportCode()) {
            airlines.insert(f.getAirline());
        }
    }

    return airlines;
}

/**
 * @brief Gets the number of flights operated by a specific airline.
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param identifier - the airline code.
 * @return The number of flights operated by the specified airline.
 */
int StatisticsController::numberOfFlightsPerAirline(string &identifier) {
    int num = 0;
    Dataset* dataset = Dataset::getInstance();
    for (char& c: identifier)
        c = (char)toupper(c);

    for(const Flight& f: dataset->getFlights()){
        if(f.getAirline().getCode() == identifier)
            num++;
    }

    return num;
}

/**
 * @brief Gets the number of flights involving a specific city (as origin or destination).
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param identifier - the name of the city.
 * @return The number of flights involving the specified city.
 */
int StatisticsController::numberOfFlightsPerCity(string &identifier) {
    int num = 0;
    Dataset* dataset = Dataset::getInstance();

    for(const Flight& f: dataset->getFlights()){
        if(f.getSource().getCity() == identifier || f.getTarget().getCity() == identifier)
            num++;
    }

    return num;
}

/**
 * @brief Gets a set of the countries that a specific airport flies to.
 * Complexity: O(n), where n is the code of adjacent airports.
 * @param identifier - the origin airport code.
 * @return A set of countries that the specified airport flies to.
 */
set<string> StatisticsController::numberOfCountriesForThisAirport(string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    set<string> countries;

    for (char& c: identifier)
        c = (char)toupper(c);

    for(const Flight& f: dataset->getFlights()){
        if(f.getSource().getAirportCode() == identifier)
            countries.insert(f.getTarget().getCountry());
    }

    return countries;
}

/**
 * @brief Gets the number of destination airports for a given airport.
 * Complexity: O(n), where n is the number of adjacent airports.
 * @param code - the origin airport code.
 * @return The number of destination airports.
 */
set<string> StatisticsController::numberOfCountriesForThisCity(string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    set<string> countries;

    for(const Flight& f: dataset->getFlights()){
        if(f.getSource().getCity() == identifier)
            countries.insert(f.getTarget().getCountry());
    }

    return countries;
}

/**
 * @brief Gets the number of destination airports for a given airport.
 * Complexity: O(n), where n is the number of adjacent airports.
 * @param code - the origin airport code.
 * @return The number of destination airports.
 */
size_t StatisticsController::getNumberOfDestinationAirports(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::set<std::string> destinationAirports;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        destinationAirports.insert(edge.getDest()->getInfo().getAirportCode());
    }
    return destinationAirports.size();
}

/**
 * @brief Gets the number of destination countries for a given airport.
 * Complexity: O(n), where n is the number of adjacent airports.
 * @param code - the origin airport code.
 * @return The number of destination countries.
 */
size_t StatisticsController::getNumberOfDestinationCountries(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::set<std::string> destinationCountries;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        const Airport& destinationAirport = edge.getDest()->getInfo();
        destinationCountries.insert(destinationAirport.getCountry());
    }
    return destinationCountries.size();
}

/**
 * @brief Gets the number of destination cities for a given airport.
 * Complexity: O(n), where n is the number of adjacent airports.
 * @param code - the origin airport code.
 * @return The number of destination cities.
 */
size_t StatisticsController::getNumberOfDestinationCities(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::set<std::string> destinationCities;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        const Airport& destinationAirport = edge.getDest()->getInfo();
        destinationCities.insert(destinationAirport.getCity());
    }
    return destinationCities.size();
}

/**
 * @brief Gets the number of reachable airports with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable airports with those stops.
 */
int StatisticsController::getNumberOfReachableAirportsWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::queue<std::pair<Vertex<Airport>*, int>> queue;
    std::set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    int reachableAirports = 0;
    while (!queue.empty()) {
        std::pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            reachableAirports++;
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                if (visited.find(neighbor) == visited.end()) {
                    queue.emplace(neighbor, current.second + 1);
                    visited.insert(neighbor);
                }
            }
        }
    }
    return reachableAirports-1;
}

/**
 * @brief Gets the number of reachable countries with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable countries with those stops.
 */
size_t StatisticsController::getNumberOfReachableCountriesWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::queue<std::pair<Vertex<Airport>*, int>> queue;
    std::set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    std::set<std::string> reachableCountries;
    while (!queue.empty()) {
        std::pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.emplace(neighbor, current.second + 1);
                visited.insert(neighbor);
                reachableCountries.insert(neighbor->getInfo().getCountry());
            }
        }
    }
    return reachableCountries.size();
}

/**
 * @brief Gets the number of reachable cities with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable cities with those stops.
 */
size_t StatisticsController::getNumberOfReachableCitiesWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    std::queue<std::pair<Vertex<Airport>*, int>> queue;
    std::set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    std::set<std::string> reachableCities;
    while (!queue.empty()) {
        std::pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.emplace(neighbor, current.second + 1);
                visited.insert(neighbor);
                reachableCities.insert(neighbor->getInfo().getCity());
            }
        }
    }
    return reachableCities.size();
}

/**
 * @brief Depth-first search to find all paths starting from a vertex.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code
 * @param maxStops - maximum number of stops.
 * @return The number of reachable cities with those stops.
 */
void dfsAllPaths(Vertex<Airport>* v, std::vector<Airport>& path, int& maxStops, std::vector<std::pair<Airport, Airport>>& maxPaths) {
    v->setProcessing(true);
    path.push_back(v->getInfo());

    if (path.size() > maxStops) {
        maxStops = path.size();
        maxPaths.clear();
        maxPaths.push_back(std::make_pair(path.front(), path.back()));
    } else if (path.size() == maxStops) {
        maxPaths.push_back(std::make_pair(path.front(), path.back()));
    }

    for (const Edge<Airport>& e : v->getAdj()) {
        if (!e.getDest()->isProcessing()) {
            dfsAllPaths(e.getDest(), path, maxStops, maxPaths);
        }
    }

    v->setProcessing(false);
    path.pop_back();
}

std::vector<std::pair<Airport, Airport>> StatisticsController::getMaximumTrips() {
    std::vector<Airport> path;
    std::vector<std::pair<Airport, Airport>> maxPaths;
    int maxStops = 0;

    for (Vertex<Airport>* v : airportGraph.getVertexSet()) {
        if (!v->isProcessing()) {
            dfsAllPaths(v, path, maxStops, maxPaths);
        }
    }

    if (maxPaths.empty()) {
        throw std::runtime_error("No path found");
    }

    return maxPaths;
}