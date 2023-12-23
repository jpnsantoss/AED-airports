//
// Created by jpsantos on 21-12-2023.
//

#include <vector>
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

vector<vector<Airport>> FlightController::getBestFlightOptionByAirport(const string &source, const string &destination) {
    try {
        Airport sourceAirport = findAirport(source);
        Airport destinationAirport = findAirport(destination);
        return getShortestPathsBFS(sourceAirport, destinationAirport);

    } catch (runtime_error &e) {
        throw runtime_error("No path found");
    }
}

vector<vector<Airport>> FlightController::getBestFlightOptionByCity(const string &source, const string &destination) {
    vector<Airport> sourceAirports = findAirportsByCity(source);
    vector<Airport> destinationAirports = findAirportsByCity(destination);

    if (sourceAirports.empty()) {
        throw runtime_error("Source city not found");
    }
    if (destinationAirports.empty()) {
        throw runtime_error("Destination city not found");
    }

    vector<vector<Airport>> bestPaths;
    int minStops = numeric_limits<int>::max();

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            try {
                vector<vector<Airport>> paths = getBestFlightOptionByAirport(sourceAirport.getAirportCode(), destinationAirport.getAirportCode());
                for (const auto &path : paths) {
                    if (path.size() - 1 < minStops) {
                        bestPaths.clear();
                        minStops = path.size() - 1;
                    }
                    if (path.size() - 1 == minStops) {
                        // Check if bestPaths already contains path
                        if (find(bestPaths.begin(), bestPaths.end(), path) == bestPaths.end()) {
                            // If not, add path to bestPaths
                            bestPaths.push_back(path);
                        }
                    }
                }
            } catch (runtime_error &e) {
                // Ignore exceptions for airports without a path
            }
        }
    }

    if (bestPaths.empty()) {
        throw runtime_error("No path found");
    }

    return bestPaths;
}

vector<vector<Airport>> FlightController::getBestFlightOptionByLocation(const Location &source, const Location &destination) {
    vector<Airport> sourceAirports = getNearestAirports(source);
    vector<Airport> destinationAirports = getNearestAirports(destination);

    vector<vector<Airport>> bestPaths;
    int minStops = numeric_limits<int>::max();

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            try {
                vector<vector<Airport>> paths = getBestFlightOptionByAirport(sourceAirport.getAirportCode(), destinationAirport.getAirportCode());
                for (const auto &path : paths) {
                    if (path.size() - 1 < minStops) {
                        bestPaths.clear();
                        minStops = path.size() - 1;
                    }
                    if (path.size() - 1 == minStops) {
                        // Check if bestPaths already contains path
                        if (find(bestPaths.begin(), bestPaths.end(), path) == bestPaths.end()) {
                            // If not, add path to bestPaths
                            bestPaths.push_back(path);
                        }
                    }
                }
            } catch (runtime_error &e) {
                // Ignore exceptions for airports without a path
            }
        }
    }

    if (bestPaths.empty()) {
        throw runtime_error("No path found");
    }

    return bestPaths;
}