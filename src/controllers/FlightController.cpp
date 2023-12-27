//
// Created by jpsantos on 21-12-2023.
//
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "FlightController.h"
FlightController::FlightController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Method to find an airport by its code or name
Airport FlightController::findAirport(const string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    try {
        // Try to find the airport by its code
        return dataset->findAirportByCode(identifier);
    } catch (runtime_error &e) {
        // If the airport is not found by its code, search all airports by their name
        const vector<Airport> &airports = dataset->getAirports();
        for (const auto &airport : airports) {
            if (airport.getAirportName() == identifier) {
                return airport;
            }
        }
    }

    throw runtime_error("Airport not found");
}

vector<Airport> FlightController::findAirportsByName(const string &name) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> matchingAirports;

    for (const auto &airport : airports) {
        if (airport.getAirportName() == name) {
            matchingAirports.push_back(airport);
        }
    }

    return matchingAirports;
}

// Method to find all airports in a given city
vector<Airport> FlightController::findAirportsByCity(const string &city) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> airportsInCity;

    for (const auto &airport : airports) {
        if (airport.getCity() == city) {
            airportsInCity.push_back(airport);
        }
    }

    return airportsInCity;
}


vector<Airport> FlightController::getNearestAirports(const Location &location) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> nearestAirports;
    double minDistance = numeric_limits<double>::max();

    for (const auto &airport : airports) {
        double distance = location.calculateDistanceTo(airport.getLocation());
        if (distance < minDistance) {
            nearestAirports.clear();
            minDistance = distance;
        }
        if (distance == minDistance) {
            nearestAirports.push_back(airport);
        }
    }

    return nearestAirports;
}

vector<vector<Airport>> FlightController::getShortestPathsBFS(const Airport &origin, const Airport &destination) {
    map<Vertex<Airport>*, vector<Vertex<Airport>*>> prev;
    queue<Vertex<Airport>*> queue;
    vector<vector<Airport>> paths;

    Vertex<Airport>* originVertex = airportGraph.findVertex(origin);
    Vertex<Airport>* destinationVertex = airportGraph.findVertex(destination);

    if (originVertex == nullptr || destinationVertex == nullptr) {
        throw runtime_error("Origin or destination airport not found");
    }

    for(Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        vertex->setVisited(false);
    }

    originVertex->setVisited(true);
    queue.push(originVertex);
    while (!queue.empty()) {
        Vertex<Airport>* vertex = queue.front();
        queue.pop();

        if (vertex->getInfo() == destination) {
            vector<Airport> path;
            buildPaths(originVertex, destinationVertex, prev, path, paths);
            return paths;
        }

        for (const Edge<Airport> &edge : vertex->getAdj()) {
            Vertex<Airport>* neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                neighbor->setVisited(true);
                queue.push(neighbor);
                prev[neighbor].push_back(vertex);
            }
        }
    }

    return paths; // Return an empty vector if no path is found
}

void FlightController::buildPaths(Vertex<Airport>* origin, Vertex<Airport>* destination, std::map<Vertex<Airport>*, std::vector<Vertex<Airport>*>>& prev, std::vector<Airport>& path, std::vector<std::vector<Airport>>& paths) {
    path.push_back(destination->getInfo());
    if (destination == origin) {
        std::vector<Airport> newPath = path;
        std::reverse(newPath.begin(), newPath.end());
        paths.push_back(newPath);
    } else {
        for (Vertex<Airport>* vertex : prev[destination]) {
            buildPaths(origin, vertex, prev, path, paths);
        }
    }
    path.pop_back();
}

void FlightController::findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res) {
    try {
        Airport sourceAirport = findAirport(source);
        Airport destinationAirport = findAirport(destination);
        vector<vector<Airport>> paths = getShortestPathsBFS(sourceAirport, destinationAirport);
        res.insert(res.end(), paths.begin(), paths.end());
    } catch (runtime_error &e) {
        // Ignore exceptions for airports without a path
    }
}

vector<vector<Airport>> FlightController::getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption, const string &destination) {
    vector<vector<Airport>> res;

    switch (sourceOption) {
        case FlightOption::ByAirportCode:
        {
            vector<Airport> sourceAirports = vector<Airport>{findAirport(source)};
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByAirportName:
        {
            vector<Airport> sourceAirports = findAirportsByName(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));

                        vector<Airport> destinationAirports = getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByCity:
        {
            vector<Airport> sourceAirports = findAirportsByCity(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByLocation:
        {
            vector<string> sourceCoords = splitString(source, ',');
            Location sourceLocation(stod(sourceCoords[0]), stod(sourceCoords[1]));
            vector<Airport> sourceAirports = getNearestAirports(sourceLocation);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{findAirport(destination)};
                        for (auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        default:
            throw runtime_error("Invalid source option");
    }

    return res;
}

size_t FlightController::getTotalAirports() const {
    return airportGraph.getVertexSet().size();
}

size_t FlightController::getTotalFlights() const {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getFlights().size();
}

size_t FlightController::getNumberOfDestinationAirports(const Airport& airport) const {
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw std::runtime_error("Airport not found");
    }
    return origin->getAdj().size();
}

size_t FlightController::getNumberOfDestinationCountries(const Airport& airport) const {
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

size_t FlightController::getNumberOfDestinationCities(const Airport& airport) const {
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

int FlightController::getNumberOfReachableAirportsWithMaxStops(const Airport& airport, int maxStops) const {
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

size_t FlightController::getNumberOfReachableCountriesWithMaxStops(const Airport& airport, int maxStops) const {
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

size_t FlightController::getNumberOfReachableCitiesWithMaxStops(const Airport& airport, int maxStops) const {
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