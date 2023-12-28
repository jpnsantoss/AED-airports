
#include "StatisticsController.h"
#include "FlightController.h"

StatisticsController::StatisticsController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

size_t StatisticsController::getTotalAirports() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getAirports().size();
}

size_t StatisticsController::getTotalFlights() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getFlights().size();
}

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

int StatisticsController::numberOfFlightsPerCity(string &identifier) {
    int num = 0;
    Dataset* dataset = Dataset::getInstance();

    for(const Flight& f: dataset->getFlights()){
        if(f.getSource().getCity() == identifier || f.getTarget().getCity() == identifier)
            num++;
    }

    return num;
}

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

set<string> StatisticsController::numberOfCountriesForThisCity(string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    set<string> countries;

    for(const Flight& f: dataset->getFlights()){
        if(f.getSource().getCity() == identifier)
            countries.insert(f.getTarget().getCountry());
    }

    return countries;
}

size_t StatisticsController::getNumberOfDestinationAirports(const Airport& airport) const {
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    return origin->getAdj().size();
}

size_t StatisticsController::getNumberOfDestinationCountries(const Airport& airport) const {
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

size_t StatisticsController::getNumberOfDestinationCities(const Airport& airport) const {
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

int StatisticsController::getNumberOfReachableAirportsWithMaxStops(const Airport& airport, int maxStops) const {
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

size_t StatisticsController::getNumberOfReachableCountriesWithMaxStops(const Airport& airport, int maxStops) const {
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

size_t StatisticsController::getNumberOfReachableCitiesWithMaxStops(const Airport& airport, int maxStops) const {
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

void dfsAllPaths(Vertex<Airport>* v, std::vector<Airport>& path, int& maxStops, std::vector<Airport>& maxPath) {
    v->setProcessing(true);
    path.push_back(v->getInfo());

    if (path.size() > maxStops) {
        maxStops = path.size();
        maxPath = path;
    }

    for (const Edge<Airport>& e : v->getAdj()) {
        if (!e.getDest()->isProcessing()) {
            dfsAllPaths(e.getDest(), path, maxStops, maxPath);
        }
    }

    v->setProcessing(false);
    path.pop_back();
}

std::pair<Airport, Airport> StatisticsController::getMaximumTrip() {
    std::vector<Airport> path, maxPath;
    int maxStops = 0;

    for (Vertex<Airport>* v : airportGraph.getVertexSet()) {
        if (!v->isProcessing()) {
            dfsAllPaths(v, path, maxStops, maxPath);
        }
    }

    if (maxPath.empty()) {
        throw std::runtime_error("No path found");
    }

    return std::make_pair(maxPath.front(), maxPath.back());
}