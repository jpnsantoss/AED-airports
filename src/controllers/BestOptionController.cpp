//
// Created by jpsantos on 28-12-2023.
//

#include <sstream>
#include <algorithm>
#include "BestOptionController.h"
#include "FlightController.h"

BestOptionController::BestOptionController() {
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

vector<vector<Airport>> BestOptionController::getShortestPathsBFS(const Airport &origin, const Airport &destination) {
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

void BestOptionController::buildPaths(Vertex<Airport>* origin, Vertex<Airport>* destination, std::map<Vertex<Airport>*, std::vector<Vertex<Airport>*>>& prev, std::vector<Airport>& path, std::vector<std::vector<Airport>>& paths) {
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

void BestOptionController::findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res) {
    try {
        Airport sourceAirport = FlightController::findAirport(source);
        Airport destinationAirport = FlightController::findAirport(destination);
        vector<vector<Airport>> paths = getShortestPathsBFS(sourceAirport, destinationAirport);
        res.insert(res.end(), paths.begin(), paths.end());
    } catch (runtime_error &e) {
        // Ignore exceptions for airports without a path
    }
}

vector<vector<Airport>> BestOptionController::getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption, const string &destination) {
    vector<vector<Airport>> res;

    switch (sourceOption) {
        case FlightOption::ByAirportCode:
        {
            vector<Airport> sourceAirports = vector<Airport>{FlightController::findAirport(source)};
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
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
            vector<Airport> sourceAirports = FlightController::findAirportsByName(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));

                        vector<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
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
            vector<Airport> sourceAirports = FlightController::findAirportsByCity(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
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
            vector<Airport> sourceAirports = FlightController::getNearestAirports(sourceLocation);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        vector<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        vector<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
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