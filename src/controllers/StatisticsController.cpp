
#include "StatisticsController.h"

StatisticsController::StatisticsController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

size_t StatisticsController::getTotalAirports() const {
    return airportGraph.getVertexSet().size();
}

size_t StatisticsController::getTotalFlights() const {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getFlights().size();
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
    queue.push({origin, 0});
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
                    queue.push({neighbor, current.second + 1});
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
    queue.push({origin, 0});
    visited.insert(origin);
    std::set<std::string> reachableCountries;
    while (!queue.empty()) {
        std::pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.push({neighbor, current.second + 1});
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
    queue.push({origin, 0});
    visited.insert(origin);
    std::set<std::string> reachableCities;
    while (!queue.empty()) {
        std::pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.push({neighbor, current.second + 1});
                visited.insert(neighbor);
                reachableCities.insert(neighbor->getInfo().getCity());
            }
        }
    }
    return reachableCities.size();
}